#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libgen.h>
#include "misc.h"
#include "main.h"

const char *dir_skip_pattern = NULL;
const char *file_skip_pattern = NULL;

const char *dir_count_pattern = NULL;
const char *file_count_pattern = NULL;

char *ignore_dir = NULL;
char *ignore_file = NULL;

static const char *const default_dir_skip_pattern = ".|build|bin";
static const char *const default_file_count_pattern = ".c|.h|.sh|.txt|Makefile";

static bool check_pattern(const char *source, const char *pattern)
{
	assert(source != NULL);
	assert(pattern != NULL);

	char *dup_pattern = NULL;
	char *token = NULL;

	dup_pattern = strdup(pattern);

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
	struct stat buf;

	if(!path)
		p_error("error: %s: the function argument was passed NULL value\n", __func__);

	if(stat(path, &buf) == 0 && S_ISREG(buf.st_mode))
		return true;

	return false;
}

bool is_dir(const char *path)
{
	struct stat buf;

	if(!path)
		p_error("error: %s: the function argument was passed NULL value\n", __func__);

	if(stat(path, &buf) == 0 && S_ISDIR(buf.st_mode))
		return true;

	return false;
}

bool check_dir(const char *dir)
{
	if(!dir)
		p_error("error: %s: the function argument was passed NULL value\n", __func__);

	if(ignore_dir)
	{
		char *dup_dir = strdup(ignore_dir);
		const char *name = basename(dup_dir);

		if(strcmp(dir, name) == 0)
		{
			free(dup_dir);
			return false;
		}

		free(dup_dir);
	}

	if(use_count_pattern)
		return check_pattern(dir, dir_count_pattern);

	if(use_skip_pattern)
		return !check_pattern(dir, dir_skip_pattern);

	return !check_pattern(dir, default_dir_skip_pattern);
}

bool check_file(const char *file)
{
	if(!file)
		p_error("error: %s: the function argument was passed NULL value\n", __func__);

	if(ignore_file)
	{
		char *dup_file = strdup(ignore_file);
		const char *name = basename(dup_file);

		if(strcmp(file, name) == 0)
		{
			free(dup_file);
			return false;
		}

		free(dup_file);
	}

	if(use_count_pattern)
		return check_pattern(file, file_count_pattern);

	if(use_skip_pattern)
		return !check_pattern(file, file_skip_pattern);

	return check_pattern(file, default_file_count_pattern);
}
