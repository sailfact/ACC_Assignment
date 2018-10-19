#include	"acc.h"
#include 	"clientlist.h"
#include    "wrappthread.h"
#include    "wrapunix.h"
#include    "wraplib.h"
#include    "wrapstdio.h"
#include    "writen.h"
#include    "readline.h"
#include    "wrapsock.h"
#include    "tcp_listen.h"

void mail_srv(int);
int check_command_one(int, char *);
int check_command_two(int, char *, char *);
int check_command_three(int, char *, char *, char *);
void cmd_make(int, char *);
void cmd_read(int, char *, int);
void cmd_delete(int, char *, int);
void cmd_send(int, char *);
void cmd_get_mailbox(int, char *);
void cmd_quit(int);
void cmd_list(int);
int add_client(char *, int, char *);
int make_mailbox(char *);
void thread_make(int);
void * thread_main(void *);

struct mailbox_info {
    int                 email_id;           /* client id */
    char                sender_name[20];    /* senders name */
    struct tm           *time;              /* time sent */
    int                 status;             /* mail status */
};

struct email_list {
    struct mailbox_info email;
    struct mailbox_info *next_email;
};


typedef struct {
    pthread_t       thread_tid;     /* thread ID */
    long            thread_count;   /* # connections handled */
} Thread;

Thread *tptr;
#define MAXNCLI 32      /* the maximum amount of clients for this program!!! */
int                 clifd[MAXNCLI], iget, iput;
static int          nthreads;
struct email_list   *mail_head = NULL;
pthread_mutex_t     clifd_mutex;
pthread_cond_t      clifd_cond;
pthread_mutex_t     clifd_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t      clifd_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t     clilist_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t      clilist_cond = PTHREAD_COND_INITIALIZER;