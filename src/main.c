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
    bool def_alloc_flag = true;
    char* def_path = NULL;

    const char* short_opt = "p:PdRhcvno";
    const struct option long_opt[] = {
        {"path", required_argument, NULL, 'p'},
        {"cur-path", no_argument, NULL, 'P'},
        {"detail", no_argument, NULL, 'd'},
        {"no-recursion", no_argument, NULL, 'R'},
        {"help", no_argument, NULL, 'h'},
        {"conf", no_argument, NULL, 'c'},
        {"version", no_argument, NULL, 'v'},
	{"no-spaces", no_argument, NULL, 'n'},
	{"output-clean", no_argument, NULL, 'o'},
        {NULL, 0, NULL, 0}
    };

    def_path = getcw();

    while((result = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1)
    {
        switch(result) {
        case 'p':
            free(def_path);
            def_path = NULL;
            def_alloc_flag = false;
            def_path = optarg;
            break;
        case 'P':
            printf("current path: %s\n", def_path);
            exit(EXIT_SUCCESS);
            break;
        case 'd':
            detail_flag = true;
            break;
        case 'R':
            recursion_flag = false;
            break;
        case 'h':
            help();
            exit(EXIT_SUCCESS);
            break;
        case 'v':
            version();
            exit(EXIT_SUCCESS);
            break;
        case 'c':
            config_and_shell_files_flag = true;
            break;
	case 'n':
            count_without_spaces = true;
            break;
        case 'o':
	    free(def_path);
	    def_path = strdup(".");
	    clean_output = true;
	    break;
        default:
            fprintf(stderr, "main(): unknown option finded\n\n");
            break;
        }
    }

    if((count = count_lines_in_dir(def_path)) != -1) {
        if(detail_flag == true) {
            printf("\n%lld\n", count);
        } else {
            printf("%lld\n", count);
        }
    } else {
        warning(stderr, "main(): an error occurred while counting in the count_lines_in_dir() function\n");
    }

    if(def_path && def_alloc_flag) {
        free(def_path);
    }

    return 0;
}
