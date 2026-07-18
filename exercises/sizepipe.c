/* =========================================================================
 * Created on: <Thu Jul 16 05:19:42 +01 2026>
 * Time-stamp: <Fri Jul 17 14:05:28 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/exercises/sizepipe.c -
 *
 * Figure C.18 [[file:../advio/README.org::#exercise-14-7]] Solution.
 * 
 * Calculation of pipe capacity using nonblocking writes
 * ========================================================================= */
#include "apue.h"
#include <fcntl.h>

int main(void) {
  int i, n;
  int fd[2];

  if (pipe(fd) < 0)
    err_sys("pipe error");
  set_fl(fd[1], O_NONBLOCK);

  /* write 1 byte at a time until pipe is full */
  for (n = 0;; n++) {
    if ((i = write(fd[1], "a", 1)) != 1) {
      printf("write ret %d, ", i);
      break;
    }
  }
  printf("pipe capacity = %d\n", n);
  exit(0);
}
