#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include "../include/misc.h"
#include "../include/count.h"
#include "../include/check.h"

bool no_total = false;
bool no_env = false;

int main(int argc, char *argv[])
{
	int result = -1;
	size_t count = 0;
	char *default_path = NULL;
	
	default_path = get_work_dir();

	while((result = getopt(argc, argv, "hp:vrsztf:eD:")) != -1)
	{
		switch(result)
		{
			case 'v':
				verbose_flag = true;
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
			case 'f':
				source_file = strdup(optarg);
				break;
			case 'e':
				no_env = true;
				break;
			case 'D':
				ignore_dir = strdup(optarg);
				break;
			case 'h':
				help();
				break;
			case 'p':
				free(default_path);
				default_path = strdup(optarg);
				break;
			default:
				p_warn("unknown option -\'%c\'\n", result);
				break;
		}
	}

	if(!no_env)
	{
		env_dir_patterns = getenv("DIR_PATTERN_COUNTER");
		env_file_patterns = getenv("FILE_PATTERN_COUNTER");
	}

	count = count_lines(default_path);
	if(!no_total)
	{
		if(verbose_flag)
			printf("total = %zd\n", count);
		else
			printf("%zd\n", count);
	}

	free(default_path);
	free(source_file);
	free(ignore_dir);
	return 0;
}
