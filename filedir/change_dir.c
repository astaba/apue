/* =========================================================================
 * Created on: <Fri Jun 19 12:28:57 +01 2026>
 * Time-stamp: <Fri Jun 19 13:00:11 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/filedir/change_dir.c -
 *
 * Figure 4.23 Example of chdir function
 *
 * The current working directory is merely an attribute of a process
 * as much as the home directory is strictly an attribute of a login
 * name (from /etc/passwd). Thus, because it is an attribute of a
 * process, current working directory affect only the default relative
 * path of the process but cannot affect the processes that invoke the
 * process that executes the `chdir`.
 * ========================================================================= */
#include "../include/apue.h"

int main(void) {
  if (chdir("/tmp") < 0)
    err_sys("chdir failed");
  printf("chdir to /tmp succeeded\n");

  exit(0);
}
