#ifndef MISC_H
#define MISC_H

void fail(FILE* out, const char *fmt, ...);
void warning(FILE* out, const char *fmt, ...);
char* getcw(void);
void help(void);
void version(void);
char* strdup(const char *string);

#endif
