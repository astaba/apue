/* =========================================================================
 * Created on: <Thu Jul 16 03:43:54 +01 2026>
 * Time-stamp: <Fri Jul 17 14:05:29 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/exercises/getpwsvr4.c -
 *
 * Figure C.5 [[file:../datafiles/README.org::#exercise-6-2]] Solution.
 * 
 * Print encrypted password under Linux and Solaris
 * ========================================================================= */
#include "apue.h"
#include <shadow.h>

int main(void) /* Linux/Solaris version */
{
  struct spwd *ptr;

  if ((ptr = getspnam("sar")) == NULL)
    err_sys("getspnam error");
  printf("sp_pwdp = %s\n", ptr->sp_pwdp == NULL || ptr->sp_pwdp[0] == 0
                               ? "(null)"
                               : ptr->sp_pwdp);
  exit(0);
}
