#ifndef MISC_H
#define MISC_H

void p_error(const char *fmt, ...);
void p_warn(const char *fmt, ...);
char* str_dup(const char *str);
char* concatenate_path_and_name(const char *path, const char *filename);
char* get_work_dir(void);
void help(void);

#endif
