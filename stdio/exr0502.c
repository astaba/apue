/* =========================================================================
 * Created on: <Fri Jun 26 17:14:54 +01 2026>
 * Time-stamp: <Fri Jun 26 17:19:11 +01 2026 by owner>
 * Author    : owner
 * Desc      : ~/coding/c_prog/apue.3e/stdio/exr0502.c -
 *
 * Exercise 5.2: Type in the program that copies a file using
 * line-at-a-time I/O (fgets and fputs) from
 * [[file:fgetsfputs.c][Figure 5.5]], but use a MAXLINE of 4. What
 * happens if you copy lines that exceed this length? Explain what is
 * happening.
 * ========================================================================= */
#include "../include/apue.h"

#define MAXLINE_4 4

int main(void) {
  char buf[MAXLINE_4];

  while (fgets(buf, MAXLINE_4, stdin) != NULL)
    if (fputs(buf, stdout) == EOF)
      err_sys("output error");

  if (ferror(stdin))
    err_sys("input error");

  exit(0);
}
