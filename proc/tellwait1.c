/* =========================================================================
 * Created on: <Sat Jul 11 21:53:43 +01 2026>
 * Time-stamp: <Tue Jul 14 18:26:25 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/proc/tellwait1.c -
 *
 * Figure 8.12: NOTICE: We set the standard output unbuffered, so
 * every character output generates a write. The goal in this example
 * is to allow the kernel to switch between the two processes as often
 * as possible to demonstrate the race condition. (If we didn’t do
 * this, we might never see any interleaving output typical of race
 * conditions.)
 * ========================================================================= */
#include "apue.h"

static void charatatime(char *);

int main(void) {
  pid_t pid;

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) {
    charatatime("output from child\n");
  } else {
    charatatime("OUTPUT FROM PARENT\n");
  }
  exit(0);
}

static void charatatime(char *str) {
  char *ptr;
  int c;

  setbuf(stdout, NULL); /* HACK: set unbuffered */
  for (ptr = str; (c = *ptr++) != 0;)
    putc(c, stdout);
}
