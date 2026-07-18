/* =========================================================================
 * Created on: <Fri Jul 17 14:37:41 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:19 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/signals/sigusr.c -
 *
 * Figure 10.2 Simple program to catch SIGUSR1 and SIGUSR2
 * ========================================================================= */
#include "apue.h"

static void sig_usr(int); /* one handler for both signals */

int main(void) {
  if (signal(SIGUSR1, sig_usr) == SIG_ERR)
    err_sys("can't catch SIGUSR1");
  if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    err_sys("can't catch SIGUSR2");
  for (;;)
    pause();
}

static void sig_usr(int signo) /* argument is signal number */
{
  if (signo == SIGUSR1)
    printf("received SIGUSR1\n");
  else if (signo == SIGUSR2)
    printf("received SIGUSR2\n");
  else
    err_dump("received signal %d\n", signo);
}
