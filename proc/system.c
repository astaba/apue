/* =========================================================================
 * Created on: <Wed Jul 15 18:17:50 +01 2026>
 * Time-stamp: <Thu Jul 16 13:15:24 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/proc/system.c -
 *
 * Figure 8.22 The system function.
 *
 * FIXME: Missing signal handling. See updated version at
 * [[file:../signals/system.c][Figure 10.28]]
 * ========================================================================= */
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>

int system(const char *cmdstring) /* version without signal handling */
{
  pid_t pid;
  int status;

  if (cmdstring == NULL)
    return (1); /* always a command processor with UNIX */

  if ((pid = fork()) < 0) {
    status = -1;         /* probably out of processes */
  } else if (pid == 0) { /* child */
    execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
    _exit(127); /* execl error */
  } else {      /* parent */
    while (waitpid(pid, &status, 0) < 0) {
      if (errno != EINTR) {
        status = -1; /* error other than EINTR from waitpid() */
        break;
      }
    }
  }

  return (status);
}
