/* =========================================================================
 * Created on: <Sun Jul 12 01:49:51 +01 2026>
 * Time-stamp: <Tue Jul 14 18:16:23 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc1/tellwait.c -
 *
 * Figure 15.7: Routines to let a parent and child synchronize
 * ========================================================================= */
#include "apue.h"

static int pfd1[2]; /* Parent writes to child waiting to read */
static int pfd2[2]; /* Child writes to parent waiting to read */

void TELL_WAIT(void) {
  if (pipe(pfd1) < 0 || pipe(pfd2) < 0)
    err_sys("pipe error");
}

void TELL_PARENT(pid_t pid) {
  if (write(pfd2[1], "c", 1) != 1)
    err_sys("write error");
}

void WAIT_PARENT(void) {
  char c;

  if (read(pfd1[0], &c, 1) != 1)
    err_sys("read error");

  if (c != 'p')
    err_quit("WAIT_PARENT: incorrect data");
}

void TELL_CHILD(pid_t pid) {
  if (write(pfd1[1], "p", 1) != 1)
    err_sys("write error");
}

void WAIT_CHILD(void) {
  char c;

  if (read(pfd2[0], &c, 1) != 1)
    err_sys("read error");

  if (c != 'c')
    err_quit("WAIT_CHILD: incorrect data");
}
