/* =========================================================================
 * Created on: <Thu Jul 16 04:05:11 +01 2026>
 * Time-stamp: <Fri Jul 17 14:05:29 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/exercises/prtime.c -
 *
 * Figure C.7 [[file:../datafiles/README.org::#exercise-6-5]] Solution.
 * 
 * Print the time and date in a format similar to date(1)
 * ========================================================================= */
#include "apue.h"
#include <time.h>

int main(void) {
  time_t caltime;
  struct tm *tm;
  char line[MAXLINE];

  if ((caltime = time(NULL)) == -1)
    err_sys("time error");
  if ((tm = localtime(&caltime)) == NULL)
    err_sys("localtime error");
  if (strftime(line, MAXLINE, "%a %b %d %X %Z %Y\n", tm) == 0)
    err_sys("strftime error");
  fputs(line, stdout);
  exit(0);
}
