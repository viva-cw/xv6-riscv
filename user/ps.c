#include "kernel/param.h"
#include "kernel/types.h"

enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

#include "kernel/pstat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  struct pstat uproc[NPROC];
  int nprocs;
  int i;
  char *state;
  static char *states[] = {
    [SLEEPING]  "sleeping",
    [RUNNABLE]  "runnable",
    [RUNNING]   "running ",
    [ZOMBIE]    "zombie  "
  };

  // Execute the system call and capture the result
  nprocs = getprocs(uproc);

  if (nprocs < 0)
    exit(-1);

  int current_time = uptime();
int age;

  printf("pid\tstate\t\tsize\tage\tppid\tprio\tname\n");
  for (i=0; i<nprocs; i++) {
    state = states[uproc[i].state];
  
  // Calculate age only if the process is ready to run
    age = 0;
    if (uproc[i].state == RUNNABLE) {
      age = current_time - uproc[i].readytime;
    }

    printf("%d\t%s\t%d\t%d\t%d\t%d\t%s\n", uproc[i].pid, state,
                   (int)uproc[i].size, age, uproc[i].ppid, uproc[i].priority, uproc[i].name);
  }

  exit(0);
}

