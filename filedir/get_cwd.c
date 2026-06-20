/* =========================================================================
 * Created on: <Fri Jun 19 13:02:49 +01 2026>
 * Time-stamp: <Fri Jun 19 13:05:21 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/filedir/get_cwd.c -
 *
 * Figure 4.24 Example of getcwd function
 * ========================================================================= */
#include "../include/apue.h"

int main(void) {
  char *ptr;
  size_t size;

  /* Change chdir() argument according to your system */
  /* if (chdir("/usr/spool/uucppublic") < 0) */
  if (chdir("/usr/share/aspell") < 0)
    err_sys("chdir failed");

  ptr = path_alloc(&size); /* our own function */
  if (getcwd(ptr, size) == NULL)
    err_sys("getcwd failed");

  printf("cwd = %s\n", ptr);
  exit(0);
}
