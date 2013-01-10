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

const char *bus_str(int bus);
#define VENDOR_ID 0x1941
#define PRODUCT_ID 0x8021

int main(int argc, char **argv)
{
	int fd;
	int i, res;
	const char *devpath;
	char buf[256];
	struct udev *udev;
	struct udev_enumerate *enumerate;
	struct udev_list_entry *devices,
			       *dev_list_entry;
	struct udev_device *dev;

	/* Udev madness */
	udev = udev_new();
	if(udev == NULL)
	{
		fprintf(stderr, "Can't create udev\n");
		return(1);
	}

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
			return(1);
		}

		if(strtol(udev_device_get_sysattr_value(dev,"idVendor"), NULL, 16) == VENDOR_ID
		   && strtol(udev_device_get_sysattr_value(dev,"idProduct"), NULL, 16) == PRODUCT_ID)
			break;

		udev_device_unref(dev);
		devpath = NULL;
	}

	udev_enumerate_unref(enumerate);
	udev_unref(udev);

	/* open the device */
	if(devpath == NULL)
	{
		fprintf(stderr, "Device not found.\n");
		return(1);
	}

	fd = open(devpath, O_RDONLY | O_NONBLOCK);
	if(fd < 0)
	{
		perror("Unable to open device");
		return(1);
	}

	/* Begin the main loop. Finally */
	memset(buf, 0x0, sizeof(buf));
	initscr();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);

	while(1)
	{
		res = read(fd, buf, 16);
		if (res < 0) {
			if(errno == EAGAIN)
				continue;
			perror("read");
		} else {
			clear();
			mvprintw(1, 0, "read() read %d bytes:", res);
			for (i = 0; i < res; i++)
				mvprintw(2, 8 + (i * 3),"%hhx", buf[i]);
		}
		refresh();
	}

	endwin();
	close(fd);
	udev_device_unref(dev);
	return(0);
}
