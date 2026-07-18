/* =========================================================================
 * Created on: <Thu Jul 09 11:57:36 +01 2026>
 * Time-stamp: <Sat Jul 11 20:06:48 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/proc/wait1.c -
 *
 * Figure 8.6: This program calls the pr_exit function, demonstrating
 * the various values for the termination status.
 * ========================================================================= */
#include "apue.h"
#include <sys/wait.h>

int main(void) {
  pid_t pid;
  int status;

  /* 1st fork and reap  */

  if ((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid == 0) /* child */
    exit(7);
  if (wait(&status) != pid) /* wait for child */
    err_sys("wait error");

  pr_exit(status); /* and print its status */

  /* 2nd fork and reap  */

  if ((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid == 0) /* child */
    abort();         /* generates SIGABRT */
  if (wait(&status) != pid) /* wait for child */
    err_sys("wait error");

  pr_exit(status); /* and print its status */

  /* 3rd fork and reap  */

  if ((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid == 0) /* child */
    status /= 0;     /* divide by 0 generates SIGFPE */
  if (wait(&status) != pid) /* wait for child */
    err_sys("wait error");

  pr_exit(status); /* and print its status */

  exit(0);
}
