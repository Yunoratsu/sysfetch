#include "include/utils.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

// Simple integer-to-ascii
char *itoa(int value, char *str, int base) {
    char *rc, *ptr, *low;
    if (base < 2 || base > 36) return str = '\0', str;
    rc = ptr = str;
    if (value < 0 && base == 10) *ptr++ = '-';
    low = ptr;
    do {
        *ptr++ = "0123456789abcdefghijklmnopqrstuvwxyz"[ABS(value % base)];
        value /= base;
    } while (value);
    *ptr-- = '\0';
    while (low < ptr) {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

char *utoa(unsigned long value, char *str, int base) {
    char *ptr, *low;

    if (base < 2 || base > 36) return str = '\0', str;

    ptr = str;
    low = ptr;

    do {
        *ptr++ = "0123456789abcdefghijklmnopqrstuvwxyz"[value % base];
        value /= base;
    } while (value);

    *ptr-- = '\0';

    while (low < ptr) {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return str;
}

void printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    
    char buf[1024]; // Our local buffer
    int b_idx = 0;

    for (int i = 0; fmt[i] != '\0'; i++) {
        if (fmt[i] == '%' && fmt[i+1] != '\0') {
            i++;
            if (fmt[i] == 's') {
                char *s = va_arg(args, char *);
                while (*s) buf[b_idx++] = *s++;
            } else if (fmt[i] == 'd') {
                char num_buf[32];
                itoa(va_arg(args, int), num_buf, 10);
                char *n = num_buf;
                while (*n) buf[b_idx++] = *n++;
            } else if (fmt[i] == 'c') {
                char c = (char)va_arg(args, int);
                buf[b_idx++] = c;
            } else if (fmt[i] == 'l') {
                if (fmt[i+1] == 'u') {
                    i++; // skip 'u'
                    unsigned long val = va_arg(args, unsigned long);
                    char num_buf[32];
                    utoa(val, num_buf, 10);
                    char *n = num_buf;
                    while (*n) buf[b_idx++] = *n++;
                }
            }
        } else {
            buf[b_idx++] = fmt[i];
        }
        
        if (b_idx >= 1024) {
            write(1, buf, b_idx);
            b_idx = 0;
        }
    }

    if (b_idx > 0) write(1, buf, b_idx);
    va_end(args);
}
