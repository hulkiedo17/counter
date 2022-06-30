#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <assert.h>
#include <stdbool.h>

void fail(FILE* out, const char* fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(out, fmt, ap);
	va_end(ap);

	exit(EXIT_FAILURE);
}

char* duplicate_string(const char* string)
{
	assert(string != NULL);

	size_t length = strlen(string) + 1;

	char* dup_string = calloc(length, sizeof(char));
	if(dup_string == NULL)
		fail(stderr, "error: allocation failed - %s\n", __func__);

	memcpy(dup_string, string, length);

	return dup_string;
}

char* concatenate_path_and_name(const char* path, const char* filename)
{
	assert(path != NULL);
	assert(filename != NULL);

	size_t path_len = 0;
	size_t filename_len = 0;
	char* full_path = NULL;

	path_len = strlen(path);
	filename_len = strlen(filename);

	if(path[path_len - 1] != '/')
	{
		full_path = calloc((path_len + filename_len + 1) + 1, sizeof(char));
		if(full_path == NULL)
			fail(stderr, "error: allocation failed - %s\n", __func__);

		strncpy(full_path, path, path_len);
		full_path[path_len] = '/';
		strncpy(full_path + path_len + 1, filename, filename_len);
	}
	else
	{
		full_path = calloc((path_len + filename_len) + 1, sizeof(char));
		if(full_path == NULL)
			fail(stderr, "error: allocation failed - %s\n", __func__);

		strncpy(full_path, path, path_len);
		strncpy(full_path + path_len, filename, filename_len);
	}

	return full_path;
}

char* get_work_dir(void)
{
	char* path = NULL;

	if((path = getcwd(NULL, 0)) == NULL)
		fail(stderr, "error: getcwd failed - %s\n", __func__);

	return path;
}

void help(void)
{
	fprintf(stdout, "Usage: counter [options...]\n");
	fprintf(stdout, "options:\n");
	fprintf(stdout, "\t-h        - prints this help message\n");
	fprintf(stdout, "\t-v        - prints files that counted\n");
	fprintf(stdout, "\t-p [path] - specifying another directory for counting lines in files\n");
	fprintf(stdout, "\t-f [file] - specifying file to count lines\n");
	fprintf(stdout, "\t-D [dir]  - ignore specified directory\n");
	fprintf(stdout, "\t-r        - do not use files in nested directories\n");
	fprintf(stdout, "\t-s        - do not count empty lines in files\n");
	fprintf(stdout, "\t-z        - do not show empty files\n");
	fprintf(stdout, "\t-t        - do not show total lines count of files\n");
	fprintf(stdout, "\t-e        - do not use global environment variables\n");

	fprintf(stdout, "\n");
}
