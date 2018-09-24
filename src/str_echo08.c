#include	"acc.h"

void
str_echo(int sockfd)
{
	long		arg1, arg2;
	ssize_t		n;
	char		line[MAXLINE];
	char 		operator;

	for ( ; ; ) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */

		if (sscanf(line, "%ld %c %ld", &arg1, &operator, &arg2) == 3) {
			switch (operator) {
				case '+':
					snprintf(line, sizeof(line), "%ld\n", arg1 + arg2);
					break;
				case '-':
					snprintf(line, sizeof(line), "%ld\n", arg1 - arg2);
					break;
				case '*':
					snprintf(line, sizeof(line), "%ld\n", arg1 * arg2);
					break;
				case '/':
					snprintf(line, sizeof(line), "%ld\n", arg1 / arg2);
					break;
				default:
					snprintf(line, sizeof(line), "input error '%c'\n", operator);
			}
		}
		else
			snprintf(line, sizeof(line), "input error\n");

		n = strlen(line);
		Writen(sockfd, line, n);
	}
}
