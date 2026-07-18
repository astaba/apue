/* =========================================================================
 * Created on: <Thu Jul 16 05:12:30 +01 2026>
 * Time-stamp: <Fri Jul 17 14:05:28 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/exercises/sleepus_select.c -
 *
 * Figure C.16 [[file:../advio/README.org::#exercise-14-5]] Solution.
 * 
 * Implementation of sleep_us using select
 * ========================================================================= */
#include "apue.h"
#include <sys/select.h>

void sleep_us(unsigned int nusecs) {
  struct timeval tval;

  tval.tv_sec = nusecs / 1000000;
  tval.tv_usec = nusecs % 1000000;
  select(0, NULL, NULL, NULL, &tval);
}
