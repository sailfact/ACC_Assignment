#include	"acc.h"
#include 	"error.h"

static ssize_t my_read(int fd, char *ptr);
ssize_t readline(int fd, void *vptr, size_t maxlen);
ssize_t Readline(int fd, void *ptr, size_t maxlen);
ssize_t readn(int fd, void *vptr, size_t n);
ssize_t Readn(int fd, void *ptr, size_t nbytes);