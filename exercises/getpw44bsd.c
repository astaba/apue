/* =========================================================================
 * Created on: <Thu Jul 16 03:46:06 +01 2026>
 * Time-stamp: <Fri Jul 17 14:05:29 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/exercises/getpw44bsd.c -
 *
 * Figure C.6 [[file:../datafiles/README.org::#exercise-6-2]] Solution.
 * 
 * Print encrypted password under FreeBSD and Mac OS X
 * ========================================================================= */
#include "apue.h"
#include <pwd.h>

int main(void) /* FreeBSD/Mac OS X version */
{
  struct passwd *ptr;

  if ((ptr = getpwnam("sar")) == NULL)
    err_sys("getpwnam error");
  printf("pw_passwd = %s\n", ptr->pw_passwd == NULL || ptr->pw_passwd[0] == 0
                                 ? "(null)"
                                 : ptr->pw_passwd);
  exit(0);
}
