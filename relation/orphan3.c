/* =========================================================================
 * Created on: <Fri Jul 17 15:55:15 +01 2026>
 * Time-stamp: <Fri Jul 17 17:45:47 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/relation/orphan3.c -
 *
 * Figure 9.12 Creating an orphaned process group
 * ========================================================================= */
#include "apue.h"
#include <errno.h>

static void sig_hup(int signo) {
  printf("SIGHUP received, pid = %ld\n", (long)getpid());
}

static void pr_ids(char *name) {
  printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n", name,
         (long)getpid(), (long)getppid(), (long)getpgrp(),
         (long)tcgetpgrp(STDIN_FILENO));
  fflush(stdout);
}

int main(void) {
  char c;
  pid_t pid;

  pr_ids("parent");
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid > 0) { /* parent */
    sleep(5);           /* sleep to let child stop itself */
  } else {              /* child */
    pr_ids("child");
    signal(SIGHUP, sig_hup); /* establish signal handler */
    kill(getpid(), SIGTSTP); /* stop ourself */
    pr_ids("child");         /* prints only if we're continued */
    if (read(STDIN_FILENO, &c, 1) != 1)
      printf("read error %d on controlling TTY\n", errno);
  }
  exit(0);
}
