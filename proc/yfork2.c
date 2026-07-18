/* =========================================================================
 * Created on: <Thu Jul  9 21:36:49 +01 2026>
 * Time-stamp: <Thu Jul  9 21:37:16 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/proc/yfork2.c -
 *
 * Figure 8.8: Avoid zombie processes by calling fork twice
 * ========================================================================= */
#include "apue.h"
#include <sys/wait.h>

int main(void) {
  pid_t pid;

  printf("parent process pid = %ld\n", (long)getpid());

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) { /* first child */
    if ((pid = fork()) < 0)
      err_sys("fork error");
    else if (pid > 0) {
      printf("first child, parent pid = %ld\n", (long)getppid());
      printf("first child pid = %ld\n", (long)getpid());
      exit(0); /* parent from second fork == first child */
    }

    /*
     * We're the second child; our parent becomes init as soon
     * as our real parent calls exit() in the statement above.
     * Here's where we'd continue executing, knowing that when
     * we're done, init will reap our status.
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
