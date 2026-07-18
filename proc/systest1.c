/* =========================================================================
 * Created on: <Wed Jul 15 19:09:49 +01 2026>
 * Time-stamp: <Wed Jul 15 19:11:06 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/proc/systest1.c -
 *
 * Figure 8.23 Calling the [[file:system.c][system]] function
 * ========================================================================= */
#include "apue.h"
#include <sys/wait.h>

int main(void) {
  int status;

  if ((status = system("date")) < 0)
    err_sys("system() error");

  pr_exit(status);

  if ((status = system("nosuchcommand")) < 0)
    err_sys("system() error");

  pr_exit(status);

  if ((status = system("who; exit 44")) < 0)
    err_sys("system() error");

  pr_exit(status);

  exit(0);
}
