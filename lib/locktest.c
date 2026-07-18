/* =========================================================================
 * Created on: <Fri Jul 17 14:45:45 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:17 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/lib/locktest.c -
 *
 * Figure 14.6 Function to test for a locking condition
 * ========================================================================= */
#include "apue.h"
#include <fcntl.h>

pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len) {
  struct flock lock;

  lock.l_type = type;     /* F_RDLCK or F_WRLCK */
  lock.l_start = offset;  /* byte offset, relative to l_whence */
  lock.l_whence = whence; /* SEEK_SET, SEEK_CUR, SEEK_END */
  lock.l_len = len;       /* #bytes (0 means to EOF) */

  if (fcntl(fd, F_GETLK, &lock) < 0)
    err_sys("fcntl error");

  if (lock.l_type == F_UNLCK)
    return (0);        /* false, region isn't locked by another proc */
  return (lock.l_pid); /* true, return pid of lock owner */
}
