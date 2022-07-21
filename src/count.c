#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <assert.h>
#include <stdbool.h>
#include "misc.h"
#include "check.h"

char *source_file = NULL;

bool output_flag = false;
bool no_recursive_flag = false;
bool no_spaces = false;
bool no_zero = false;

static size_t count_lines_in_file(const char *path)
{
	size_t count = 0;
	size_t nread = 0;
	char *buf = NULL;
	FILE *fp = NULL;

	if(!path)
		p_error("error: %s: the function argument was passed the NULL value\n", __func__);

	fp = fopen(path, "r");
	if(!fp)
		p_error("error: %s: fopen failed, cannot open file\n", __func__);

	while(getline(&buf, &nread, fp) != -1)
	{
		if(!no_spaces)
			count++;
		else if(no_spaces && (buf[0] != '\0'))
			count++;
	}
	
	free(buf);
	fclose(fp);

	if(output_flag)
	{
		if(no_zero && (count > 0)) 
			fprintf(stdout, "%s = %zd\n", path, count);
		else if(!no_zero)
			fprintf(stdout, "%s = %zd\n", path, count);
	}

	return count;
}

size_t count_lines(const char *path)
{
	DIR *dir = NULL;
	struct dirent *entry = NULL;
	char *full_path = NULL;
	size_t count = 0;

	if(!path)
		p_error("error: %s: the function argument was passed the NULL value\n", __func__);

	if(source_file)
	{
		if(is_file(source_file) && check_file(source_file))
			count += count_lines_in_file(source_file);
		else
			p_error("error: %s: invalid file\n", __func__);
		
		return count;
	}

	dir = opendir(path);
	if(!dir)
		p_error("error: %s: opendir() function failed\n", __func__);

	while((entry = readdir(dir)) != NULL)
	{
		full_path = concatenate_path_and_name(path, entry->d_name);

		if(is_file(full_path) && check_file(entry->d_name))
			count += count_lines_in_file(full_path);

		if(is_dir(full_path) && check_dir(entry->d_name) && !no_recursive_flag)
			count += count_lines(full_path);

		free(full_path);
	}

	closedir(dir);
	return count;
}
