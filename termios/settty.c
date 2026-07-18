/* =========================================================================
 * Created on: <Fri Jul 17 15:40:21 +01 2026>
 * Time-stamp: <Fri Jul 17 15:42:52 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/termios/settty.c -
 *
 * Figure 18.10 Disable interrupt character and change end-of-file character
 * ========================================================================= */
#include "apue.h"
#include <termios.h>

int main(void) {
  struct termios term;
  long vdisable;

  if (isatty(STDIN_FILENO) == 0)
    err_quit("standard input is not a terminal device");

  if ((vdisable = fpathconf(STDIN_FILENO, _PC_VDISABLE)) < 0)
    err_quit("fpathconf error or _POSIX_VDISABLE not in effect");

  if (tcgetattr(STDIN_FILENO, &term) < 0) /* fetch tty state */
    err_sys("tcgetattr error");

  term.c_cc[VINTR] = vdisable; /* disable INTR character */
  term.c_cc[VEOF] = 2;         /* EOF is Control-B */

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) < 0)
    err_sys("tcsetattr error");

  exit(0);
}
