#include	"acc.h"
#include    "error.h"

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);

void Bind(int fd, const struct sockaddr *sa, socklen_t salen);

void Connect(int fd, const struct sockaddr *sa, socklen_t salen);

void Getpeername(int fd, struct sockaddr *sa, socklen_t *salenptr);

void Getsockname(int fd, struct sockaddr *sa, socklen_t *salenptr);

void Getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlenptr);

int Isfdtype(int fd, int fdtype);

/* include Listen */
void Listen(int fd, int backlog);
/* end Listen */

#ifdef	HAVE_POLL
int Poll(struct pollfd *fdarray, unsigned long nfds, int timeout);
#endif

ssize_t Recv(int fd, void *ptr, size_t nbytes, int flags);

ssize_t Recvfrom(int fd, void *ptr, size_t nbytes, int flags, struct sockaddr *sa, socklen_t *salenptr);

ssize_t Recvmsg(int fd, struct msghdr *msg, int flags);

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

void Send(int fd, const void *ptr, size_t nbytes, int flags);

void Sendto(int fd, const void *ptr, size_t nbytes, int flags, const struct sockaddr *sa, socklen_t salen);

void Sendmsg(int fd, const struct msghdr *msg, int flags);

void Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen);

void Shutdown(int fd, int how);

/*
int Sockatmark(int fd);
*/

/* include Socket */
int Socket(int family, int type, int protocol);
/* end Socket */

void Socketpair(int family, int type, int protocol, int *fd);