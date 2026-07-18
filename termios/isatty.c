/* =========================================================================
 * Created on: <Fri Jul 17 15:40:46 +01 2026>
 * Time-stamp: <Fri Jul 17 15:42:52 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/termios/isatty.c -
 *
 * Figure 18.13 Implementation of POSIX.1 isatty function
 * ========================================================================= */
#include <termios.h>

int isatty(int fd) {
  struct termios ts;

  return (tcgetattr(fd, &ts) != -1); /* true if no error (is a tty) */
}
