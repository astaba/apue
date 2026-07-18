/* =========================================================================
 * Created on: <Fri Jul 17 14:50:35 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:16 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc1/add2stdio.c -
 *
 * Figure 15.19 Filter to add two numbers, using standard I/O
 * ========================================================================= */
#include "apue.h"

int main(void) {
  int int1, int2;
  char line[MAXLINE];

  while (fgets(line, MAXLINE, stdin) != NULL) {
    if (sscanf(line, "%d%d", &int1, &int2) == 2) {
      if (printf("%d\n", int1 + int2) == EOF)
        err_sys("printf error");
    } else {
      if (printf("invalid args\n") == EOF)
        err_sys("printf error");
    }
  }
  exit(0);
}
