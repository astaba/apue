/* =========================================================================
 * Created on: <Fri Jul 17 19:10:12 +01 2026>
 * Time-stamp: <Fri Jul 17 19:47:43 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc2/open/main.c -
 *
 * Figure 17.18.alt The client main function, version 1
 * ========================================================================= */
#include "open.h"
#include <fcntl.h>

#define BUFFSIZE 8192

int main(int argc, char *argv[]) {
  int n, fd;
  char buf[BUFFSIZE], line[MAXLINE];

  /* read filename to cat from stdin */
  while (fgets(line, MAXLINE, stdin) != NULL) {
    if (line[strlen(line) - 1] == '\n')
      line[strlen(line) - 1] = 0; /* replace newline with null */

    /* open the file */
    if ((fd = csopen(line, O_RDONLY)) < 0)
      continue; /* csopen() prints error from server */

    /* and cat to stdout */
    while ((n = read(fd, buf, BUFFSIZE)) > 0)
      if (write(STDOUT_FILENO, buf, n) != n)
        err_sys("write error");
    if (n < 0)
      err_sys("read error");
    close(fd);
  }

  exit(0);
}
