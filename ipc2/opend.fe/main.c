/* =========================================================================
 * Created on: <Fri Jul 17 15:35:08 +01 2026>
 * Time-stamp: <Fri Jul 17 15:36:54 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc2/opend.fe/main.c -
 *
 * Figure 17.21 The server main function, version 1
 * ========================================================================= */
#include "opend.h"

char errmsg[MAXLINE];
int oflag;
char *pathname;

int main(void) {
  int nread;
  char buf[MAXLINE];

  for (;;) { /* read arg buffer from client, process request */
    if ((nread = read(STDIN_FILENO, buf, MAXLINE)) < 0)
      err_sys("read error on stream pipe");
    else if (nread == 0)
      break; /* client has closed the stream pipe */
    handle_request(buf, nread, STDOUT_FILENO);
  }
  exit(0);
}
