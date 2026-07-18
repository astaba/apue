/* =========================================================================
 * Created on: <Thu Jul 16 12:04:29 +01 2026>
 * Time-stamp: <Thu Jul 16 12:06:01 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/signals/systest2.c -
 *
 * Figure 10.26: Using system to invoke the ed editor
 * ========================================================================= */
#include "apue.h"

static void sig_int(int signo) { printf("caught SIGINT\n"); }

static void sig_chld(int signo) { printf("caught SIGCHLD\n"); }

int main(void) {
  if (signal(SIGINT, sig_int) == SIG_ERR)
    err_sys("signal(SIGINT) error");
  if (signal(SIGCHLD, sig_chld) == SIG_ERR)
    err_sys("signal(SIGCHLD) error");
  if (system("/bin/ed") < 0)
    err_sys("system() error");
  exit(0);
}
