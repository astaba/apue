/* =========================================================================
 * Created on: <Thu Jul 16 05:22:39 +01 2026>
 * Time-stamp: <Fri Jul 17 14:05:28 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/exercises/fifo1.c -
 *
 * Figure C.20 [[file:../ipc1/README.org::#exercise-15-10]] Solution.
 * 
 * Opening a FIFO for reading and writing, without blocking
 * ========================================================================= */
#include "apue.h"
#include <fcntl.h>

#define FIFO "temp.fifo"

int main(void) {
  int fdread, fdwrite;

  unlink(FIFO);
  if (mkfifo(FIFO, FILE_MODE) < 0)
    err_sys("mkfifo error");
  if ((fdread = open(FIFO, O_RDONLY | O_NONBLOCK)) < 0)
    err_sys("open error for reading");
  if ((fdwrite = open(FIFO, O_WRONLY)) < 0)
    err_sys("open error for writing");
  clr_fl(fdread, O_NONBLOCK);
  exit(0);
}
