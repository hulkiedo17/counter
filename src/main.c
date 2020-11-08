#include <stdio.h>
#include <getopt.h>
#include "../include/count.h"

int main(int argc, char **argv)
{
    int result;
    long long count;
    char* def_path = NULL;
    int debug_val = 0;
    int recursion = 0;

    const char* short_opt = "p:dR";
    const struct option long_opt[] = {
        {"path", required_argument, NULL, 'p'},
        {"detail", no_argument, NULL, 'd'},
        {"no-recursion", no_argument, NULL, 'R'},
        {NULL, 0, NULL, 0}
    };

    def_path = get_current_dir();

    while((result = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1)
    {
        switch(result) {
        case 'p':
            def_path = optarg;
            break;
        case 'd':
            debug_val = 1;
            break;
        case 'R':
            recursion = 1;
            break;
        default:
            fprintf(stderr, "main(): unknown option finded\n\n");
            break;
        }
    }

    count = count_lines_in_dir(def_path, debug_val, recursion);
    printf("%lld\n", count);

    return 0;
}