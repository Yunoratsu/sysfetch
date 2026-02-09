#include "include/sysfetch.h"
#include "include/display.h"
#include "include/utils.h"
#include "include/art.h"

void display(FetchStats *stats) {
    char *art_ptr = (char *)src_assets_linux_txt;
    int art_len = src_assets_linux_txt_len;
    int line_count = 0;
    char *current_pos = art_ptr;
    int art_width = 45; // Adjust this to the width of your widest art line

    while (current_pos < art_ptr + art_len) {
        int chars_printed = 0;

        // 1. Print one line of art and count the characters
        while (current_pos < art_ptr + art_len && *current_pos != '\n') {
            write(1, current_pos, 1);
            current_pos++;
            chars_printed++;
        }
        
        // 2. Padding: If the art line is shorter than art_width, add spaces
        while (chars_printed < art_width) {
            write(1, " ", 1);
            chars_printed++;
        }

        // 3. Print the separator and info
        printf(" | ");
        
        if (line_count == 0)      printf(CYN "%s" RST "@" CYN "%s" RST, stats->username, stats->hostname);
        else if (line_count == 1) printf(YEL "OS:     " RST "%s", stats->os_name);
        else if (line_count == 2) printf(YEL "Kernel: " RST "%s", stats->kernel);
        else if (line_count == 3) printf(YEL "CPU:    " RST "%s", stats->cpu_model);
        else if (line_count == 4) printf(YEL "Uptime: " RST "%dh %dm", stats->uptime_h, stats->uptime_m);
        else if (line_count == 5) printf(YEL "RAM:    " RST "%luMB / %luMB", stats->mem_used_mb, stats->mem_total_mb);

        printf("\n");
        
        if (current_pos < art_ptr + art_len && *current_pos == '\n') {
            current_pos++;
        }
        line_count++;
    }
}

int main(void) {
    FetchStats stats;
    fetch_all(&stats);
    display(&stats);
    return 0;
}
