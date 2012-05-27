#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "libsocks.h"

#define NAME "socks_rx"
#define BACKLOG 32
#define PORT "1337"
#define ADDR NULL
#define MAXDATASIZE 100

void run(){
}

int main(int argc, const char *argv[])
{
	char mbuf[MAXDATASIZE],
	     raddr[INET6_ADDRSTRLEN];
	int echeck,
	    conn_fd,
	    sock_fd;
	struct addrinfo hint,
			*adr;
	struct sockaddr_storage rc;
	socklen_t rclen;

	memset(&hint, 0, sizeof hint);
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags = AI_PASSIVE;

	echeck = getaddrinfo(ADDR, PORT, &hint, &adr);
	if(echeck != 0){
		perror("getaddrinfo");
		perror(gai_strerror(echeck));
	}

	for(;;){
		if((sock_fd = sobind(adr)) == -1){
			if(adr->ai_next == NULL){
				sock_fd = -1;
				break;
			}
			adr++;
		}
		break;
	}

	if(sock_fd < 0){
		perror("No socket bound, exiting");
		exit(2);
	}

	freeaddrinfo(adr);

	if(listen(sock_fd, BACKLOG) != 0){
		perror("listen");
	}

	for(;;){
		rclen = sizeof rc;
		conn_fd = accept(sock_fd, (struct sockaddr *)&rc, &rclen);
		if(conn_fd < 0){
			perror("accept");
			continue;
		}

		inet_ntop(rc.ss_family, get_in_addr((struct sockaddr *)&rc), raddr, sizeof raddr);
		printf("Connection from %s established on socket %d\n", raddr, conn_fd);

		if(!fork()){
			close(sock_fd);
			if(recv(conn_fd, mbuf, MAXDATASIZE - 1, 0) == -1){
				perror("recieve");
			}
			close(conn_fd);
			exit(0);
		}

		close(conn_fd);
	}

	close(sock_fd);
	close(conn_fd);
	return 0;
}
