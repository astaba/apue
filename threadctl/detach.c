/* =========================================================================
 * Created on: <Fri Jul 17 14:43:08 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:18 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/threadctl/detach.c -
 *
 * Figure 12.4 Creating a thread in the detached state
 * ========================================================================= */
#include "apue.h"
#include <pthread.h>

int makethread(void *(*fn)(void *), void *arg) {
  int err;
  pthread_t tid;
  pthread_attr_t attr;

  err = pthread_attr_init(&attr);
  if (err != 0)
    return (err);
  err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  if (err == 0)
    err = pthread_create(&tid, &attr, fn, arg);
  pthread_attr_destroy(&attr);
  return (err);
}
