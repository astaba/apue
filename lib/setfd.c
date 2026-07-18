/* =========================================================================
 * Created on: <Fri Jul 17 14:45:13 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:17 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/lib/setfd.c -
 *
 * Figure 13.9 Set close-on-exec flag
 * ========================================================================= */
#include "apue.h"
#include <fcntl.h>

int set_cloexec(int fd) {
  int val;

  if ((val = fcntl(fd, F_GETFD, 0)) < 0)
    return (-1);

  val |= FD_CLOEXEC; /* enable close-on-exec */

  return (fcntl(fd, F_SETFD, val));
}
