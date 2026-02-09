#ifndef UTILS_H
#define UTILS_H

#include <stdarg.h>
#include <unistd.h> // write()


// Wrappers
void printf(const char *fmt, ...);
char *utoa(unsigned long value, char *str, int base);
char *itoa(int value, char *str, int base);

#endif
