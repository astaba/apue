/* =========================================================================
 * Created on: <Fri Jul 17 14:45:36 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:17 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/lib/lockreg.c -
 *
 * Figure 14.5 Function to lock or unlock a region of a file
 * ========================================================================= */
#include "apue.h"
#include <fcntl.h>

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len) {
  struct flock lock;

  lock.l_type = type;     /* F_RDLCK, F_WRLCK, F_UNLCK */
  lock.l_start = offset;  /* byte offset, relative to l_whence */
  lock.l_whence = whence; /* SEEK_SET, SEEK_CUR, SEEK_END */
  lock.l_len = len;       /* #bytes (0 means to EOF) */

  return (fcntl(fd, cmd, &lock));
}
