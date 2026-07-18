/* =========================================================================
 * Created on: <Fri Jul 17 15:27:29 +01 2026>
 * Time-stamp: <Fri Jul 17 15:34:12 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/lib/sendfd.c -
 *
 * Figure 17.13 Sending a file descriptor over a UNIX domain socket
 * ========================================================================= */
#include "apue.h"
#include <sys/socket.h>

/* size of control buffer to send/recv one file descriptor */
#define CONTROLLEN CMSG_LEN(sizeof(int))

static struct cmsghdr *cmptr = NULL; /* malloc'ed first time */

/*
 * Pass a file descriptor to another process.
 * If fd<0, then -fd is sent back instead as the error status.
 */
int send_fd(int fd, int fd_to_send) {
  struct iovec iov[1];
  struct msghdr msg;
  char buf[2]; /* send_fd()/recv_fd() 2-byte protocol */

  iov[0].iov_base = buf;
  iov[0].iov_len = 2;
  msg.msg_iov = iov;
  msg.msg_iovlen = 1;
  msg.msg_name = NULL;
  msg.msg_namelen = 0;

  if (fd_to_send < 0) {
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
    buf[1] = -fd_to_send; /* nonzero status means error */
    if (buf[1] == 0)
      buf[1] = 1; /* -256, etc. would screw up protocol */
  } else {
    if (cmptr == NULL && (cmptr = malloc(CONTROLLEN)) == NULL)
      return (-1);
    cmptr->cmsg_level = SOL_SOCKET;
    cmptr->cmsg_type = SCM_RIGHTS;
    cmptr->cmsg_len = CONTROLLEN;
    msg.msg_control = cmptr;
    msg.msg_controllen = CONTROLLEN;
    *(int *)CMSG_DATA(cmptr) = fd_to_send; /* the fd to pass */
    buf[1] = 0;                            /* zero status means OK */
  }

  buf[0] = 0; /* null byte flag to recv_fd() */
  if (sendmsg(fd, &msg, 0) != 2)
    return (-1);
  return (0);
}
