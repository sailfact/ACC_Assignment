#include "acc.h"

int check_input(char *sendline);
void help();

void mail_cli (FILE *fp, int sockfd) {
    char	sendline[MAXLINE], recvline[MAXLINE];
    help();
    printf("\nMESC>");
	while ((void *) Fgets(sendline, MAXLINE, fp) != NULL) {
		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		Fputs(recvline, stdout);
        printf("\nMESC>");
	}
}


void help() {
    printf("MES Commands\n\nmake <client name>\nget_client_list\nsend <receiver name>\nget_mailbox <client name>\nread <client name> <mail id>\ndelete <client name> <mail id>\nquit\n");
}