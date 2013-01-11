#include <linux/types.h>
#include <linux/input.h>
#include <linux/hidraw.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <curses.h>
#include <fcntl.h>
#include <libudev.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define VENDOR_ID 0x1941
#define PRODUCT_ID 0x8021
#define streq(s1, s2) !strcmp(s1, s2)

#define DISABLE_CURSES if(1)

const char *
hiddev_path(struct udev *udev)
{
	const char *devpath;
	struct udev_enumerate *enumerate;
	struct udev_list_entry *devices,
			       *dev_list_entry;
	struct udev_device *dev = NULL;

	/* Udev madness */
	enumerate = udev_enumerate_new(udev);
	udev_enumerate_add_match_subsystem(enumerate, "hidraw");
	udev_enumerate_scan_devices(enumerate);
	devices = udev_enumerate_get_list_entry(enumerate);

	udev_list_entry_foreach(dev_list_entry, devices)
	{
		const char *path;
		path = udev_list_entry_get_name(dev_list_entry);
		dev = udev_device_new_from_syspath(udev, path);
		devpath = udev_device_get_devnode(dev);

		dev = udev_device_get_parent_with_subsystem_devtype(
					dev, "usb", "usb_device");
		if (dev == NULL)
		{
			fprintf(stderr, "Unable to find parent usb device.\n");
			udev_enumerate_unref(enumerate);
			return NULL;
		}

		if(strtol(udev_device_get_sysattr_value(dev, "idVendor"), NULL, 16) == VENDOR_ID
		   && strtol(udev_device_get_sysattr_value(dev, "idProduct"), NULL, 16) == PRODUCT_ID)
		{
			udev_device_unref(dev);
			break;
		}

		udev_device_unref(dev);
		devpath = NULL;
	}

	udev_enumerate_unref(enumerate);

	return(devpath);
}

void
draw_board(void *chars)
{
}

int main(int argc, char **argv)
{
	fd_set fds;
	struct timeval tv;
	int fd = -1;
	int x, y, monfd, res, ret;
	const char *devpath;
	char buf[256];
	char row[72];
	struct udev *udev;
	struct udev_monitor *mon;
	struct udev_device *dev = NULL;

	udev = udev_new();
	if(udev == NULL)
	{
		fprintf(stderr, "Can't create udev\n");
		udev_unref(udev);
		return(1);
	}

	mon = udev_monitor_new_from_netlink(udev, "udev");
	udev_monitor_filter_add_match_subsystem_devtype(mon, "hidraw", NULL);
	udev_monitor_enable_receiving(mon);
	monfd = udev_monitor_get_fd(mon);

	devpath = hiddev_path(udev);
	if(devpath == NULL)
	{
		fprintf(stderr, "Device not found.\n");
		return(1);
	}

	fd = open(devpath, O_RDONLY | O_NONBLOCK);
	if(fd < 0)
	{
		perror("Unable to open device.\n");
		return(1);
	}
	printf("%d\n", fd);

	/* Begin the main loop. Finally */
	memset(buf, 0x0, sizeof(buf));
	memset(row, '\0', sizeof(row));

	DISABLE_CURSES initscr();
	DISABLE_CURSES cbreak();
	DISABLE_CURSES noecho();
	DISABLE_CURSES nonl();
	DISABLE_CURSES intrflush(stdscr, FALSE);
	DISABLE_CURSES keypad(stdscr, TRUE);

	while(1)
	{

		FD_ZERO(&fds);
		FD_SET(monfd, &fds);
		tv.tv_sec = 0;
		tv.tv_usec = 0;

		ret = select(fd+1, &fds, NULL, NULL, &tv);
		if(ret > 0 && FD_ISSET(monfd, &fds))
		{
			dev = udev_monitor_receive_device(mon);
			if (dev == NULL)
				continue;

			if(streq(udev_device_get_action(dev), "add"))
			{
				devpath = hiddev_path(udev);
				if(devpath == NULL)
				{
					fprintf(stderr, "Device not found.\n");
					udev_device_unref(dev);
					continue;
				}

				fd = open(devpath, O_RDONLY | O_NONBLOCK);
				if(fd < 0)
				{
					perror("Unable to open device.\n");
					udev_device_unref(dev);
					continue;
				}
			}
			else if(streq(udev_device_get_action(dev), "remove") &&
				streq(udev_device_get_devpath(dev), devpath))
			{
				devpath = NULL;
				fd = -1;
				udev_device_unref(dev);
				continue;
			}

			udev_device_unref(dev);
		}

		if(fd < 0)
		{
			usleep(5000);
			continue;
		}

		res = read(fd, buf, 16);
		if(res < 0)
		{
			if(errno == EAGAIN)
				continue;
			perror("read");
		}
		else
		{
			for(x = 0; x < res; x++)
			{
				for(y = 0; y < res; y++)
					row[y + (x * (res + 1))] = ((0x80 >> x) & buf[y]) ? '*' : '0';
				DISABLE_CURSES mvprintw(1+x, 1, (const char *)&row[x * (res + 1)]);
			}
		}
		usleep(1000);
		DISABLE_CURSES refresh();
	}

	DISABLE_CURSES endwin();
	close(fd);
	udev_unref(udev);

	return(0);
}
