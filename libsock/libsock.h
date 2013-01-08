#ifndef LIBSOCK_H
#define LIBSOCK_H

#include <sys/socket.h>
#include <sys/types.h>
extern struct addrinfo* get_addr(char *address, char *port, int family, int socktype, int flags, int proto);
extern void *get_inaddr(struct sockaddr *sa);
extern int sobind(struct addrinfo *ad);
extern int soconnect(struct addrinfo *ad);

#endif /* LIBSOCK_H */
