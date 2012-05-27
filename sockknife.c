#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "libsocks.h"

#define PROG "sockknife"

void usage(){
	printf("%s [options] address port\n", PROG);
	puts(""
	    );
}

int main(int argc, const char *argv[])
{
	char *addr = ADDR,
	     *port = PORT;
	int sockaddr = AF_UNSPEC,
	    socktype = SOCK_STREAM,
	    trans;

	// Prime the iteration
	argv++; argc--;

	while(argc > 0 && argv[0][0] == '-'){
		switch(argv[0][1]){
			case '4':
				// inet
				sockaddr = AF_INET;
				break;
			case '6':
				// inet6
				sockaddr = AF_INET6;
				break;
			case 'r':
				// receive
				trans = 0;
				break;
			case 't':
				// transmit
				trans = 1;
				break;
			case 'u':
				// udp
				socktype = SOCK_DGRAM;
				break;
			case default:
				//usage
				usage();
				break;
		}
		argv++;
		argc--;
	}

	if (argc != 1 && argc != 2) {
		usage();
		exit(1);
	}
	addr = ++argv;
	port = ++argv;

	int apperr;
	struct addrinfo hints,
	                *servinfo;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = sockaddr;
	hints.ai_socktype = socktype;
	hints.ai_flags = AI_PASSIVE;

	apperr = getaddrinfo(addr, port, &hints, &servinfo);
	if(apperr != 0){
		printf("getaddrinfo:Error %d:%s\n", apperr, gai_strerror(apperr));
	}

	struct addrinfo foo = servinfo[0];
	while(foo != NULL){
		sock_fd = socket(foo.ai_family, foo.ai_socktype, foo.ai_protocol);
		if(sock_fd < 0){
			perror("socket");
		}

		apperr = bind(sock_fd, foo.ai_addr, foo.ai_addrlen);
		if(apperr == -1){
			perror("bind");
		}
		foo = foo->ai_next;
	}

	if(sock_fd == NULL){
		perror("socket descriptor missing");
	}

	apperr = connect(sock_fd, foo.ai_addr, foo.ai_addrlen);
	if(err != 0){
		perror("connect");
	}
}
