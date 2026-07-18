/* =========================================================================
 * Created on: <Fri Jun 19 20:30:15 +01 2026>
 * Time-stamp: <Fri Jun 19 20:31:58 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/filedir/device_num.c -
 *
 * Figure 4.25: This program prints the device number for each
 * command-line argument. Additionally, if the argument refers to a
 * character special file or a block special file, the st_rdev value
 * for the special file is printed.
 * ========================================================================= */
#include "apue.h"
#ifdef SOLARIS
#include <sys/mkdev.h>
#else
#include <sys/sysmacros.h>
#endif

int main(int argc, char *argv[]) {
  int i;
  struct stat statbuf;

  for (i = 1; i < argc; i++) {
    printf("%s: ", argv[i]);
    if (stat(argv[i], &statbuf) < 0) {
      err_ret("stat error");
      continue;
    }

    printf("dev = %d/%d", major(statbuf.st_dev), minor(statbuf.st_dev));

    if (S_ISCHR(statbuf.st_mode) || S_ISBLK(statbuf.st_mode)) {
      printf(" (%s) rdev = %d/%d",
             (S_ISCHR(statbuf.st_mode)) ? "character" : "block",
             major(statbuf.st_rdev), minor(statbuf.st_rdev));
    }
    printf("\n");
  }

  exit(0);
}
