#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include "../include/check.h"

static char* concat_name_and_path(char *path, char *name)
{
    size_t len = 0;
    char* full_path = NULL;

    len = strlen(path) + strlen(name) + 2;
    full_path = malloc(len * sizeof(char));
    if(full_path == NULL) {
        fprintf(stderr, "concat_name_and_path(): malloc() failed\n");
        return NULL;
    }

    strcpy(full_path, path);    // full_path = path
    strcat(full_path, "/");     // full_path = path + /
    strcat(full_path, name);    // full_path = path + / + name
    return full_path;
}

static long long count_lines_in_file(char *path, int debug)
{
    FILE *fp = NULL;
    long long count = 0;
    int c, char_flag;

    if(path == NULL) {
        fprintf(stderr, "count_lines_in_file(): NULL path pointer (in arguments)\n");
        return -1;
    }

    fp = fopen(path, "r");
    if(fp == NULL) {
        fprintf(stderr, "count_lines(): NULL file pointer (fopen() failed)\n");
        return -1;
    }

    char_flag = 0;
    while((c = fgetc(fp)) != EOF) {
        if(c == '\n') {
            count++;
            char_flag = 0;
        } else {
            // if there is no '\n' character in the line, but
            // there are other characters, then count this line
            // by setting the flag
            if(isalnum(c) || ispunct(c) || isspace(c)) {
                char_flag = 1;
            }
        }
    }

    if(char_flag == 1)
        count++;
    
    if(debug == 1)
        printf("%s = %lld\n", path, count);
    
    fclose(fp);
    return count;
}

char* get_current_dir(void)
{
    char *path = NULL;

    path = getenv("PWD");
    if(path == NULL) {
        fprintf(stderr, "get_current_dir(): getenv() failed\n");
        return NULL;
    }

    return path;
}

long long count_lines_in_dir(char *path, int debug, int recursion)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char *full_path = NULL;
    long long count = 0;
    int dir_skip_count = 0;

    if(path == NULL) {
        fprintf(stderr, "count_lines_in_dir(): NULL dir pointer\n");
        return -1;
    }

    dir = opendir(path);
    if(dir == NULL) {
        fprintf(stderr, "count_lines_in_dir(): opendir() failed -> (%s)\n", path);
        return -1;
    }

    while((entry = readdir(dir)) != NULL) {
        full_path = concat_name_and_path(path, entry->d_name);

        // if it's a file, then count the lines in it
        if(is_file(full_path) == 0) {
            if(is_normal_file(entry->d_name) == 0) {
                count += count_lines_in_file(full_path, debug);
            }
        }

        // if recursion is allowed for dirs, then check
        // the dir if it is
        if(recursion == 0) {
            // if it's a dir, then open it and count the 
            // lines in the files there
            if(is_dir(full_path) == 0) {
                if(is_normal_dir(entry->d_name) == 0) {
                    count += count_lines_in_dir(full_path, debug, recursion);
                }
            }
        }

        free(full_path);
        dir_skip_count++;
    }

    closedir(dir);
    return count;
}