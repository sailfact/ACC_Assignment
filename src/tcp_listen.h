#include	"acc.h"
#include    "error.h"
#include    "wrapsock.h"
#include    "wrapunix.h"

int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp);
int Tcp_listen(const char *host, const char *serv, socklen_t *addrlenp);