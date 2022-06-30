#ifndef CHECK_H
#define CHECK_H

extern const char *env_dir_patterns;
extern const char *env_file_patterns;
extern char *ignore_dir;

bool is_file(const char *path);
bool is_dir(const char *path);
bool check_dir(const char *dir);
bool check_file(const char *file);

#endif
