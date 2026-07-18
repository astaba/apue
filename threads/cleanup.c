/* =========================================================================
 * Created on: <Mon Jun 29 12:08:45 +01 2026>
 * Time-stamp: <Wed Jul  1 18:17:25 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/threads/cleanup.c -
 *
 * Figure 11.5 Thread cleanup handler.
 *
 * NOTICE: Although we never intend to pass zero as an argument to the
 * thread start-up routines, we still need to match calls to
 * pthread_cleanup_pop with the calls to pthread_cleanup_push;
 * otherwise, the program might not compile. Expand their macros or
 * comment out the pthread_cleanup_pop to see why.
 * ========================================================================= */
#include "apue.h"
#include <pthread.h>

void cleanup(void *arg) { printf("cleanup: %s\n", (char *)arg); }

void *thr_fn1(void *arg) {
  printf("thread 1: start\n");
  pthread_cleanup_push(cleanup, "thread 1 first handler");
  pthread_cleanup_push(cleanup, "thread 1 second handler");
  printf("thread 1: push complete\n");
  if (arg)
    return ((void *)1);
  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);
  return ((void *)1);
}

void *thr_fn2(void *arg) {
  printf("thread 2: start\n");
  pthread_cleanup_push(cleanup, "thread 2 first handler");
  pthread_cleanup_push(cleanup, "thread 2 second handler");
  printf("thread 2: push complete\n");
  if (arg)
    pthread_exit((void *)2);
  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);
  pthread_exit((void *)2);
}

int main(void) {
  int err;
  pthread_t tid1, tid2;
  void *tret;

  err = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
  if (err != 0)
    err_exit(err, "can't create thread 1");

  err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);
  if (err != 0)
    err_exit(err, "can't create thread 2");

  err = pthread_join(tid1, &tret);
  if (err != 0)
    err_exit(err, "can't join with thread 1");
  printf("thread m: thread 1 exit code %ld\n", (long)tret);

  err = pthread_join(tid2, &tret);
  if (err != 0)
    err_exit(err, "can't join with thread 2");
  printf("thread m: thread 2 exit code %ld\n", (long)tret);

  exit(0);
}
