/* =========================================================================
 * Created on: <Mon Jun 15 18:43:53 +01 2026>
 * Time-stamp: <Mon Jun 15 18:58:20 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/fileio/print_flags.c -
 *
 * Figure 3.11 Print file status flags for specified descriptor.
 * See also [[file:../filedir/filetype.c::30]]
 * ========================================================================= */
#include "../include/apue.h"
#include <fcntl.h>

int main(int argc, char *argv[]) {
  int val;

  if (argc != 2)
    err_quit("usage: a.out <descriptor#>");

  if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
    err_sys("fcntl error for fd %d", atoi(argv[1]));
  /* clang-format off */

  switch (val & O_ACCMODE) {
  case O_RDONLY: printf("read only"); break;
  case O_WRONLY: printf("write only"); break;
  case O_RDWR: printf("read write"); break;
  default: err_dump("unknown access mode");
  }

  if (val & O_APPEND)   printf(", append");
  if (val & O_NONBLOCK) printf(", nonblocking");
  if (val & O_SYNC)     printf(", synchronous writes");

    /* clang-format on */
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
  if (val & O_FSYNC)
    printf(", synchronous writes");
#endif

  putchar('\n');
  exit(0);
}
