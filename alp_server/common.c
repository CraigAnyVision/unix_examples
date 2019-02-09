#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

const char *program_name;
int verbose;

void *xmalloc(size_t size)
{
	void *ptr = malloc(size);

	if (ptr == NULL)
		abort();
	else
		return ptr;
}

void *xrealloc(void *ptr, size_t size)
{
	ptr = realloc(ptr, size);

	if (ptr == NULL)
		abort();
	else
		return ptr;
}

char *xstrdup(const char *s)
{
	char *copy = strdup(s);

	if (copy == NULL)
		abort();
	else
		return copy;
}

void system_error(const char *operation)
{
	error(operation, strerror(errno));
}

void error(const char *cause, const char *message)
{
	fprintf(stderr, "%s: error: (%s) %s\n", program_name, cause, message);
	exit(1);
}

char *get_self_executable_directory()
{
	char link_target[1024];

	// Read the target of the symbolic link /proc/self/exe
	ssize_t rval = readlink("/proc/self/exe", link_target, sizeof(link_target));

	if (rval == -1)
		abort();
	else
		link_target[rval] = '\0';  // NUL-terminate the target

	// We want to trim the name of the executable file, to obtain the
	// directory that contains it. Find the rightmost slash
	char *last_slash = strrchr(link_target, '/');

	if (last_slash == NULL || last_slash == link_target)
		abort();

	// Allocate a buffer to hold the resulting path
	size_t result_length = last_slash - link_target;
	char *result = (char *)xmalloc(result_length + 1);

	// Copy the result
	strncpy(result, link_target, result_length);
	result[result_length] = '\0';
	return result;
}
