/* =========================================================================
 * Created on: <Wed Jul 15 02:13:20 +01 2026>
 * Time-stamp: <Thu Jul 16 13:20:59 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/proc/exec1.c -
 *
 * Figure 8.16: this progrm demonstrates the exec functions.
 *
 * Prior to run make sure to build ~/bin/echoall:
 *
 *	$ make utility
 *
 * ========================================================================= */
#include "apue.h"
#include <sys/wait.h>

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(void) {
  pid_t pid;

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) { /* specify pathname, specify environment */
    if (execle("/home/owner/bin/echoall", "echoall", "myarg1", "MY ARG2",
               (char *)0, env_init) < 0)
      err_sys("execle error");
  }

  if (waitpid(pid, NULL, 0) < 0)
    err_sys("wait error");

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) { /* specify filename, inherit environment */
    if (execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0)
      err_sys("execlp error");
  }

  exit(0);
}
