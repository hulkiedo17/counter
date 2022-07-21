#ifndef CHECK_H
#define CHECK_H

extern const char *dir_skip_pattern;
extern const char *dir_count_pattern;

extern const char *file_skip_pattern;
extern const char *file_count_pattern;

extern char *ignore_dir;
extern char *ignore_file;

bool is_file(const char *path);
bool is_dir(const char *path);
bool check_dir(const char *dir);
bool check_file(const char *file);

#endif
