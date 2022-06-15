#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include "../include/misc.h"
#include "../include/count.h"
#include "../include/check.h"

bool no_total = false;
bool no_env = false;

int main(int argc, char* argv[])
{
	int result = -1;
	size_t count = 0;
	char* default_path = NULL;
	
	const char* short_opt = "hp:vrsztf:eD:";
	const struct option long_opt[] = 
	{
		{"help", no_argument, NULL, 'h'},
		{"path", required_argument, NULL, 'p'},
		{"verbose", no_argument, NULL, 'v'},
		{"no-recursive", no_argument, NULL, 'r'},
		{"no-spaces", no_argument, NULL, 's'},
		{"no-zero", no_argument, NULL, 'z'},
		{"no-total", no_argument, NULL, 't'},
		{"file", required_argument, NULL, 'f'},
		{"no-env", no_argument, NULL, 'e'},
		{"ignore-dir", required_argument, NULL, 'D'},
		{NULL, 0, NULL, 0}
	};

	default_path = get_work_dir();

	while((result = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1)
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
				source_file = duplicate_string(optarg);
				break;
			case 'e':
				no_env = true;
				break;
			case 'D':
				ignore_directory = duplicate_string(optarg);
				break;
			case 'h':
				help();
				exit(EXIT_SUCCESS);
				break;
			case 'p':
				free(default_path);
				default_path = duplicate_string(optarg);
				break;
			default:
				fprintf(stderr, "unknown option -\'%c\'\n", result);
				break;
		}
	}

	if(!no_env)
	{
		environment_dir_patterns = getenv("DIR_PATTERN_COUNTER");
		environment_file_patterns = getenv("FILE_PATTERN_COUNTER");
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
	return 0;
}
