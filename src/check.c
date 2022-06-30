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

const char *env_dir_patterns = NULL;
const char *env_file_patterns = NULL;

char *ignore_dir = NULL;

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
		p_error("error: %s: the function argument was passed NULL value\n", __func__);

	if(ignore_dir != NULL)
	{
		char *dup_dir = str_dup(ignore_dir);
		const char *name = basename(dup_dir);

		if(strcmp(dir, name) == 0)
		{
			free(dup_dir);
			return false;
		}

		free(dup_dir);
	}

	if(env_dir_patterns != NULL)
		return !check_pattern(dir, env_dir_patterns);

	return !check_pattern(dir, default_dir_patterns);
}

bool check_file(const char *file)
{
	assert(file != NULL);

	if(file == NULL)
		p_error("error: %s: the function argument was passed NULL value\n", __func__);

	if(env_file_patterns != NULL)
		return check_pattern(file, env_file_patterns);

	return check_pattern(file, default_file_patterns);
}
