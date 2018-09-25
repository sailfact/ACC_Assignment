#include	"acc.h"

static int nthreads;
pthread_mutex_t clifd_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t clifd_cond = PTHREAD_COND_INITIALIZER;

static struct client_list *head = NULL;
static struct client_list *current = NULL;

int main(int argc, char **argv) {
	int 				i, listenfd, connfd;
	void				sig_int(int), thread_make(int);
	socklen_t			addrlen, clilen;
	struct sockaddr* 	cliaddr;

	if (argc == 3)
		listenfd = Tcp_listen(NULL, argv[1], &addrlen);
	else if (argc == 4)
		listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
	else
		err_quit("usage: mess [ <host> ] <port#> <#threads>");
	
	cliaddr = Malloc(addrlen);

	nthreads = atoi(argv[argc - 1]);
	tptr = Calloc(nthreads, sizeof(Thread));
	iget = iput = 0;

	/* create all the threads */
	
	for(i = 0; i < nthreads; i++) {
		thread_make(i);		/* only main thread returns */
	}
	
	while (1) {
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

void thread_make(int i) {
	void 	*thread_main(void *);
	Pthread_create(&tptr[i].thread_tid, NULL, &thread_main, (void *) i);
	return;		/* main thread returns */
}

void * thread_main(void *arg) {
	int 	connfd;
	void 	str_echo(int);

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

			str_echo(connfd);
			Close(connfd);
	}
}