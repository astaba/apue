/* =========================================================================
 * Created on: <Fri Jul 17 15:40:57 +01 2026>
 * Time-stamp: <Fri Jul 17 15:42:52 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/termios/t_isatty.c -
 *
 * Figure 18.14 Test the isatty function
 * ========================================================================= */
#include "apue.h"

int main(void) {
  printf("fd 0: %s\n", isatty(0) ? "tty" : "not a tty");
  printf("fd 1: %s\n", isatty(1) ? "tty" : "not a tty");
  printf("fd 2: %s\n", isatty(2) ? "tty" : "not a tty");
  exit(0);
}
