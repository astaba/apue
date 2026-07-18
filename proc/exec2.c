/* =========================================================================
 * Created on: <Wed Jul 15 13:43:10 +01 2026>
 * Time-stamp: <Thu Jul 16 13:24:50 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/proc/exec2.c -
 *
 * Figure 8.20 A program that execs an interpreter file
 *
 * Prior to run make sure to build ~/bin/echoarg and ~/bin/testinterp:
 * 
 *	$ make utility
 *
 * ========================================================================= */
#include "apue.h"
#include <sys/wait.h>

int main(void) {
  pid_t pid;

  if ((pid = fork()) < 0) {
    err_sys("fork error");

  } else if (pid == 0) { /* child */
    if (execl("/home/owner/bin/testinterp", "testinterp", "myarg1", "MY ARG2",
              (char *)0) < 0)
      err_sys("execl error");
  }

  if (waitpid(pid, NULL, 0) < 0) /* parent */
    err_sys("waitpid error");
  exit(0);
}
