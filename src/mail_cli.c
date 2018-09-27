#include "acc.h"

void mail_cli (FILE *fp, int sockfd) {
    char	sendline[MAXLINE], recvline[MAXLINE];
    printf("\nMESC>");
	while ((void *) Fgets(sendline, MAXLINE, fp) != NULL) {
		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		Fputs(recvline, stdout);
        printf("\nMESC>");
	}
}