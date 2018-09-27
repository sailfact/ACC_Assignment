#include	"acc.h"

int check_command(int argc, ...);

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

int check_command(int argc, ...) {
    va_list valist;
    char *args[argc];
    char *str;
    int  i = 0;

    va_start(valist, argc);

    for (i = 0; i < argc; i++) {
        strcpy(args[i], va_arg(valist, char *));
    }
    
    strcpy(str, args[0]);
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }

    if (strcmp(str, "make") == 0)
        printf("make");

    return 0;
}



