#ifndef SYSFETCH_H
#define SYSFETCH_H

#include <sys/types.h>

typedef struct {
    char username[32];
    char hostname[64];
    char os_name[32];
    char kernel[64];
    char cpu_model[128];
    unsigned long mem_used_mb;
    unsigned long mem_total_mb;
    int uptime_h, uptime_m;
} FetchStats;

void fetch_all(FetchStats *stats);

#endif
