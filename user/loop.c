#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int pid = getpid();
    printf("Starting loop program with PID %d\n", pid);
    
    for (long long i = 0; i < 100000000; i++) {
        if (i % 25000000 == 0) {
            printf("PID %d is running...\n", pid);
        }
    }
    exit(0);
}
