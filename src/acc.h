#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/select.h>

#define	MAXLINE	4096
#define	LISTENQ	1024
#define	SERV_TCP_PORT	52001
#define TIMEOUT 20
#define	SA	struct sockaddr
#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))
typedef	void	Sigfunc(int);

enum status {
    Read,
    Unread
};

struct mailbox_info {
    int             email_id;           /* client id */
    char            sender_name[20];    /* senders name */
    int             time;               /* time sent */
    enum status     status;             /* mail status */
};

typedef struct {
    pthread     thread_tid;     /* thread ID */
    long        thread_count;   /* # connections handled */
} Thread;

Thread *tptr;
#define MAXNCLI 32 
int clifd[MAXNCLI], iget, iput;
pthread_mutex_t clifd_mutex;
pthread_cond_t clifd_cond;