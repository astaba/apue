/* =========================================================================
 * Created on: <Wed Jul 08 15:54:00 +01 2026>
 * Time-stamp: <Wed Jul  8 16:16:28 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/proc/vfork1.c -
 *
 * Figure 8.3 Example of vfork function
 * ========================================================================= */
#include "apue.h"

int globvar = 6; /* external variable in initialized data */

int main(void) {
  int var; /* automatic variable on the stack */
  pid_t pid;

  var = 88;
  printf("before vfork\n"); /* we don't flush stdio */
  if ((pid = vfork()) < 0) {
    err_sys("vfork error");
  } else if (pid == 0) { /* child */
    globvar++;           /* modify parent's variables */
    var++;
    _exit(0); /* child terminates */
  }

  /* parent continues here */
  printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
  exit(0);
}
