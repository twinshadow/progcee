#ifndef TWINSHADOW_NET_H
#define TWINSHADOW_NET_H

#define INADDR(X) {(X->sa_family == AF_INET) ? \
			(((struct sockaddr_in*)X)->sin_addr) : \
			(((struct sockaddr_in6*)X)->sin6_addr)}

int soconnect(struct addrinfo *ad);
int sobind(struct addrinfo *ad);
struct addrinfo* get_addr(const char *address,
			  const char *port,
			  const int family,
			  const int socktype,
			  const int flags,
			  const int proto);

#endif /* TWINSHADOW_NET_H */

