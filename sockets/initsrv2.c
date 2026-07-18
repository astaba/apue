/* =========================================================================
 * Created on: <Fri Jul 17 14:52:49 +01 2026>
 * Time-stamp: <Fri Jul 17 14:53:55 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/sockets/initsrv2.c -
 *
 * Figure 16.22 Initialize a socket endpoint for use by a server with address
 * reuse
 * ========================================================================= */
#include "apue.h"
#include <errno.h>
#include <sys/socket.h>

int initserver(int type, const struct sockaddr *addr, socklen_t alen,
               int qlen) {
  int fd, err;
  int reuse = 1;

  if ((fd = socket(addr->sa_family, type, 0)) < 0)
    return (-1);
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0)
    goto errout;
  if (bind(fd, addr, alen) < 0)
    goto errout;
  if (type == SOCK_STREAM || type == SOCK_SEQPACKET)
    if (listen(fd, qlen) < 0)
      goto errout;
  return (fd);

errout:
  err = errno;
  close(fd);
  errno = err;
  return (-1);
}
