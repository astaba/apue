/* =========================================================================
 * Created on: <Fri Jul 17 15:40:35 +01 2026>
 * Time-stamp: <Fri Jul 17 15:42:52 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/termios/ctermid.c -
 *
 * Figure 18.12 Implementation of POSIX.1 ctermid function
 * ========================================================================= */
#include <stdio.h>
#include <string.h>

static char ctermid_name[L_ctermid];

char *ctermid(char *str) {
  if (str == NULL)
    str = ctermid_name;
  return (strcpy(str, "/dev/tty")); /* strcpy() returns str */
}
