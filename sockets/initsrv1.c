/* =========================================================================
 * Created on: <Fri Jul 17 14:51:57 +01 2026>
 * Time-stamp: <Fri Jul 17 14:53:55 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/sockets/initsrv1.c -
 *
 * Figure 16.12 Initialize a socket endpoint for use by a server
 * ========================================================================= */
#include "apue.h"
#include <errno.h>
#include <sys/socket.h>

int initserver(int type, const struct sockaddr *addr, socklen_t alen,
               int qlen) {
  int fd;
  int err = 0;

  if ((fd = socket(addr->sa_family, type, 0)) < 0)
    return (-1);
  if (bind(fd, addr, alen) < 0)
    goto errout;
  if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
    if (listen(fd, qlen) < 0)
      goto errout;
  }
  return (fd);

errout:
  err = errno;
  close(fd);
  errno = err;
  return (-1);
}
