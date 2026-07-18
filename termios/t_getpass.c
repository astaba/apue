/* =========================================================================
 * Created on: <Fri Jul 17 15:41:41 +01 2026>
 * Time-stamp: <Fri Jul 17 15:42:52 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/termios/t_getpass.c -
 *
 * Figure 18.18 Call the getpass function
 * ========================================================================= */
#include "apue.h"

char *getpass(const char *);

int main(void) {
  char *ptr;

  if ((ptr = getpass("Enter password:")) == NULL)
    err_sys("getpass error");
  printf("password: %s\n", ptr);

  /* now use password (probably encrypt it) ... */

  while (*ptr != 0)
    *ptr++ = 0; /* zero it out when we're done with it */
  exit(0);
}
