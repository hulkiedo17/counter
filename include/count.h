#ifndef COUNT_H
#define COUTN_H

extern char *source_file;

extern bool output_flag;
extern bool no_recursive_flag;
extern bool no_spaces;
extern bool no_zero;

size_t count_lines(const char *path);

#endif
