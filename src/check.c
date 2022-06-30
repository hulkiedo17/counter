#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libgen.h>
#include "../include/misc.h"

const char *environment_dir_patterns = NULL;
const char *environment_file_patterns = NULL;

char *ignore_directory = NULL;

static const char *const default_dir_patterns = ".|build|bin";
static const char *const default_file_patterns = ".c|.h|.sh|.txt|Makefile";

static bool check_pattern(const char *source, const char *pattern)
{
	assert(source != NULL);
	assert(pattern != NULL);

	char *dup_pattern = NULL;
	char *token = NULL;

	dup_pattern = str_dup(pattern);

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

bool is_file(const char *path)
{
	assert(path != NULL);

	struct stat buf;

	if(path == NULL)
		p_error("error: %s: the function argument was passed NULL value\n", __func__);

	if(stat(path, &buf) == 0 && S_ISREG(buf.st_mode))
		return true;

	return false;
}

bool is_dir(const char *path)
{
	assert(path != NULL);

	struct stat buf;

	if(path == NULL)
		p_error("error: %s: the function argument was passed NULL value\n", __func__);

	if(stat(path, &buf) == 0 && S_ISDIR(buf.st_mode))
		return true;

	return false;
}

bool check_dir(const char *dir)
{
	assert(dir != NULL);

	if(dir == NULL)
		p_error(stderr, "error: %s: the function argument was passed NULL value\n", __func__);

	if(ignore_directory != NULL)
	{
		char *dup_ignore_dir = duplicate_string(ignore_directory);
		const char *ignore_dir_name = basename(dup_ignore_dir);

		if(strcmp(dir, ignore_dir_name) == 0)
		{
			free(dup_ignore_dir);
			return false;
		}

		free(dup_ignore_dir);
	}

	if(environment_dir_patterns != NULL)
		return !check_pattern(dir, environment_dir_patterns);

	return !check_pattern(dir, default_dir_patterns);
}

bool check_file(const char *file)
{
	assert(file != NULL);

	if(file == NULL)
		fail(stderr, "error: the function argument was passed NULL value - %s\n", __func__);

	if(environment_file_patterns != NULL)
		return check_pattern(file, environment_file_patterns);

	return check_pattern(file, default_file_patterns);
}
