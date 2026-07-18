/* =========================================================================
 * Created on: <Mon Jun 29 00:04:04 +01 2026>
 * Time-stamp: <Mon Jun 29 11:35:12 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/threads/threadid.c -
 *
 * Figure 11.2 creates one thread and prints the process and thread
 * IDs of the new thread and the initial thread.
 * ========================================================================= */
#include "apue.h"
#include <pthread.h>

pthread_t ntid;

void printids(const char *s) {
  pid_t pid;
  pthread_t tid;

  pid = getpid();
  tid = pthread_self();
  printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid,
         (unsigned long)tid, (unsigned long)tid);
}

void *thr_fn(void *arg) {
  printids("new thread: ");
  return ((void *)0);
}

int main(void) {
  int err;

  err = pthread_create(&ntid, NULL, thr_fn, NULL);
  if (err != 0)
    err_exit(err, "can't create thread");

  printids("main thread:");

  sleep(1);
  exit(0);
}
