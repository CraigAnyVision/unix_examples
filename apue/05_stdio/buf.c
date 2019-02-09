#include <stdio.h>
#include <stdlib.h>

void pr_stdio(const char *, FILE *);

int is_unbuffered(FILE *);

int is_line_buffered(FILE *);

int buffer_size(FILE *);

int main(void)
{
	FILE *fp;

	fputs("enter any character: ", stdout);

	if (getchar() == EOF)
	{
		fputs("getchar error", stderr);
		exit(1);
	}

	fputs("one line to standard error\n", stderr);

	pr_stdio("stdin", stdin);
	pr_stdio("stdout", stdout);
	pr_stdio("stderr", stderr);

	if ((fp = fopen("/etc/passwd", "r")) == NULL)
	{
		fputs("fopen error", stderr);
		exit(1);
	}

	if (getc(fp) == EOF)
	{
		fputs("getc error", stderr);
		exit(1);
	}

	pr_stdio("/etc/passwd", fp);

	exit(0);
}

void pr_stdio(const char *name, FILE *fp)
{
	printf("stream = %s, ", name);

	if (is_unbuffered(fp))
		printf("unbuffered");
	else if (is_line_buffered(fp))
		printf("line buffered");
	else
		printf("fully buffered");

	printf(", buffer size = %d\n", buffer_size(fp));
}

/*
 * The following is non-portable.
 */

int is_unbuffered(FILE *fp)
{
	return (fp->_flags & _IO_UNBUFFERED);
}

int is_line_buffered(FILE *fp)
{
	return (fp->_flags & _IO_LINE_BUF);
}

int buffer_size(FILE *fp)
{
	return (int)(fp->_IO_buf_end - fp->_IO_buf_base);
}
