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
void cmd_make(int sockfd, char *name);
void cmd_read(int sockfd, char *name, int id);
void cmd_delete(int sockfd, char *name, int id);
void cmd_get_client_list(int sockfd);
void cmd_get_mailbox(int sockfd, char *name);
void cmd_quit(int sockfd);
int add_client(char *address, int port, char *name);
void make_mailbox(char * filename);
void thread_make(int i);
void * thread_main(void *arg);


static int nthreads;
pthread_mutex_t clifd_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t clifd_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t clilist_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t clilist_cond = PTHREAD_COND_INITIALIZER;