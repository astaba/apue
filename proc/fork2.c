/* =========================================================================
 * Created on: <Thu Jul 09 12:27:10 +01 2026>
 * Time-stamp: <Wed Jul 15 01:22:07 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/proc/fork2.c -
 *
 * Figure 8.8: Avoid zombie processes by calling fork twice
 * ========================================================================= */
#include "apue.h"
#include <sys/wait.h>

int main(void) {
  pid_t pid;

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) { /* first child */
    if ((pid = fork()) < 0)
      err_sys("fork error");
    else if (pid > 0)
      exit(0); /* parent from second fork == first child */

    /*
     * NOTE: We're the second child; our parent becomes init as soon
     * as our real parent calls exit() in the statement above.  Here's
     * where we'd continue executing, knowing that when we're done,
     * init will reap our status.
     *
     * WARNING: The purpose of sleep() is to give the parent (the
     * first child) enough time to exit while its orphan child (the
     * second child) is still running so that it is inherited by init,
     * which is the whole purpose of the experiment. However, on a
     * heavy loaded system scheduling sleep() could run and return
     * control to the child before the parent is given enough time
     * slices to exit.
     */
    sleep(2);
    printf("second child, parent pid = %ld\n", (long)getppid());
    exit(0);
  }

  if (waitpid(pid, NULL, 0) != pid) /* wait for first child */
    err_sys("waitpid error");

  /*
   * We're the parent (the original process); we continue executing,
   * knowing that we're not the parent of the second child.
   */
  exit(0);
}
