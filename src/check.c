#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../include/misc.h"
#include "../include/count.h"

/* STATIC FUNCTIONS */

static bool check_source_files(const char *path)
{
    bool result = false;

    if(strstr(path, ".c") != NULL) {
        result = true;
    } else if(strstr(path, ".h") != NULL) {
        result = true;
    } else {
        result = false;
    }

    return result;
}

static bool check_config_files(const char *path)
{
    bool result = false;

    if(strstr(path, ".git") != NULL) {
        result = true;
    } else if(strstr(path, ".in") != NULL) {
        result = true;
    } else if(strstr(path, ".am") != NULL) {
        result = true;
    } else if(strstr(path, ".mk") != NULL) {
        result = true;
    } else if(strstr(path, ".conf") != NULL) {
        result = true;
    } else if(strstr(path, "config") != NULL) {
        result = true;
    } else if(strstr(path, "Makefile") != NULL) {
        result = true;
    } else if(strstr(path, "rc") != NULL) {
        result = true;
    } else if(strstr(path, ".sh") != NULL) {
        result = true;
    } else {
        result = false;
    }

    return result;
}

/* NON-STATIC FUNCTIONS */

bool is_file(const char *path)
{
    struct stat buf;

    if(path == NULL) {
        warning(stderr, "is_file(): the function argument was passed the NULL value (const char *path)\n");
        return false;
    }

    if(stat(path, &buf) == 0) {
        if(S_ISREG(buf.st_mode)) {
            return true;
        }
    }

    return false;
}

bool is_dir(const char *path)
{
    struct stat buf;

    if(path == NULL) {
        warning(stderr, "is_dir(): the function argument was passed the NULL value (const char *path)\n");
        return false;
    }

    if(stat(path, &buf) == 0) {
        if(S_ISDIR(buf.st_mode)) {
            return true;
        }
    }

    return false;
}

bool is_normal_file(const char *path)
{
    int res = false;

    if(path == NULL) {
        warning(stderr, "is_normal_file(): the function argument was passed the NULL value (const char *path)\n");
        return res;
    }

    if(config_and_shell_files_flag == true) {
        if(check_source_files(path) || check_config_files(path)) {
            res = true;
        } else {
            res = false;
        }
    } else {
        if(check_source_files(path)) {
            res = true;
        } else {
            res = false;
        }
    }

    return res;
}

bool is_normal_dir(const char *path)
{
    bool res = false;

    if(path == NULL) {
        warning(stderr, "is_normal_dir(): the function argument was passed the NULL value (const char *path)\n");
        return res;
    }

    if(strstr(path, ".git") != NULL) {
        res = false;
    } else if(strchr(path, '.') != NULL) {
        res = false;
    } else if(strstr(path, "doc") != NULL) {
        res = false;
    } else if(strstr(path, "bin") != NULL) {
        res = false;
    } else if(strstr(path, "build") != NULL) {
        res = false;
    } else {
        res = true;
    }

    return res;
}
