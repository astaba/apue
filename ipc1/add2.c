/* =========================================================================
 * Created on: <Fri Jul 17 14:50:18 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:16 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc1/add2.c -
 *
 * Figure 15.17 Simple filter to add two numbers
 * ========================================================================= */
#include "apue.h"

int main(void) {
  int n, int1, int2;
  char line[MAXLINE];

  while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0) {
    line[n] = 0; /* null terminate */
    if (sscanf(line, "%d%d", &int1, &int2) == 2) {
      sprintf(line, "%d\n", int1 + int2);
      n = strlen(line);
      if (write(STDOUT_FILENO, line, n) != n)
        err_sys("write error");
    } else {
      if (write(STDOUT_FILENO, "invalid args\n", 13) != 13)
        err_sys("write error");
    }
  }
  exit(0);
}
