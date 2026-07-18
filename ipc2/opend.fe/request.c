/* =========================================================================
 * Created on: <Fri Jul 17 15:35:48 +01 2026>
 * Time-stamp: <Fri Jul 17 15:36:54 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc2/opend.fe/request.c -
 *
 * Figure 17.22 The handle_request function, version 1
 * ========================================================================= */
#include "opend.h"
#include <fcntl.h>

void handle_request(char *buf, int nread, int fd) {
  int newfd;

  if (buf[nread - 1] != 0) {
    snprintf(errmsg, MAXLINE - 1, "request not null terminated: %*.*s\n", nread,
             nread, buf);
    send_err(fd, -1, errmsg);
    return;
  }
  if (buf_args(buf, cli_args) < 0) { /* parse args & set options */
    send_err(fd, -1, errmsg);
    return;
  }
  if ((newfd = open(pathname, oflag)) < 0) {
    snprintf(errmsg, MAXLINE - 1, "can't open %s: %s\n", pathname,
             strerror(errno));
    send_err(fd, -1, errmsg);
    return;
  }
  if (send_fd(fd, newfd) < 0) /* send the descriptor */
    err_sys("send_fd error");
  close(newfd); /* we're done with descriptor */
}
