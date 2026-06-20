/* =========================================================================
 * Created on: <Wed Jun 17 23:26:06 +01 2026> 
 * Time-stamp: <Wed Jun 17 23:26:43 +01 2026 by owner> 
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/filedir/change_mode.c -
 *
 * Figure 4.12 Example of chmod function
 * ========================================================================= */
#include "../include/apue.h"

int main(void) {
  struct stat statbuf;

  /* set mode relative to current state:
   * set-group-ID and turn off group-execute */
  if (stat("foo", &statbuf) < 0)
    err_sys("stat error for foo");
  if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
    err_sys("chmod error for foo");

  /* set absolute mode to "rw-r--r--" */
  if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
    err_sys("chmod error for bar");

  exit(0);
}
