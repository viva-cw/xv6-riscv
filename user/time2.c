#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(2, "Usage: time2 <command> [args...]\n");
        exit(1);
    }

    int pid = fork();

    if (pid < 0) {
        fprintf(2, "fork failed\n");
        exit(1);
    }

    if (pid == 0) {
        // Child process executes the command
        exec(argv[1], argv + 1);
        fprintf(2, "exec %s failed\n", argv[1]);
        exit(1);
    }

    // Parent process waits for child to finish using our new system call
    int status;
    int cputime;
    wait2((uint64)&status, (uint64)&cputime);
    
    printf("cpu time: %d ticks\n", cputime);
    
    exit(0);
}
