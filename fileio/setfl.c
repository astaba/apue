/* Figure 3.12 Turn on one or more of the file status flags for a descriptor */

#include "../include/apue.h"
#include <fcntl.h>

/* @param flags are file status flags to turn on */
void set_fl(int fd, int flags) {
  int val;
  /* Be extra careful to first get all flags previously there */
  if ((val = fcntl(fd, F_GETFL, 0)) < 0)
    err_sys("fcntl F_GETFL error");
  /* turn on flags with binaryORing to keep previous and new flags */
  val |= flags;

  if (fcntl(fd, F_SETFL, val) < 0)
    err_sys("fcntl F_SETFL error");
}
