#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include "misc.h"
#include "count.h"
#include "check.h"

bool use_skip_pattern = false;
bool use_count_pattern = false;

int main(int argc, char *argv[])
{
	int result = -1;
	size_t count = 0;
	bool no_total = false;
	char *default_path = NULL;
	
	default_path = get_work_dir();

	while((result = getopt(argc, argv, "vhorsztecp:f:F:D:")) != -1)
	{
		switch(result)
		{
			case 'v':
				version();
				exit(EXIT_SUCCESS);
			case 'h':
				help();
				exit(EXIT_SUCCESS);
			case 'o':
				output_flag = true;
				break;
			case 'r':
				no_recursive_flag = true;
				break;
			case 's':
				no_spaces = true;
				break;
			case 'z':
				no_zero = true;
				break;
			case 't':
				no_total = true;
				break;
			case 'e':
				use_skip_pattern = true;
				break;
			case 'c':
				use_count_pattern = true;
				break;
			case 'p':
				free(default_path);
				default_path = strdup(optarg);
				break;
			case 'f':
				source_file = strdup(optarg);
				break;
			case 'F':
				ignore_file = strdup(optarg);
				break;
			case 'D':
				ignore_dir = strdup(optarg);
				break;
			default:
				p_warn("unknown option -\'%c\'\n", result);
				break;
		}
	}

	if(use_skip_pattern)
	{
		if((dir_skip_pattern = getenv("DIR_SKIP_COUNTER")) == NULL)
			p_error("error: %s: dir_skip_pattern is null\n", __func__);

		if((file_skip_pattern = getenv("FILE_SKIP_COUNTER")) == NULL)
			p_error("error: %s: file_skip_pattern is null\n", __func__);
	}

	if(use_count_pattern)
	{
		if((dir_count_pattern = getenv("DIR_COUNT_COUNTER")) == NULL)
			p_error("error: %s: dir_count_pattern is null\n", __func__);

		if((file_count_pattern = getenv("FILE_COUNT_COUNTER")) == NULL)
			p_error("error: %s: file_count_pattern is null\n", __func__);
	}

	count = count_lines(default_path);
	if(!no_total)
	{
		if(output_flag)
			printf("total = %zd\n", count);
		else
			printf("%zd\n", count);
	}

	free(default_path);
	free(source_file);
	free(ignore_dir);
	return 0;
}
