#ifndef CHECK_H
#define CHECK_H

extern const char* environment_dir_patterns;
extern const char* environment_file_patterns;
extern const char* ignore_directory;

bool is_file(const char* path);
bool is_dir(const char* path);
bool check_dir(const char* dir);
bool check_file(const char* file);

#endif
