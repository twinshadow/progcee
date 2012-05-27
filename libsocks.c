#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "libsocks.h"

/*
 * get sockaddr, IPv4 or IPv6:
 */
extern void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/*
 * return socket connection from addrinfo
 */
extern int soconnect(struct addrinfo *ad){
	int sock_fd = socket(ad->ai_family, ad->ai_socktype, ad->ai_protocol);
	if(sock_fd < 0){
		return -1;
	}
	else{
		if(connect(sock_fd, ad->ai_addr, ad->ai_addrlen) == -1){
			return -1;
		}
	}
	return sock_fd;
}

/*
 * return socket bind from addrinfo
 */
extern int sobind(struct addrinfo *ad){
	int sock_fd = socket(ad->ai_family, ad->ai_socktype, ad->ai_protocol);
	if(sock_fd < 0){
		return -1;
	}
	else{
		if(bind(sock_fd, ad->ai_addr, ad->ai_addrlen) == -1){
			return -1;
		}
	}
	return sock_fd;
}

