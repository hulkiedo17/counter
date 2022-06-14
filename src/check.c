#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../include/misc.h"

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

	if(dir[0] == '.')
		return false;
	
	return true;
}

bool check_file(const char* file)
{
	assert(file != NULL);

	if(file == NULL)
		fail(stderr, "error: the function argument was passed NULL value - %s\n", __func__);

	if(file[0] == '.')
		return false;

	return true;
}
