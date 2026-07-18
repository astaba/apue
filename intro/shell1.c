/* =========================================================================
 * Created on: <Fri Jun 26 18:42:41 +01 2026>
 * Time-stamp: <Fri Jun 26 18:48:23 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/intro/shell1.c -
 *
 * Figure 1.7: A bare-bones implementation of a shell-like program.
 * The process control features of the UNIX System are demonstrated
 * using this simple program that reads commands from standard input
 * and executes the commands.  See [[file:shell2.c][Figure 1.10]]
 * ========================================================================= */
#include "apue.h"
#include <sys/wait.h>

int main(void) {
  char buf[MAXLINE]; /* from apue.h */
  pid_t pid;
  int status;

  while (1) {
    printf("%% "); /* print prompt (printf requires %% to print %) */
    if (fgets(buf, MAXLINE, stdin) == NULL)
      break;

    if (buf[strlen(buf) - 1] == '\n')
      buf[strlen(buf) - 1] = 0; /* replace newline with null */

    if ((pid = fork()) < 0) {
      err_sys("fork error");
    } else if (pid == 0) { /* child */
      execlp(buf, buf, (char *)0);
      err_ret("couldn't execute: %s", buf);
      exit(127);
    }

    /* parent */
    if ((pid = waitpid(pid, &status, 0)) < 0)
      err_sys("waitpid error");
  }
  exit(0);
}
