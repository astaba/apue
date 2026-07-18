/* =========================================================================
 * Created on: <Fri Jul 17 14:39:28 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:19 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/signals/read1.c -
 *
 * Figure 10.10 Calling read with a timeout
 * ========================================================================= */
#include "apue.h"

static void sig_alrm(int);

int main(void) {
  int n;
  char line[MAXLINE];

  if (signal(SIGALRM, sig_alrm) == SIG_ERR)
    err_sys("signal(SIGALRM) error");

  alarm(10);
  if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
    err_sys("read error");
  alarm(0);

  write(STDOUT_FILENO, line, n);
  exit(0);
}

static void sig_alrm(int signo) {
  /* nothing to do, just return to interrupt the read */
}
