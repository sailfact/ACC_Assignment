#include	"mess.h"

int main(int argc, char **argv) 
{
	int 				i, listenfd, connfd;
	void				sig_int(int), thread_make(int);
	socklen_t			addrlen, clilen;
	struct sockaddr* 	cliaddr;

	if (argc == 3)
		listenfd = Tcp_listen(NULL, argv[2], &addrlen);
	else
		err_quit("usage: mess <#threads> <port#>");
	
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
	while (1)
    {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */

		if ((scans = sscanf(line, "%s %s %s", arg1, arg2, arg3)) < 4)
		{
			switch (scans) 
			{
				case 1:
					if (check_command_one(sockfd, arg1) < 0) 
						fprintf(stderr, "check cmd one failed : <%s>", arg1);
					break;
				case 2:
					if (check_command_two(sockfd, arg1, arg2) < 0) 
						fprintf(stderr, "check cmd two failed : <%s> <%s>", arg1, arg2);
					break;
				case 3:
					if (check_command_three(sockfd, arg1, arg2, arg3) < 0)
						fprintf(stderr, "check cmd one failed : <%s> <%s> <%s>", arg1, arg2, arg3);
					break;    
				default:     
					snprintf(line, sizeof(line), "input error\n");   
					n = strlen(line);
					Writen(sockfd, line, n);
			}
		} 
		else
		{
			snprintf(line, sizeof(line), "input error\n");
			n = strlen(line);
			Writen(sockfd, line, n);
		}
		bzero(line, MAXLINE);
	}
}

int check_command_one(int sockfd, char *arg) 
{
	ssize_t		n;
	char		line[MAXLINE];
	int len = strlen(arg);
    char str[sizeof(arg)];
    for(int i = 0; i < len; i++)
            str[i] = tolower(arg[i]);
	
	if (strcmp(str, "quit") == 0)
    {
		cmd_quit(sockfd);
	}
    else if (strcmp(str, "get_client_list") == 0)
    {
		cmd_list(sockfd);
	}
	else
	{
		snprintf(line, sizeof(line), "input error\n");
		n = strlen(line);
		Writen(sockfd, line, n);
	}
	bzero(line, MAXLINE);
	return 0;
}

int check_command_two(int sockfd, char *arg1, char *arg2) 
{
	int len = strlen(arg1);
    char str[sizeof(arg1)];
    for(int i = 0; i < len; i++)
        str[i] = tolower(arg1[i]);

    if (strcmp(str, "make") == 0)
 	{
		cmd_make(sockfd, arg2);
	}
    else if (strcmp(str, "mailbox") == 0)
	{
        cmd_mailbox(sockfd, arg2);
	}
	else if(strcmp(str, "send") == 0)
	{
		cmd_send(sockfd, arg2);
	}

    return 0;
}

int check_command_three(int sockfd, char *arg1, char *arg2, char *arg3) 
{
	int len = strlen(arg1);
    char str[sizeof(arg1)];
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
	struct sockaddr_in 	cliaddr;
	socklen_t 			len;
	char 				buff[MAXLINE];
	ssize_t				n;
	char				line[MAXLINE];

	const char 			*ptr;
	len = sizeof(cliaddr);
	Getpeername(sockfd, (SA *) &cliaddr, &len);
	Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff));
	add_client(buff, ntohs(cliaddr.sin_port), name);
	if (make_mailbox(name) == 0)
	{
		snprintf(line, sizeof(line), "Client %s added.\n", name);
	}
	else
	{
		snprintf(line, sizeof(line), "Client %s all ready exists.\n", name);
	}

	n = strlen(line);
	Writen(sockfd, line, n);
	bzero(line, MAXLINE);
}

int add_client(char *address, int port, char *name)
{
	char 			line[MAXLINE];
	time_t 			rawtime;
	struct 			tm *timeinfo;
	struct client 	newClient;
	time(&rawtime);
	strcpy(newClient.client_name, name);
	newClient.time_joined = localtime(&rawtime);
	strcpy(newClient.ip_address, address);
	newClient.ip_port = port;
	newClient.email_counter = 0;

	Pthread_mutex_lock(&clilist_mutex);
	insertFirst(newClient);
	Pthread_mutex_unlock(&clilist_mutex);

	return 0;
}

int make_mailbox(char * filename)
{
	struct stat st = {0};

	if (stat(filename, &st) == 0)
		return 1;
	else
		mkdir(filename, 0777);
	
	return 0;
}

void cmd_quit(int sockfd)
{
	char line[MAXLINE];
	snprintf(line, sizeof(line), "Bye\n");
	Writen(sockfd, line, strlen(line));
	bzero(line, MAXLINE);
}

void cmd_list(int sockfd)
{
	char line[MAXLINE];
	getList(line);
	Writen(sockfd, line, strlen(line));
	bzero(line, MAXLINE);
}

void cmd_read(int sockfd, char *name, int id)
{
	// send file /name/id
	char path[PATH_MAX], line[MAXLINE];
	snprintf(path, sizeof(path), "%s/%d", name, id);
	char * buffer = 0;
	long length;
	FILE * f = fopen (path, "rb");

	if (f)
	{
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = malloc (length);
		if (buffer)
		{
			fread (buffer, 1, length, f);
		}
		fclose (f);
	}

	if (buffer)
	{
		snprintf(line, sizeof(line), "%s", buffer);
	}
	else
	{
		snprintf(line, sizeof(line), "error retrieving file.\n");
	}
	
	Writen(sockfd, line, strlen(line));
	bzero(line, MAXLINE);
}

void cmd_delete(int sockfd, char *name, int id)
{
	// delete rile /name/id
	char path[PATH_MAX], line[MAXLINE];
	snprintf(path, sizeof(path), "%s/%d", name, id);

	if (remove(path))
	{
		snprintf(line, sizeof(line), "%s file deleted successfully.\n", path);
	}
  	else
  	{
		snprintf(line, sizeof(line), "Unable to delete the file\n");
  	}

	Writen(sockfd, line, strlen(line));
	bzero(line, MAXLINE);
}

void cmd_send(int sockfd, char *name)
{
	char message[MAXLINE], line[MAXLINE];
	ssize_t n;
	if (Readline(sockfd, message, MAXLINE) == 0)	// wait for the message
		return;		// other end closed

	printf("%s\n", message);
	snprintf(line, sizeof(line), "Message received\n");
	n = strlen(line);
	Writen(sockfd, line, n);
	bzero(line, MAXLINE);
}

void cmd_mailbox(int sockfd, char *name)
{
	char line[MAXLINE], buff[MAXLINE];
	char curdir[20];
	ssize_t n;
	struct dirent *de;
	DIR *dr = opendir(name);
	if (dr != NULL)
	{
		snprintf(line, sizeof(line), "name %s\n", name);
		while ((de = readdir(dr)) != NULL)
		{
			snprintf(buff, sizeof(buff), "%s\n", de->d_name);
			strncat(line, buff, sizeof(buff));
		}
	}
	else
		snprintf(line, sizeof(line), "Message received\n");
	closedir(dr);

	printf("%s", line);

	n = strlen(line);
	Writen(sockfd, line, n);
	bzero(line, MAXLINE);
}