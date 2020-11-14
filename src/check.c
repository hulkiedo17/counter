#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../include/misc.h"

int is_file(const char *path)
{
    struct stat buf;

	if(path == NULL) {
		fail(stderr, "is_file(): the function argument was passed the NULL value (const char *path)\n");
		return 0;
	}

    if(stat(path, &buf) == 0) {
        if(S_ISREG(buf.st_mode)) {
            return 1;
        }
    }

    return 0;
}

int is_dir(const char *path)
{
    struct stat buf;

	if(path == NULL) {
		fail(stderr, "is_dir(): the function argument was passed the NULL value (const char *path)\n");
		return 0;
	}

    if(stat(path, &buf) == 0) {
        if(S_ISDIR(buf.st_mode)) {
            return 1;
        }
    }

    return 0;
}

int is_normal_file(const char *path)
{
    int res = 0;

    if(path == NULL) {
		fail(stderr, "is_normal_file(): the function argument was passed the NULL value (const char *path)\n");
        return res;
    }

    if(strstr(path, ".c") != NULL) {
        res = 1;
    } else if(strstr(path, ".h") != NULL) {
        res = 1;
    } else if(strstr(path, ".git") != NULL) {
        res = 1;
    } else if(strstr(path, ".in") != NULL) {
        res = 1;
    } else if(strstr(path, ".am") != NULL) {
        res = 1;
    } else if(strstr(path, ".mk") != NULL) {
        res = 1;
    } else if(strstr(path, ".conf") != NULL) {
        res = 1;
    } else if(strstr(path, "config") != NULL) {
        res = 1;
    } else if(strstr(path, "Makefile") != NULL) {
        res = 1;
    } else if(strstr(path, ".asm") != NULL) {
        res = 1;
    } else if(strstr(path, ".s") != NULL) {
        res = 1;
    } else if(strstr(path, ".S") != NULL) {
        res = 1;
    } else if(strstr(path, "rc") != NULL) {
        res = 1;
    } else {
        res = 0;
    }

    return res;
}

int is_normal_dir(const char *path)
{
    int res = 0;

    if(path == NULL) {
		fail(stderr, "is_normal_dir(): the function argument was passed the NULL value (const char *path)\n");
        return res;
    }

    if(strstr(path, ".git") != NULL) {
        res = 0;
    } else if(strchr(path, '.') != NULL) {
        res = 0;
	} else if(strstr(path, "doc") != NULL) {
		res = 0;
	} else if(strstr(path, "bin") != NULL) {
		res = 0;
	} else if(strstr(path, "build") != NULL) {
		res = 0;
    } else {
        res = 1;
    }

    return res;
}
