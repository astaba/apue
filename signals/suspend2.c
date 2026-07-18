/* =========================================================================
 * Created on: <Fri Jul 17 14:41:14 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:18 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/signals/suspend2.c -
 *
 * Figure 10.23 Using sigsuspend to wait for a global variable to be set
 * ========================================================================= */
#include "apue.h"

volatile sig_atomic_t quitflag; /* set nonzero by signal handler */

static void sig_int(int signo) /* one signal handler for SIGINT and SIGQUIT */
{
  if (signo == SIGINT)
    printf("\ninterrupt\n");
  else if (signo == SIGQUIT)
    quitflag = 1; /* set flag for main loop */
}

int main(void) {
  sigset_t newmask, oldmask, zeromask;

  if (signal(SIGINT, sig_int) == SIG_ERR)
    err_sys("signal(SIGINT) error");
  if (signal(SIGQUIT, sig_int) == SIG_ERR)
    err_sys("signal(SIGQUIT) error");

  sigemptyset(&zeromask);
  sigemptyset(&newmask);
  sigaddset(&newmask, SIGQUIT);

  /*
   * Block SIGQUIT and save current signal mask.
   */
  if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    err_sys("SIG_BLOCK error");

  while (quitflag == 0)
    sigsuspend(&zeromask);

  /*
   * SIGQUIT has been caught and is now blocked; do whatever.
   */
  quitflag = 0;

  /*
   * Reset signal mask which unblocks SIGQUIT.
   */
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    err_sys("SIG_SETMASK error");

  exit(0);
}
