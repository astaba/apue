/* =========================================================================
 * Created on: <Fri Jul 17 14:38:51 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:19 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/signals/sleep2.c -
 *
 * Figure 10.8 Another (imperfect) implementation of sleep
 * ========================================================================= */
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

static jmp_buf env_alrm;

static void sig_alrm(int signo) { longjmp(env_alrm, 1); }

unsigned int sleep2(unsigned int seconds) {
  if (signal(SIGALRM, sig_alrm) == SIG_ERR)
    return (seconds);
  if (setjmp(env_alrm) == 0) {
    alarm(seconds); /* start the timer */
    pause();        /* next caught signal wakes us up */
  }
  return (alarm(0)); /* turn off timer, return unslept time */
}
