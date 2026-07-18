/* =========================================================================
 * Created on: <Fri Jul 17 15:40:27 +01 2026>
 * Time-stamp: <Fri Jul 17 15:42:52 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/termios/csize.c -
 *
 * Figure 18.11 Example of tcgetattr and tcsetattr
 * ========================================================================= */
#include "apue.h"
#include <termios.h>

int main(void) {
  struct termios term;

  if (tcgetattr(STDIN_FILENO, &term) < 0)
    err_sys("tcgetattr error");

  switch (term.c_cflag & CSIZE) {
  case CS5:
    printf("5 bits/byte\n");
    break;
  case CS6:
    printf("6 bits/byte\n");
    break;
  case CS7:
    printf("7 bits/byte\n");
    break;
  case CS8:
    printf("8 bits/byte\n");
    break;
  default:
    printf("unknown bits/byte\n");
  }

  term.c_cflag &= ~CSIZE; /* zero out the bits */
  term.c_cflag |= CS8;    /* set 8 bits/byte */
  if (tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
    err_sys("tcsetattr error");

  exit(0);
}
