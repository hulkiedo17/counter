#ifndef COUNT_H
#define COUNT_H

#define BUFSIZE 1024

extern bool detail_flag;
extern bool recursion_flag;
extern bool config_and_shell_files_flag;
extern bool count_without_spaces;
extern bool clean_output;
extern bool output_pipe_short;
extern bool output_pipe_long;
extern bool output_pipe_full;

long long count_lines_in_dir(const char *dir);

#endif
