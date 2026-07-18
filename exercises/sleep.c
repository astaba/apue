/* =========================================================================
 * Created on: <Thu Jul 16 04:59:10 +01 2026>
 * Time-stamp: <Fri Jul 17 14:05:28 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/exercises/sleep.c -
 *
 * Figure C.13 [[file:../threadctl/README.org::#exercise-12-6]] Solution.
 * 
 * A thread-safe implementation of sleep
 * ========================================================================= */
#include <sys/select.h>
#include <time.h>
#include <unistd.h>

unsigned sleep(unsigned seconds) {
  int n;
  unsigned slept;
  time_t start, end;
  struct timeval tv;

  tv.tv_sec = seconds;
  tv.tv_usec = 0;
  time(&start);
  n = select(0, NULL, NULL, NULL, &tv);
  if (n == 0)
    return (0);
  time(&end);
  slept = end - start;
  if (slept >= seconds)
    return (0);
  return (seconds - slept);
}
