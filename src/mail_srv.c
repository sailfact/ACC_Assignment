#include	"acc.h"

int check_command(char *arg1);
int check_command(char *arg1, char *arg2):
int check_command(char *arg1, char *arg2, char *arg3);

void mail_srv(int sockfd)
{
	char		arg1[50], arg2[50], arg3[50];
	ssize_t		n;
	char		line[MAXLINE];
    int scans;
	for ( ; ; ) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */
        scans = sscanf(line, "%s %s %s", arg1, arg2, arg2);
        switch (scans) {
            case 3:
                check_command(arg1, arg2, arg3);
                break;
            case 2:
                check_command(arg1, arg2, arg3);
                break;
            case 1:
                check_command(arg1);
                break;
            default:
			    snprintf(line, sizeof(line), "input error\n");
        }

		n = strlen(line);
		Writen(sockfd, line, n);
	}
}

int check_command(char *arg1) {

}

int check_command(char *arg1, char *arg2) {

}

int check_command(char *arg1, char *arg2, char *arg3) {

}



