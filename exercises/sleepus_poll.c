/* =========================================================================
 * Created on: <Thu Jul 16 05:14:39 +01 2026>
 * Time-stamp: <Fri Jul 17 14:05:28 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/exercises/sleepus_poll.c -
 *
 * Figure C.17 [[file:../advio/README.org::#exercise-14-5]] Solution.
 * 
 * Implementation of sleep_us using poll
 * ========================================================================= */
#include <poll.h>

void sleep_us(unsigned int nusecs) {
  struct pollfd dummy;
  int timeout;

  if ((timeout = nusecs / 1000) <= 0)
    timeout = 1;
  poll(&dummy, 0, timeout);
}
