/* =========================================================================
 * Created on: <Fri Jul 17 14:50:02 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:17 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc1/myuclc.c -
 *
 * Figure 15.14 Filter to convert uppercase characters to lowercase
 * ========================================================================= */
#include "apue.h"
#include <ctype.h>

int main(void) {
  int c;

  while ((c = getchar()) != EOF) {
    if (isupper(c))
      c = tolower(c);
    if (putchar(c) == EOF)
      err_sys("output error");
    if (c == '\n')
      fflush(stdout);
  }
  exit(0);
}
