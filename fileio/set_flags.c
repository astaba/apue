/* =========================================================================
 * Created on: <Tue Dec  9 16:09:15 +01 2025>
 * Time-stamp: <Mon Jun 15 19:07:30 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/fileio/set_flags.c -
 *
 * Figure 3.12 Turn on one or more of the file status flags for a
 * descriptor.
 * ========================================================================= */
#include "../include/apue.h"
#include <fcntl.h>

/* @param flags are file status flags to turn on */
void set_fl(int fd, int flags) {
  int value;

  /* First, retrieve previous flags if any */
  if (fcntl(fd, F_GETFL, value) < 0)
    err_sys("fcntl F_GETFL error");

  value |= flags; /* turn on flags */
  /* value &= ~flags; /\* HACK: turn flags off *\/   */

  if (fcntl(fd, F_SETFL, value) < 0)
    err_sys("fcntl F_SETFL error");
}
