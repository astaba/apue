/* =========================================================================
 * Created on: <Fri Jun 19 11:21:50 +01 2026>
 * Time-stamp: <Fri Jun 19 11:25:20 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/filedir/unlink_file.c -
 *
 * Figure 4.16 Open a file and then unlink it.
 * ========================================================================= */
#include "apue.h"
#include <fcntl.h>

int main(void) {
  if (open("tempfile", O_RDWR) < 0)
    err_sys("open error");

  if (unlink("tempfile") < 0)
    err_sys("unlink error");
  printf("file unlinked\n");

  sleep(15);
  printf("done\n");

  exit(0);
}
