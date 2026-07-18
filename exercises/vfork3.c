/* =========================================================================
 * Created on: <Thu Jul 16 04:44:44 +01 2026>
 * Time-stamp: <Fri Jul 17 14:05:28 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/exercises/vfork3.c -
 *
 * Figure C.8 [[file:../proc/README.org::#exercise-8-2]] Solution.
 * 
 * Incorrect use of vfork
 * ========================================================================= */
#include "apue.h"

static void f1(void), f2(void);

int main(void) {
  f1();
  f2();
  _exit(0);
}

static void f1(void) {
  pid_t pid;

  if ((pid = vfork()) < 0)
    err_sys("vfork error");
  /* child and parent both return */
}

static void f2(void) {
  char buf[1000]; /* automatic variables */
  int i;

  for (i = 0; i < sizeof(buf); i++)
    buf[i] = 0;
}
