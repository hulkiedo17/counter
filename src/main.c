#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/count.h"
#include "../include/misc.h"

int main(int argc, char **argv)
{
    int result;
    long long count;
	bool def_alloc_flag = false;
    char* def_path = NULL;

    const char* short_opt = "p:PdR";
    const struct option long_opt[] = {
        {"path", required_argument, NULL, 'p'},
		{"cur-path", no_argument, NULL, 'P'},
        {"detail", no_argument, NULL, 'd'},
        {"no-recursion", no_argument, NULL, 'R'},
        {NULL, 0, NULL, 0}
    };

    def_path = getcw();

    while((result = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1)
    {
        switch(result) {
        case 'p':
			free(def_path);
			def_alloc_flag = true;
            def_path = optarg;
            break;
		case 'P':
			printf("current path: %s\n", def_path);
			break;
        case 'd':
            detail_flag = true;
            break;
        case 'R':
            recursion_flag = false;
            break;
        default:
            fprintf(stderr, "main(): unknown option finded\n\n");
            break;
        }
    }

    if((count = count_lines_in_dir(def_path)) != -1)
    	printf("%lld\n", count);
	else
		fail(stderr, "main(): an error occurred while counting in the count_lines_in_dir() function\n");

	if(def_path && def_alloc_flag)
		free(def_path);

    return 0;
}
