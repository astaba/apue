/* =========================================================================
 * Created on: <Fri Jul 17 15:41:53 +01 2026>
 * Time-stamp: <Fri Jul 17 15:42:52 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/termios/t_raw.c -
 *
 * Figure 18.21 Test raw and cbreak terminal modes
 * ========================================================================= */
#include "apue.h"

static void sig_catch(int signo) {
  printf("signal caught\n");
  tty_reset(STDIN_FILENO);
  exit(0);
}

int main(void) {
  int i;
  char c;

  if (signal(SIGINT, sig_catch) == SIG_ERR) /* catch signals */
    err_sys("signal(SIGINT) error");
  if (signal(SIGQUIT, sig_catch) == SIG_ERR)
    err_sys("signal(SIGQUIT) error");
  if (signal(SIGTERM, sig_catch) == SIG_ERR)
    err_sys("signal(SIGTERM) error");

  if (tty_raw(STDIN_FILENO) < 0)
    err_sys("tty_raw error");
  printf("Enter raw mode characters, terminate with DELETE\n");
  while ((i = read(STDIN_FILENO, &c, 1)) == 1) {
    if ((c &= 255) == 0177) /* 0177 = ASCII DELETE */
      break;
    printf("%o\n", c);
  }
  if (tty_reset(STDIN_FILENO) < 0)
    err_sys("tty_reset error");
  if (i <= 0)
    err_sys("read error");
  if (tty_cbreak(STDIN_FILENO) < 0)
    err_sys("tty_cbreak error");
  printf("\nEnter cbreak mode characters, terminate with SIGINT\n");
  while ((i = read(STDIN_FILENO, &c, 1)) == 1) {
    c &= 255;
    printf("%o\n", c);
  }
  if (tty_reset(STDIN_FILENO) < 0)
    err_sys("tty_reset error");
  if (i <= 0)
    err_sys("read error");

  exit(0);
}
