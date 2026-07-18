/* =========================================================================
 * Created on: <Fri Jul 17 14:46:02 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:17 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/advio/lockfile.c -
 *
 * Figure 14.9 Place a write lock on an entire file
 * ========================================================================= */
#include <fcntl.h>
#include <unistd.h>

int lockfile(int fd) {
  struct flock fl;

  fl.l_type = F_WRLCK;
  fl.l_start = 0;
  fl.l_whence = SEEK_SET;
  fl.l_len = 0;
  return (fcntl(fd, F_SETLK, &fl));
}
