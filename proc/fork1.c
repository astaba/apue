/* =========================================================================
 * Created on: <Wed Jul 08 12:56:18 +01 2026>
 * Time-stamp: <Wed Jul  8 13:10:28 +01 2026 by owner>
 * Author    : owner
 * Desc      : ~/coding/c_prog/apue.3e/proc/fork1.c -
 *
 * Figure 8.1: This program demonstrates the fork function, showing
 * how changes to variables in a child process do not affect the value
 * of the variables in the parent process.
 * ========================================================================= */
#include "apue.h"

int globvar = 6; /* external variable in initialized data */
char buf[] = "a write() to stdout\n";

int main(void) {
  int var; /* automatic variable on the stack */
  pid_t pid;

  var = 88;
  if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
    err_sys("write error");
  printf("a printf() before fork\n"); /* we don't flush stdout */

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) { /* child */
    globvar++;           /* modify variables */
    var++;
  } else {
    sleep(2); /* parent */
  }

  printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
  exit(0);
}
