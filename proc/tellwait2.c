/* =========================================================================
 * Created on: <Sat Jul 11 21:56:15 +01 2026>
 * Time-stamp: <Sun Jul 12 01:56:24 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/proc/tellwait2.c -
 *
 * Figure 8.13: Modification of [[file:tellwait1.c][Figure 8.12]] to
 * avoid race condition.
 *
 * See also [[file:../lib/tellwait.c][Figure 10.24]]
 * ========================================================================= */
#include "apue.h"

static void charatatime(char *);

int main(void) {
  pid_t pid;

  TELL_WAIT();

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) {
    WAIT_PARENT(); /* parent goes first */
    charatatime("output from child\n");
  } else {
    charatatime("OUTPUT FROM PARENT\n");
    TELL_CHILD(pid);
  }
  exit(0);
}

static void charatatime(char *str) {
  char *ptr;
  int c;

  setbuf(stdout, NULL); /* set unbuffered */
  for (ptr = str; (c = *ptr++) != 0;)
    putc(c, stdout);
}
