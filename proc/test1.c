/* =========================================================================
 * Created on: <Fri Jul 17 14:36:14 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:19 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/proc/test1.c -
 *
 * Figure 8.28 Program to generate accounting data
 * ========================================================================= */
#include "apue.h"

int main(void) {
  pid_t pid;

  if ((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid != 0) { /* parent */
    sleep(2);
    exit(2); /* terminate with exit status 2 */
  }

  if ((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid != 0) { /* first child */
    sleep(4);
    abort(); /* terminate with core dump */
  }

  if ((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid != 0) { /* second child */
    execl("/bin/dd", "dd", "if=/etc/passwd", "of=/dev/null", NULL);
    exit(7); /* shouldn't get here */
  }

  if ((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid != 0) { /* third child */
    sleep(8);
    exit(0); /* normal exit */
  }

  sleep(6);                /* fourth child */
  kill(getpid(), SIGKILL); /* terminate w/signal, no core dump */
  exit(6);                 /* shouldn't get here */
}
