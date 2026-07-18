/* =========================================================================
 * Created on: <Fri Jul 17 14:39:54 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:19 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/signals/setops.c -
 *
 * Figure 10.12 An implementation of sigaddset, sigdelset, and sigismember
 * ========================================================================= */
#include <errno.h>
#include <signal.h>

/*
 * <signal.h> usually defines NSIG to include signal number 0.
 */
#define SIGBAD(signo) ((signo) <= 0 || (signo) >= NSIG)

int sigaddset(sigset_t *set, int signo) {
  if (SIGBAD(signo)) {
    errno = EINVAL;
    return (-1);
  }
  *set |= 1 << (signo - 1); /* turn bit on */
  return (0);
}

int sigdelset(sigset_t *set, int signo) {
  if (SIGBAD(signo)) {
    errno = EINVAL;
    return (-1);
  }
  *set &= ~(1 << (signo - 1)); /* turn bit off */
  return (0);
}

int sigismember(const sigset_t *set, int signo) {
  if (SIGBAD(signo)) {
    errno = EINVAL;
    return (-1);
  }
  return ((*set & (1 << (signo - 1))) != 0);
}
