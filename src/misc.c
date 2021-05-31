#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "../include/misc.h"

static const char* const program_version = "1.0";

void fail(FILE* out, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vfprintf(out, fmt, ap);
    va_end(ap);
}

char* getcw(void)
{
    char *path_ptr = NULL;
    size_t len;
    char buffer[BUFSIZ];

    if(getcwd(buffer, BUFSIZ) == NULL) {
        fail(stderr, "getcw(): error taking the path to the current directory (getcwd() failed)\n");
        return NULL;
    }

    len = strlen(buffer) + 1;
    path_ptr = malloc(sizeof(char) * len);
    if(path_ptr == NULL) {
        fail(stderr, "getcw(): memory allocation error (malloc() failed)\n");
        return NULL;
    }

    strncpy(path_ptr, buffer, len);

    return path_ptr;
}

void help(void) {
    printf("Usage: counter [options]\n");
    printf("options:\n");
    printf("\t(--path) -p [path_name] - specifying another directory for counting lines in files\n");
    printf("\t(--help) -h - prints this help message\n");
    printf("\t(--conf) -c - include to count config files\n\n");

    printf("\t(--no-recursion) -R - do not use files in nested(recursive) directories\n");
    printf("\t(--cur-path)\t -P - just show the current path\n");
    printf("\t(--detail)\t -d - show exactly which files are in use and the path to them\n");
    printf("\t(--no-spaces)\t -n - dont count the empty lines\n");
}

void version(void) {
    printf("program version = v%s\n\n", program_version);
}
