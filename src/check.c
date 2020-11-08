#include <stdio.h>
#include <string.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int is_file(char *path)
{
    struct stat buf;

    if(stat(path, &buf) == 0) {
        if(S_ISREG(buf.st_mode)) {
            return 0;
        }
    }

    return -1;
}

int is_dir(char *path)
{
    struct stat buf;

    if(stat(path, &buf) == 0) {
        if(S_ISDIR(buf.st_mode)) {
            return 0;
        }
    }

    return -1;
}

int is_normal_file(char *path)
{
    int res = -1;

    if(path == NULL) {
        fprintf(stderr, "is_normal_file(): NULL path pointer (in arguments)\n");
        return res;
    }

    if(strstr(path, ".c") != NULL) {
        res = 0;
    } else if(strstr(path, ".h") != NULL) {
        res = 0;
    } else if(strstr(path, ".git") != NULL) {
        res = 0;
    } else if(strstr(path, ".in") != NULL) {
        res = 0;
    } else if(strstr(path, ".am") != NULL) {
        res = 0;
    } else if(strstr(path, ".mk") != NULL) {
        res = 0;
    } else if(strstr(path, ".conf") != NULL) {
        res = 0;
    } else if(strstr(path, "config") != NULL) {
        res = 0;
    } else if(strstr(path, "Makefile") != NULL) {
        res = 0;
    } else if(strstr(path, ".asm") != NULL) {
        res = 0;
    } else if(strstr(path, ".s") != NULL) {
        res = 0;
    } else if(strstr(path, ".S") != NULL) {
        res = 0;
    } else if(strstr(path, "rc") != NULL) {
        res = 0;
    } else {
        res = -1;
    }

    return res;
}

int is_normal_dir(char *path)
{
    int res = -1;

    if(path == NULL) {
        fprintf(stderr, "is_normal_dir(): NULL path pointer (in arguments)\n");
        return res;
    }

    if(strstr(path, ".git") != NULL) {
        res = -1;
    } else if(strstr(path, ".") != NULL) {
        res = -1;
    } else {
        res = 0;
    }

    return res;
}