/* =========================================================================
 * Created on: <Fri Jul 17 14:40:06 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:19 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/lib/prmask.c -
 *
 * Figure 10.14 Print the signal mask for the process
 * ========================================================================= */
#include "apue.h"
#include <errno.h>

void pr_mask(const char *str) {
  sigset_t sigset;
  int errno_save;

  errno_save = errno; /* we can be called by signal handlers */
  if (sigprocmask(0, NULL, &sigset) < 0) {
    err_ret("sigprocmask error");
  } else {
    printf("%s", str);
    if (sigismember(&sigset, SIGINT))
      printf(" SIGINT");
    if (sigismember(&sigset, SIGQUIT))
      printf(" SIGQUIT");
    if (sigismember(&sigset, SIGUSR1))
      printf(" SIGUSR1");
    if (sigismember(&sigset, SIGALRM))
      printf(" SIGALRM");

    /* remaining signals can go here  */

    printf("\n");
  }

  errno = errno_save; /* restore errno */
}
