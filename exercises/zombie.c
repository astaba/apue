/* =========================================================================
 * Created on: <Thu Jul 16 04:49:37 +01 2026>
 * Time-stamp: <Fri Jul 17 14:05:28 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/exercises/zombie.c -
 *
 * Figure C.10 [[file:../proc/README.org::#exercise-8-6]] Solution.
 * 
 * Create a zombie and look at its status with ps
 * ========================================================================= */
#include "apue.h"

#ifdef SOLARIS
#define PSCMD "ps -a -o pid,ppid,s,tty,comm"
#else
#define PSCMD "ps -o pid,ppid,state,tty,command"
#endif

int main(void) {
  pid_t pid;

  if ((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid == 0) /* child */
    exit(0);

  /* parent */
  sleep(4);
  system(PSCMD);

  exit(0);
}
