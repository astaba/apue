/* =========================================================================
 * Created on: <Fri Jul 17 15:58:58 +01 2026>
 * Time-stamp: <Fri Jul 17 15:59:18 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/lib/senderr.c -
 *
 * Figure 17.12 The send_err function
 * ========================================================================= */
#include "apue.h"

/*
 * Used when we had planned to send an fd using send_fd(),
 * but encountered an error instead.  We send the error back
 * using the send_fd()/recv_fd() protocol.
 */
int send_err(int fd, int errcode, const char *msg) {
  int n;

  if ((n = strlen(msg)) > 0)
    if (writen(fd, msg, n) != n) /* send the error message */
      return (-1);

  if (errcode >= 0)
    errcode = -1; /* must be negative */

  if (send_fd(fd, errcode) < 0)
    return (-1);

  return (0);
}
