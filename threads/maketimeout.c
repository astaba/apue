/* =========================================================================
 * Created on: <Wed Jul 01 16:41:52 +01 2026>
 * Time-stamp: <Wed Jul  1 17:23:11 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/threads/maketimeout.c -
 *
 * As an alternative to clock_gettime this program shows how to use
 * the gettimeofday function to get the current time expressed as a
 * timeval structure and translate it into a timespec structure and
 * produce the absolute time for the timeout value.(assuming the
 * maximum time blocked is expressed in minutes). In turn its timespec
 * returned value is needed by pthread_cond_timedwait.
 * ========================================================================= */
#include <stdlib.h>
#include <sys/time.h>

void maketimeout(struct timespec *tsp, long minutes) {
  struct timeval now;

  /* get the current time */
  gettimeofday(&now, NULL);
  tsp->tv_sec = now.tv_sec;
  tsp->tv_nsec = now.tv_usec * 1000; /* usec to nsec */
  /* add the offset to get timeout value */
  tsp->tv_sec += minutes * 60;
}
