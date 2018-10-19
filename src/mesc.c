#include	"mesc.h"

int main(int argc, char **argv) 
{
	int			        sockfd;
	struct sockaddr_in	servaddr;

	if (argc != 3)
		err_quit("usage: mesc.out <hostname/IPaddress> <service/port#>");

	sockfd = Tcp_connect(argv[1], argv[2]);//Socket(AF_INET, SOCK_STREAM, 0);

	mail_cli(stdin, sockfd);		/* do it all */

	exit(0);
}

void mail_cli (FILE *fp, int sockfd)  
{
    char	sendline[MAXLINE], recvline[MAXLINE], arg[20];
    printf("\nMESC>");
	while ((void *) Fgets(sendline, MAXLINE, fp) != NULL) 
	{
		sscanf(sendline, "%s", arg);
		
		

		Writen(sockfd, sendline, strlen(sendline));
		
		if (strcmp(arg, "send") == 0)
		{
			sendMsg(fp,sockfd);
			printf("finished sending msg\n");
		}
		
		if (Read(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		Fputs(recvline, stdout);
		if (strcmp(recvline, "Bye\n") == 0)
			return;
		
        printf("\nMESC>");
	}
}

void sendMsg(FILE *fp, int sockfd)
{
	sleep(1);	// to make sure server is ready to receive the message
	char	message[MAXLINE];
	printf("\nEnter MSG>>");
	while ((void *) Fgets(message, MAXLINE, fp) != NULL)
	{
		Writen(sockfd, message, strlen(message));
		return;
	}
}
