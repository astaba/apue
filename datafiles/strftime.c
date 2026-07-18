/* =========================================================================
 * Created on: <Sun Jun 28 18:50:30 +01 2026>
 * Time-stamp: <Sun Jun 28 18:52:27 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/datafiles/strftime.c -
 *
 * Figure 6.11: This program shows how to use several of the time
 * functions discussed in this chapter. In particular, it shows how
 * strftime can be used to print a string containing the current date
 * and time.
 * ========================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  time_t t;
  struct tm *tmp;
  char buf1[16];
  char buf2[64];

  time(&t);
  tmp = localtime(&t);

  if (strftime(buf1, 16, "time and date: %r, %a %b %d, %Y", tmp) == 0)
    printf("buffer length 16 is too small\n");
  else
    printf("%s\n", buf1);

  if (strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0)
    printf("buffer length 64 is too small\n");
  else
    printf("%s\n", buf2);

  exit(0);
}
