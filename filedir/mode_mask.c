/* =========================================================================
 * Created on: <Wed Jun 17 23:19:56 +01 2026>
 * Time-stamp: <Wed Jun 17 23:22:05 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/filedir/mode_mask.c -
 *
 * Figure 4.9: Example of umask function Any bits that are on in the
 * file mode creation mask are turned off in the file's mode.
 * ========================================================================= */
#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main(void) {
  umask(0);
  if (creat("foo", RWRWRW) < 0)
    err_sys("creat error for foo");

  umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  if (creat("bar", RWRWRW) < 0)
    err_sys("creat error for bar");

  exit(0);
}
