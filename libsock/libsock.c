#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libsock.h"

/*
 * Return the addrinfo from the selected options
 */
extern struct addrinfo*
get_addr(char *address,
	char *port,
	int family,
	int socktype,
	int flags,
	int proto)
{
	int echeck;
	struct addrinfo hint;
	struct addrinfo *adr;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = family;
	hint.ai_socktype = socktype;
	hint.ai_flags = flags;
	hint.ai_protocol = proto;

	echeck = getaddrinfo(address, port, &hint, &adr);
	if(echeck != 0){
		perror("libsock: getaddrinfo");
		fputs(gai_strerror(echeck), stderr);
		return(NULL);
	}
	return(adr);
}

/*
 * get sockaddr, IPv4 or IPv6:
 */
extern void*
get_inaddr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/*
 * return socket connection from addrinfo
 */
extern int
soconnect(struct addrinfo *ad)
{
	int sock_fd = socket(ad->ai_family, ad->ai_socktype, ad->ai_protocol);

	if(sock_fd < 0)
	{
		perror("libsock: soconnect socket");
		return sock_fd;
	}

	if(connect(sock_fd, ad->ai_addr, ad->ai_addrlen) == -1)
	{
		perror("libsock: soconnect connect");
		if(close(sock_fd) != 0)
			perror("libsock: soconnect close");
		return -1;
	}

	return sock_fd;
}

/*
 * return socket binding from addrinfo
 */
extern int
sobind(struct addrinfo *ad)
{
	int sock_fd = socket(ad->ai_family, ad->ai_socktype, ad->ai_protocol);

	if(sock_fd < 0)
	{
		perror("libsock: sobind socket");
		return sock_fd;
	}

	if(bind(sock_fd, ad->ai_addr, ad->ai_addrlen) == -1)
	{
		perror("libsock: sobind bind");
		if(close(sock_fd) != 0)
			perror("libsock: sobind close");
		return -1;
	}

	return sock_fd;
}
