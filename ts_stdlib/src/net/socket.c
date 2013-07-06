#include <unistd.h>

#include "twinshadow/net.h"

/*
 * return socket connection from addrinfo
 */
int
soconnect(struct addrinfo *ad)
{
	int sock_fd = socket(ad->ai_family, ad->ai_socktype, ad->ai_protocol);

	if(sock_fd < 0)
		return sock_fd;

	if(connect(sock_fd, ad->ai_addr, ad->ai_addrlen) == -1)
	{
		close(sock_fd);
		return -1;
	}

	return sock_fd;
}

/*
 * return socket binding from addrinfo
 */
int
sobind(struct addrinfo *ad)
{
	int sock_fd = socket(ad->ai_family, ad->ai_socktype, ad->ai_protocol);

	if(sock_fd < 0)
		return sock_fd;

	if(bind(sock_fd, ad->ai_addr, ad->ai_addrlen) == -1)
	{
		close(sock_fd);
		return -1;
	}

	return sock_fd;
}
