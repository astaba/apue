/* =========================================================================
 * Created on: <Mon Jun 29 00:47:09 +01 2026>
 * Time-stamp: <Mon Jun 29 00:49:40 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/threads/exitstatus.c -
 *
 * Figure 11.3 shows how to fetch the exit code from a thread that has
 * terminated.
 * ========================================================================= */
#include "apue.h"
#include <pthread.h>

void *thr_fn1(void *arg) {
  printf("thread 1 returning\n");
  return ((void *)1);
}

void *thr_fn2(void *arg) {
  printf("thread 2 exiting\n");
  pthread_exit((void *)2);
}

int main(void) {
  int err;
  pthread_t tid1, tid2;
  void *tret;

  err = pthread_create(&tid1, NULL, thr_fn1, NULL);
  if (err != 0)
    err_exit(err, "can't create thread 1");

  err = pthread_create(&tid2, NULL, thr_fn2, NULL);
  if (err != 0)
    err_exit(err, "can't create thread 2");

  err = pthread_join(tid1, &tret);
  if (err != 0)
    err_exit(err, "can't join with thread 1");
  printf("thread 1 exit code %ld\n", (long)tret);

  err = pthread_join(tid2, &tret);
  if (err != 0)
    err_exit(err, "can't join with thread 2");
  printf("thread 2 exit code %ld\n", (long)tret);

  exit(0);
}
