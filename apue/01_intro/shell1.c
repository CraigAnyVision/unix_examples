#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 4096

int main(void)
{
	char buf[MAX_LINE_LENGTH];

	printf("%% ");

	while (fgets(buf, MAX_LINE_LENGTH, stdin) != NULL)
	{
		if (buf[strlen(buf) - 1] == '\n')
		{
			// replace newline with null
			buf[strlen(buf) - 1] = 0;
		}

		if (buf[0] == 0)
		{
			printf("%% ");
			continue;
		}

		pid_t pid = fork();

		if (pid < 0)
		{
			printf("fork error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			// child
			execlp(buf, buf, (char *)0);
			printf("couldn't execute: %s\n", buf);
			// 127: command not found
			exit(127);
		}

		int status;

		// parent
		if ((pid = waitpid(pid, &status, 0)) < 0)
		{
			printf("waitpid error");
			exit(EXIT_FAILURE);
		}

		printf("%% ");
	}
}
