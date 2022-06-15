#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../include/misc.h"

const char* environment_dir_patterns = NULL;
const char* environment_file_patterns = NULL;

const char* ignore_directory = NULL;

static const char* const default_dir_patterns = ".|build|bin";
static const char* const default_file_patterns = ".c|.h|.sh|.txt|Makefile";

static bool check_pattern(const char* source, const char* pattern)
{
	char* dup_pattern = duplicate_string(pattern);
	char* token = NULL;

	token = strtok(dup_pattern, "|");
	while(token != NULL)
	{
		if(strstr(source, token) != NULL)
		{
			free(dup_pattern);
			return true;
		}

		token = strtok(NULL, "|");
	}

	free(dup_pattern);
	return false;
}

bool is_file(const char* path)
{
	assert(path != NULL);

	struct stat buf;

	if(path == NULL)
		fail(stderr, "error: the function argument was passed NULL value - %s\n", __func__);

	if(stat(path, &buf) == 0 && S_ISREG(buf.st_mode))
		return true;

	return false;
}

bool is_dir(const char* path)
{
	assert(path != NULL);

	struct stat buf;

	if(path == NULL)
		fail(stderr, "error: the function argument was passed NULL value - %s\n", __func__);

	if(stat(path, &buf) == 0 && S_ISDIR(buf.st_mode))
		return true;

	return false;
}

bool check_dir(const char* dir)
{
	assert(dir != NULL);

	if(dir == NULL)
		fail(stderr, "error: the function argument was passed NULL value - %s\n", __func__);

	if(ignore_directory != NULL && strcmp(dir, ignore_directory) == 0)
		return false;

	if(environment_dir_patterns != NULL)
		return !check_pattern(dir, environment_dir_patterns);

	return !check_pattern(dir, default_dir_patterns);
}

bool check_file(const char* file)
{
	assert(file != NULL);

	if(file == NULL)
		fail(stderr, "error: the function argument was passed NULL value - %s\n", __func__);

	if(environment_file_patterns != NULL)
		return check_pattern(file, environment_file_patterns);

	return check_pattern(file, default_file_patterns);
}
