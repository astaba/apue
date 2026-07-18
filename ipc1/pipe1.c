/* =========================================================================
 * Created on: <Fri Jul 17 14:49:03 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:17 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc1/pipe1.c -
 *
 * Figure 15.5 Send data from parent to child over a pipe
 * ========================================================================= */
#include "apue.h"

int main(void) {
  int n;
  int fd[2];
  pid_t pid;
  char line[MAXLINE];

  if (pipe(fd) < 0)
    err_sys("pipe error");
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid > 0) { /* parent */
    close(fd[0]);
    write(fd[1], "hello world\n", 12);
  } else { /* child */
    close(fd[1]);
    n = read(fd[0], line, MAXLINE);
    write(STDOUT_FILENO, line, n);
  }
  exit(0);
}
