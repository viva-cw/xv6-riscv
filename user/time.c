#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

struct rusage {
    uint cputime;
};

int main(int argc, char *argv[]) {
  if(argc < 2){
    fprintf(2, "Usage: time command\n");
    exit(1);
  }

  int start_time = uptime();
  int pid = fork();

  if(pid < 0){
    fprintf(2, "time: fork failed\n");
    exit(1);
  }
  
  if(pid == 0){
    exec(argv[1], argv + 1);
    fprintf(2, "exec %s failed\n", argv[1]);
    exit(1);
  }

  struct rusage r;
  wait2(0, &r);
  int end_time = uptime();
  int elapsed = end_time - start_time;
  
  int cpu_usage = 0;
  if (elapsed > 0) {
      cpu_usage = (r.cputime * 100) / elapsed;
  }

  printf("elapsed time: %d ticks, cpu time: %d ticks, %d%% CPU\n", elapsed, r.cputime, cpu_usage);
  exit(0);
}
