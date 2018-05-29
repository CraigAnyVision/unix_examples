#define BUFLEN 512
#define NPACK 10
#define PORT 9930

void exit_error(const char *const s)
{
	perror(s);
	exit(1);
}
