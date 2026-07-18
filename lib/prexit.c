/* =========================================================================
 * Created on: <Thu Jul 09 12:01:36 +01 2026>
 * Time-stamp: <Thu Jul  9 17:37:50 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/lib/prexit.c -
 *
 * Figure 8.5: This function uses the macros from
 * [[file:../proc/README.org::#figure-8-4][Figure 8.4]] to print a
 * description of the termination status. We’ll call this function
 * from numerous programs in the text. Note that this function handles
 * the WCOREDUMP macro, if it is defined.
 * ========================================================================= */
#include "apue.h"
#include <sys/wait.h>

void pr_exit(int status) {
  if (WIFEXITED(status))
    printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
  else if (WIFSIGNALED(status))
    printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
           WCOREDUMP(status) ? " (core file generated)" : "");
#else
           "");
#endif
  else if (WIFSTOPPED(status))
    printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}
