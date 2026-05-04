#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

void print_sched_priority(const char *label) {
    char cmd[64];
    char buf[256];
    FILE *f;

    snprintf(cmd, sizeof(cmd), "ps -l | grep ' %d '", getpid());
    f = popen(cmd, "r");
    if (f) {
        while (fgets(buf, sizeof(buf), f))
            printf("[%s] %s", label, buf);
        pclose(f);
    }
    fflush(stdout);
}

int main() {
    int count = 0;

    printf("This process will sleep periodically\n");
    
    while(count < 100) {
        print_sched_priority("sleep");
        sleep(1);
        
        count++;
    }
    
    printf("Sleep test finished\n");
    return 0;
}