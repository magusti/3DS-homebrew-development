#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    struct rusage r_usage;
    double cpu_percentage;
    double prev_cpu_time = 0.0;
    float y;


    while (1) {
        for(int i = 0; i < 1000000; i++) y = y * 1.0;

        if (getrusage(RUSAGE_SELF, &r_usage) == 0) {
            double current_cpu_time = r_usage.ru_utime.tv_sec + r_usage.ru_utime.tv_usec / 1000000.0;
            
            if (prev_cpu_time != 0.0) {
                cpu_percentage = (current_cpu_time - prev_cpu_time) * 100.0 / sysconf(_SC_CLK_TCK);
                printf("CPU Percentage used by the process: %.2f%%\n", cpu_percentage);
            }
            
            prev_cpu_time = current_cpu_time;
        } else {
            perror("Error getting resource usage");
        }

        sleep(1); // Wait for 1 second before checking again
    }

    return 0;
}
