#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 4096

int main(void)
{
	char name[L_tmpnam], line[MAX_LINE];
	FILE *fp;

	printf("%s\n", tmpnam(NULL));  // first temp name (tmpnam is dangerous, use mkstemp)

	tmpnam(name);  // second temp name

	printf("%s\n", name);

	if ((fp = tmpfile()) == NULL)  // create temp file
	{
		fputs("tmpfile error", stderr);
		exit(1);
	}

	fputs("one line of output\n", fp);  // write to temp file
	rewind(fp);                         // then read it back

	if (fgets(line, sizeof(line), fp) == NULL)
	{
		fputs("fgets error", stderr);
		exit(1);
	}

	fputs(line, stdout);  // print the line we wrote

	exit(0);
}
