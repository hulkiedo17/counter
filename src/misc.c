#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "../include/misc.h"

void fail(FILE* out, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(out, fmt, ap);
	va_end(ap);
}

char* getcw(void)
{
	char *path_ptr = NULL;
	size_t len;
	char buffer[BUFSIZ];

	if(getcwd(buffer, BUFSIZ) == NULL) {
		fail(stderr, "getcw(): error taking the path to the current directory (getcwd() failed)\n");
		return NULL;
	}

	len = strlen(buffer) + 1;
	path_ptr = malloc(sizeof(char) * len);
	if(path_ptr == NULL) {
		fail(stderr, "getcw(): memory allocation error (malloc() failed)\n");
		return NULL;
	}

	strncpy(path_ptr, buffer, len);

	return path_ptr;
}
