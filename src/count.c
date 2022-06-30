#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <assert.h>
#include <stdbool.h>
#include "../include/misc.h"
#include "../include/check.h"

#define LINE_SIZE 256

char *source_file = NULL;

bool verbose_flag = false;
bool no_recursive_flag = false;
bool no_spaces = false;
bool no_zero = false;

static char* read_line_from_file(FILE *fp)
{
	assert(fp != NULL);

	int c;
	size_t pos = 0;
	size_t len = LINE_SIZE;
	char *buf = NULL;

	buf = calloc(len, sizeof(char));
	if(buf == NULL) 
		p_error("error: %s: allocation failed\n", __func__);

	while(1)
	{
		c = fgetc(fp);

		if(c == '\n')
		{
			buf[pos] = '\0';
			return buf;
		}
		else if(c == EOF)
		{
			if(pos != 0)
			{
				buf[pos] = '\0';
				return buf;
			}

			free(buf);
			return NULL;
		}

		buf[pos++] = c;

		if(pos >= len)
		{
			len += LINE_SIZE;
			buf = realloc(buf, len);
			if(buf == NULL)
				p_error("error: %s: allocation failed\n", __func__);
		}
	}

	return NULL;
}

static size_t count_lines_in_file(const char *path)
{
	assert(path != NULL);

	size_t count = 0;
	char *buf = NULL;
	FILE *fp = NULL;

	if(path == NULL)
		p_error("error: %s: the function argument was passed the NULL value\n", __func__);

	fp = fopen(path, "r");

	while((buf = read_line_from_file(fp)) != NULL)
	{
		if(!no_spaces)
			count++;
		else if(no_spaces && (buf[0] != '\0'))
			count++;

		free(buf);
	}
	
	fclose(fp);

	if(verbose_flag)
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
	assert(path != NULL);

	DIR *dir = NULL;
	struct dirent *entry = NULL;
	char *full_path = NULL;
	size_t count = 0;

	if(path == NULL)
		p_error("error: %s: the function argument was passed the NULL value\n", __func__);

	if(source_file != NULL)
	{
		if(is_file(source_file) && check_file(source_file))
			count += count_lines_in_file(source_file);
		else
			p_error("error: %s: invalid file\n", __func__);
		
		return count;
	}

	dir = opendir(path);
	if(dir == NULL)
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
