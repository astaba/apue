/* =========================================================================
 * Created on: <Fri Jul 17 14:19:09 +01 2026>
 * Time-stamp: <Fri Jul 17 14:22:20 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/intro/getcputc.c -
 *
 * Figure 1.5: Buffered I/O behaving right like unbuffered I/O
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
