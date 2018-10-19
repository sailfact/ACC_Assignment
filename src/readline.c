/* include readline */
#include	"readline.h"

static ssize_t my_read(int fd, char *ptr)
{
	static int	read_cnt = 0;
	static char	*read_ptr;
	static char	read_buf[MAXLINE];

	if (read_cnt <= 0) 
	{
		while ((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) 
		{
			if (errno == EINTR)
				continue;
			else
				return(-1);
		}
		if (read_cnt == 0)
			return(0);
		
		read_ptr = read_buf;
	}

	read_cnt--;
	*ptr = *read_ptr++;
	return(1);
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
	int		n, rc;
	char	c, *ptr;

	ptr = vptr;
	for (n = 1; n < maxlen; n++) 
	{
		if ( (rc = my_read(fd, &c)) == 1) 
		{
			*ptr++ = c;
			if (c == '\n')
				break;	/* newline is stored, like fgets() */
		} 
		else if (rc == 0) 
		{
			if (n == 1)
				return(0);	/* EOF, no data read */
			else
				break;		/* EOF, some data was read */
		} 
		else
			return(-1);		/* error, errno set by read() */
	}

	*ptr = 0;	/* null terminate like fgets() */
	return(n);
}
/* end readline */

ssize_t Readline(int fd, void *ptr, size_t maxlen)
{
	ssize_t		n;

	if ( (n = readline(fd, ptr, maxlen)) < 0)
		err_sys("readline error");
	return(n);
}

ssize_t readn(int fd, void *vptr, size_t n)
{
	size_t  nleft;
	ssize_t nread;
	char 	*ptr;
	ptr = vptr;
	nleft = n;
	while (nleft > 0)
	{
		if ((nread = read(fd, ptr, nleft)) < 0)
		{
			if (errno == EINTR)	// if interrupted
				nread = 0;	// call read again
			else 
				return (-1);
		}
		else if (nread == 0)
			break;	//EOF
		nleft -= nread;
		ptr += nread;
	}
	return (n-nleft); // returns >= 0
}

ssize_t Readn(int fd, void *ptr, size_t nbytes)
{
	ssize_t n;
	if ((n =  readn(fd, ptr, nbytes)) < 0)
		err_sys("readn error");
	return (n);
}
