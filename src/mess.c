#include	"acc.h"
#include 	"clientlist.h"

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


static int nthreads;
pthread_mutex_t clifd_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t clifd_cond = PTHREAD_COND_INITIALIZER;

int main(int argc, char **argv) 
{
	int 				i, listenfd, connfd;
	void				sig_int(int), thread_make(int);
	socklen_t			addrlen, clilen;
	struct sockaddr* 	cliaddr;

	if (argc == 3)
		listenfd = Tcp_listen(NULL, argv[2], &addrlen);
	else
		err_quit("usage: mess <#threads> <#threads>");
	
	cliaddr = Malloc(addrlen);

	nthreads = atoi(argv[1]);
	tptr = Calloc(nthreads, sizeof(Thread));
	iget = iput = 0;

	/* create all the threads */
	
	for(i = 0; i < nthreads; i++)
		thread_make(i);		/* only main thread returns */
	
	while (1) 
	{
		clilen = addrlen;
		connfd = Accept(listenfd, cliaddr, &clilen);

		Pthread_mutex_lock(&clifd_mutex);
		clifd[iput] = connfd;
		if (++iput == MAXNCLI)
			iput = 0;
		if (iput == iget)
			err_quit("iput = iget = %d", iput);
		Pthread_cond_signal(&clifd_cond);
		Pthread_mutex_unlock(&clifd_mutex);
	}
}

void thread_make(int i)
{
	void 	*thread_main(void *);
	Pthread_create(&tptr[i].thread_tid, NULL, &thread_main, (void *) i);
	return;		/* main thread returns */
}

void * thread_main(void *arg) 
{
	int 	connfd;
	void 	mail_srv(int);

	printf("thread %d starting\n", (int)arg);
	while (1) {
		Pthread_mutex_lock(&clifd_mutex);
		while (iget == iput)
			Pthread_cond_wait(&clifd_cond, &clifd_mutex);
		connfd = clifd[iget]; 	/* connected socket to service */
		if (++iget == MAXNCLI)
			iget = 0;
			Pthread_mutex_unlock(&clifd_mutex);
			tptr[(int)arg].thread_count++;
			mail_srv(connfd);
			Close(connfd);
	}
}

void mail_srv(int sockfd)
{
	char		arg1[20], arg2[20], arg3[20];
	ssize_t		n;
	char		line[MAXLINE];
    int scans;
	for ( ; ; ) 
    {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */
        scans = sscanf(line, "%s %s %s", arg1, arg2, arg2);
		printf("commands %d\n\targ1 = %s\n\targ2 = %s\n\targ3 = %s\n",scans, arg1, arg2, arg3);
        switch (scans) 
        {
            case 1:
                check_command_one(sockfd, arg1);
                break;
			case 2:
                check_command_two(sockfd, arg1, arg2);
                break;
			case 3:
                check_command_three(sockfd, arg1, arg2, arg3);
                break;            
            default:
			    snprintf(line, sizeof(line), "input error\n");
        }

		n = strlen(line);
		Writen(sockfd, line, n);
	}
}
int check_command_one(int sockfd, char *arg) 
{
	int len = strlen(arg);
    char str[sizeof(arg)+1];
    for(int i = 0; i < len; i++)
            str[i] = tolower(arg[i]);

    if (strcmp(str, "quit") == 0)
    {
		printf("quit\n");
		cmd_quit(sockfd);
	}
    else if (strcmp(str, "get_client_list") == 0)
    {
		printf("get_client_list\n");
		cmd_get_client_list(sockfd);
	}

	return 0;
}

int check_command_two(int sockfd, char *arg1, char *arg2) 
{
	int len = strlen(arg1);
    char str[sizeof(arg1)+1];
    for(int i = 0; i < len; i++)
            str[i] = tolower(arg1[i]);

    if (strcmp(str, "make") == 0)
 	{
	    printf("make %s\n", arg2);
		cmd_make(sockfd, arg2);
	}
    else if (strcmp(str, "get_mailbox") == 0)
	{
        printf("get_mailbox %s\n", arg2);
		cmd_get_mailbox(sockfd, arg2);
	}

    return 0;
}

int check_command_three(int sockfd, char *arg1, char *arg2, char *arg3) 
{
	printf("cmd%s name%s id%s\n", arg1, arg2, arg3);
	int len = strlen(arg1);
    char str[sizeof(arg1)+1];
    for(int i = 0; i < len; i++)
            str[i] = tolower(arg1[i]);
        
    if (strcmp(str, "read") == 0)
    {    
		printf("read %s %s\n", arg2, arg3);
		cmd_read(sockfd, arg2, atoi(arg3));
	}
    else if (strcmp(str, "delete") == 0)
    {
	    printf("delete %s %s\n", arg2, arg3);
		cmd_delete(sockfd, arg2, atoi(arg3));
	}
    return 0;
}

void cmd_make(int sockfd, char *name)
{

}

void cmd_read(int sockfd, char *name, int id)
{

}

void cmd_delete(int sockfd, char *name, int id)
{

}

void cmd_get_client_list(int sockfd)
{
	
}

void cmd_get_mailbox(int sockfd, char *name)
{

}

void cmd_quit(int sockfd)
{
	printf("quittig...\n");
	char line[MAXLINE];
	snprintf(line, sizeof(line), "input error\n");
	Writen(sockfd, line, sizeof(line));
	Close(sockfd);
}