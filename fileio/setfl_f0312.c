/* apue.3e/fileio/setfl_f0312.c */
/* Rehearsed: Tue Dec  9 16:09:15 +01 2025 */
/* Figure 3.12 Turn on one or more of the file status flags for a descriptor */

#include "../include/apue.h"
#include <fcntl.h>

/* @param flags are file status flags to turn on */
void set_fl(int fd, int flags) {
  int value;

  /* First, retrieve previous flags if any */
  if (fcntl(fd, F_GETFL, value) < 0)
    err_sys("fcntl F_GETFL error");

  /* Binary OR new flags on retrieved value to preserve previous flags */
  value |= flags;
  if (fcntl(fd, F_SETFL, value) < 0)
    err_sys("fcntl F_SETFL error");
}
