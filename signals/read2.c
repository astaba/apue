/* =========================================================================
 * Created on: <Fri Jul 17 14:39:41 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:19 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/signals/read2.c -
 *
 * Figure 10.11 Calling read with a timeout, using longjmp
 * ========================================================================= */
#include "apue.h"
#include <setjmp.h>

static void sig_alrm(int);
static jmp_buf env_alrm;

int main(void) {
  int n;
  char line[MAXLINE];

  if (signal(SIGALRM, sig_alrm) == SIG_ERR)
    err_sys("signal(SIGALRM) error");
  if (setjmp(env_alrm) != 0)
    err_quit("read timeout");

  alarm(10);
  if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
    err_sys("read error");
  alarm(0);

  write(STDOUT_FILENO, line, n);
  exit(0);
}

static void sig_alrm(int signo) { longjmp(env_alrm, 1); }
