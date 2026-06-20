/* =========================================================================
 * Created on: <Wed Jun 17 22:48:12 +01 2026> 
 * Time-stamp: <Wed Jun 17 22:57:07 +01 2026 by owner> 
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/filedir/file_types.c -
 *
 * Figure 4.3 Print type of file for each command-line argument.
 * See also [[file:../fileio/print_flags.c]]
 * ========================================================================= */
#include "../include/apue.h"

int main(int argc, char *argv[]) {
  int i;
  struct stat buf;
  char *ptr;

  for (i = 1; i < argc; i++) {
    printf("%s: ", argv[i]);
    /* Using lstat(): stat() ignores links because it follows them */
    if (lstat(argv[i], &buf) < 0) {
      err_ret("lstat error");
      continue;
    }
    /* clang-format off */
    if      (S_ISREG(buf.st_mode))  ptr = "regular";
    else if (S_ISDIR(buf.st_mode))  ptr = "directory";
    else if (S_ISCHR(buf.st_mode))  ptr = "character special";
    else if (S_ISBLK(buf.st_mode))  ptr = "block special";
    else if (S_ISFIFO(buf.st_mode)) ptr = "fifo";
    else if (S_ISLNK(buf.st_mode))  ptr = "symbolic link";
    else if (S_ISSOCK(buf.st_mode)) ptr = "socket";
    else                            ptr = "** unknown mode **";
    /* clang-format on */
    printf("%s\n", ptr);
  }
  exit(0);
}

/*
$ ./a.out /etc/passwd /etc /dev/log /dev/tty \
> /var/lib/oprofile/opd_pipe /dev/sr0 /dev/cdrom
*/
