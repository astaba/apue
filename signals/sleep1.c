/* =========================================================================
 * Created on: <Fri Jul 17 14:38:30 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:19 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/signals/sleep1.c -
 *
 * Figure 10.7 Simple, incomplete implementation of sleep
 * ========================================================================= */
#include <signal.h>
#include <unistd.h>

static void sig_alrm(int signo) {
  /* nothing to do, just return to wake up the pause */
}

unsigned int sleep1(unsigned int seconds) {
  if (signal(SIGALRM, sig_alrm) == SIG_ERR)
    return (seconds);
  alarm(seconds);    /* start the timer */
  pause();           /* next caught signal wakes us up */
  return (alarm(0)); /* turn off timer, return unslept time */
}
