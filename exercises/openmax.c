/* =========================================================================
 * Created on: <Thu Jul 16 03:22:20 +01 2026>
 * Time-stamp: <Fri Jul 17 14:05:29 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/exercises/openmax.c -
 *
 * Figure C.1 [[file:../standards/README.org::#exercise-2-3]] Solution.
 *
 * Alternative method for identifying the largest possible file
 * descriptor.
 *
 * If OPEN_MAX is indeterminate or ridiculously large (i.e., equal to
 * LONG_MAX), we can use getrlimit to get the per-process maximum for
 * open file descriptors. Since the per-process limit can be modified,
 * we can’t cache the value obtained from the previous call (it might
 * have changed).
 * ========================================================================= */
#include "apue.h"
#include <limits.h>
#include <sys/resource.h>

#define OPEN_MAX_GUESS 256

long open_max(void) {
  long openmax;
  struct rlimit rl;

  if ((openmax = sysconf(_SC_OPEN_MAX)) < 0 || openmax == LONG_MAX) {
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
      err_sys("can't get file limit");
    if (rl.rlim_max == RLIM_INFINITY)
      openmax = OPEN_MAX_GUESS;
    else
      openmax = rl.rlim_max;
  }
  return (openmax);
}
