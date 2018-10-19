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
void cmd_get_mailbox(int, char *);
int add_client(char *, int, char *);
int make_mailbox(char *);
void thread_make(int);
void * thread_main(void *);


static int nthreads;
pthread_mutex_t clifd_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t clifd_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t clilist_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t clilist_cond = PTHREAD_COND_INITIALIZER;