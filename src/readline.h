#include	"acc.h"
#include 	"error.h"
#include    "wrappthread.h"
#include    "wrapunix.h"

typedef struct {
  int	 rl_cnt;			/* initialize to 0 */
  char	*rl_bufptr;			/* initialize to rl_buf */
  char	 rl_buf[MAXLINE];
} Rline;

static void readline_destructor(void *ptr);
static void readline_once(void);
static ssize_t my_read(Rline *tsd, int fd, char *ptr);
ssize_t readline(int fd, void *vptr, size_t maxlen);
ssize_t Readline(int fd, void *ptr, size_t maxlen);


