/* =========================================================================
 * Created on: <Fri Jul 17 14:50:10 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:17 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc1/popen1.c -
 *
 * Figure 15.15 Invoke uppercase/lowercase filter to read commands
 * ========================================================================= */
#include "apue.h"
#include <sys/wait.h>

int main(void) {
  char line[MAXLINE];
  FILE *fpin;

  if ((fpin = popen("myuclc", "r")) == NULL)
    err_sys("popen error");
  for (;;) {
    fputs("prompt> ", stdout);
    fflush(stdout);
    if (fgets(line, MAXLINE, fpin) == NULL) /* read from pipe */
      break;
    if (fputs(line, stdout) == EOF)
      err_sys("fputs error to pipe");
  }
  if (pclose(fpin) == -1)
    err_sys("pclose error");
  putchar('\n');
  exit(0);
}
