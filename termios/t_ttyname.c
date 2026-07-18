/* =========================================================================
 * Created on: <Fri Jul 17 15:41:21 +01 2026>
 * Time-stamp: <Fri Jul 17 15:42:52 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/termios/t_ttyname.c -
 *
 * Figure 18.16 Test the ttyname function
 * ========================================================================= */
#include "apue.h"

int main(void) {
  char *name;
  if (isatty(0)) {
    name = ttyname(0);
    if (name == NULL)
      name = "undefined";
  } else {
    name = "not a tty";
  }
  printf("fd 0: %s\n", name);

  if (isatty(1)) {
    name = ttyname(1);
    if (name == NULL)
      name = "undefined";
  } else {
    name = "not a tty";
  }
  printf("fd 1: %s\n", name);

  if (isatty(2)) {
    name = ttyname(2);
    if (name == NULL)
      name = "undefined";
  } else {
    name = "not a tty";
  }
  printf("fd 2: %s\n", name);

  exit(0);
}
