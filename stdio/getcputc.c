/* =========================================================================
 * Created on: <Tue Jun 23 13:00:58 +01 2026>
 * Time-stamp: <Mon Jul 13 12:37:25 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/stdio/getcputc.c -
 *
 * Figure 5.4: Copy standard input to standard output using getc and
 * putc
 * ========================================================================= */
#include "apue.h"

int main(void) {
  int c;

  while ((c = getc(stdin)) != EOF)
    if (putc(c, stdout) == EOF)
      err_sys("output error");

  if (ferror(stdin))
    err_sys("input error");

  exit(0);
}
