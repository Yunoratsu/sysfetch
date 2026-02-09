#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>

#include "include/sysfetch.h"
#include "include/utils.h"

void fetch_all(FetchStats *stats) {
    // User and Host
    struct passwd *pw = getpwuid(getuid());
    strncpy(stats->username, pw ? pw->pw_name : "unknown", 31);
    gethostname(stats->hostname, 63);

    // Kernel & OS
    struct utsname ut;
    uname(&ut);
    strncpy(stats->kernel, ut.release, 63);
    strncpy(stats->os_name, ut.sysname, 31);

    // Uptime & RAM (One syscall for both!)
    struct sysinfo si;
    if (sysinfo(&si) == 0) {
        stats->uptime_h = si.uptime / 3600;
        stats->uptime_m = (si.uptime % 3600) / 60;

        // RAM
        unsigned long total = si.totalram * si.mem_unit;
        unsigned long free = si.freeram * si.mem_unit;
        unsigned long buff = si.bufferram * si.mem_unit;

        stats->mem_total_mb = total / 1024 / 1024;
        stats->mem_used_mb = (total - free - buff) / 1024 / 1024;
    }

    // CPU (Parsing /proc/cpuinfo manually)
    int fd = open("/proc/cpuinfo", O_RDONLY);
    if (fd != -1) {
        char buffer[2048];
        int bytes = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes > 0) {
            buffer[bytes] = '\0';
            char *model = strstr(buffer, "model name");
            if (model) {
                char *colon = strchr(model, ':');
                if (colon) {
                    colon += 2; // Skip ": "
                    int i = 0;
                    while (colon[i] != '\n' && colon[i] != '\0' && i < 127) {
                        stats->cpu_model[i] = colon[i];
                        i++;
                    }
                    stats->cpu_model[i] = '\0';

                }
            }
        }
        close(fd);
    }
}
