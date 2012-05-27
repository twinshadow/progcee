#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "libsocks.h"

#define NAME "socks_tx"
#define PORT "1337"
#define ADDR NULL
#define PROMPT "> "
#define MAXDATASIZE 100

void run(){
}

int main(int argc, const char *argv[])
{
	char *mbuf,
	     raddr[INET6_ADDRSTRLEN],
	     rbuf[MAXDATASIZE];
	int echeck,
	    sock_fd;
	struct addrinfo hint,
			*adr;

	memset(&hint, 0, sizeof hint);
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;

	echeck = getaddrinfo(ADDR, PORT, &hint, &adr);
	if(echeck != 0){
		perror("getaddrinfo");
		perror(gai_strerror(echeck));
	}

	while((sock_fd = soconnect(adr)) == -1){
		if(adr->ai_next == NULL){
			sock_fd = -1;
			break;
		}
		adr++;
	}

	if(sock_fd < 0){
		fputs("No more addresses to use, exiting\n", stderr);
		exit(2);
	}

	inet_ntop(adr->ai_family, get_in_addr((struct sockaddr *)adr->ai_addr), raddr, sizeof raddr);
	freeaddrinfo(adr);

	char prompt[strlen(raddr) + strlen(PROMPT)];
	if(sprintf(prompt, "%s%s", raddr, PROMPT) < 0){
		perror("sprintf");
	}

	for(;;){
		mbuf = readline(prompt);
		if(send(sock_fd, mbuf, sizeof mbuf, 0) == -1){
			perror("send");
		}
		if(recv(sock_fd, rbuf, MAXDATASIZE - 1, 0) == -1){
			perror("recv");
		}
	}

	close(sock_fd);
	return 0;
}
