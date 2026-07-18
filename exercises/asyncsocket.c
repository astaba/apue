/* =========================================================================
 * Created on: <Thu Jul 16 05:31:04 +01 2026>
 * Time-stamp: <Fri Jul 17 14:05:28 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/exercises/asyncsocket.c -
 *
 * Figure C.23 [[file:../sockets/README.org::#exercise-16-6]] Solution.
 * 
 * Enable and disable asynchronous socket I/O
 * ========================================================================= */
#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#if defined(BSD) || defined(MACOS) || defined(SOLARIS)
#include <sys/filio.h>
#endif

int setasync(int sockfd) {
  int n;

  if (fcntl(sockfd, F_SETOWN, getpid()) < 0)
    return (-1);
  n = 1;
  if (ioctl(sockfd, FIOASYNC, &n) < 0)
    return (-1);
  return (0);
}

int clrasync(int sockfd) {
  int n;

  n = 0;
  if (ioctl(sockfd, FIOASYNC, &n) < 0)
    return (-1);
  return (0);
}
