#ifndef MISC_H
#define MISC_H

void fail(FILE* out, const char* fmt, ...);
char* duplicate_string(const char* string);
char* concatenate_path_and_name(const char* path, const char* filename);
char* get_work_dir(void);
void help(void);
void version(void);

#endif
