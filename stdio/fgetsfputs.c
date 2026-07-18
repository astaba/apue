/* =========================================================================
 * Created on: <Tue Jun 23 13:02:49 +01 2026>
 * Time-stamp: <Tue Jun 23 13:03:53 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/stdio/fgetsfputs.c -
 *
 * Figure 5.5 Copy standard input to standard output using fgets and
 * fputs.
 * ========================================================================= */
#include "apue.h"

int main(void) {
  char buf[MAXLINE];

  while (fgets(buf, MAXLINE, stdin) != NULL)
    if (fputs(buf, stdout) == EOF)
      err_sys("output error");

  if (ferror(stdin))
    err_sys("input error");

  exit(0);
}
