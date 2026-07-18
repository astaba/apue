/* =========================================================================
 * Created on: <Fri Jul 17 14:45:52 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:17 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/advio/deadlock.c -
 *
 * Figure 14.7 Example of deadlock detection
 * ========================================================================= */
#include "apue.h"
#include <fcntl.h>

static void lockabyte(const char *name, int fd, off_t offset) {
  if (writew_lock(fd, offset, SEEK_SET, 1) < 0)
    err_sys("%s: writew_lock error", name);
  printf("%s: got the lock, byte %lld\n", name, (long long)offset);
}

int main(void) {
  int fd;
  pid_t pid;

  /*
   * Create a file and write two bytes to it.
   */
  if ((fd = creat("templock", FILE_MODE)) < 0)
    err_sys("creat error");
  if (write(fd, "ab", 2) != 2)
    err_sys("write error");

  TELL_WAIT();
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) { /* child */
    lockabyte("child", fd, 0);
    TELL_PARENT(getppid());
    WAIT_PARENT();
    lockabyte("child", fd, 1);
  } else { /* parent */
    lockabyte("parent", fd, 1);
    TELL_CHILD(pid);
    WAIT_CHILD();
    lockabyte("parent", fd, 0);
  }
  exit(0);
}
