#include	"acc.h"

int main(int argc, char **argv) 
{
	int			        sockfd;
	struct sockaddr_in	servaddr;

	if (argc != 3)
		err_quit("usage: tcpcli <IPaddress> <port number>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	mail_cli(stdin, sockfd);		/* do it all */

	exit(0);
}

void mail_cli (FILE *fp, int sockfd)  
{
    char	sendline[MAXLINE], recvline[MAXLINE];
    printf("\nMESC>");
	while ((void *) Fgets(sendline, MAXLINE, fp) != NULL) 
	{
		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		Fputs(recvline, stdout);
		if (strcmp(recvline, "Bye\n") == 0)
			return;
		
        printf("\nMESC>");
	}
}
