/* =========================================================================
 * Created on: <Wed Jun 17 23:07:02 +01 2026>
 * Time-stamp: <Wed Jun 17 23:08:14 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/filedir/access_file.c -
 *
 * Figure 4.8 Example of access function
 * ========================================================================= */
#include "../include/apue.h"
#include <fcntl.h>

int main(int argc, char *argv[]) {
  if (argc != 2)
    err_quit("usage: a.out <pathname>");

  if (access(argv[1], R_OK) < 0)
    err_ret("access(2): error for %s", argv[1]);
  else
    printf("access(2): OK for reading\n");

  if (open(argv[1], O_RDONLY) < 0)
    err_ret("open(2): error for %s", argv[1]);
  else
    printf("open(2): OK for reading\n");

  exit(0);
}
