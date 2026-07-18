/* =========================================================================
 * Created on: <Fri Jul 17 14:34:26 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:19 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/proc/systest3.c -
 *
 * Figure 8.24 Execute the command-line argument using system
 * ========================================================================= */
#include "apue.h"

int main(int argc, char *argv[]) {
  int status;

  if (argc < 2)
    err_quit("command-line argument required");

  if ((status = system(argv[1])) < 0)
    err_sys("system() error");

  pr_exit(status);

  exit(0);
}
