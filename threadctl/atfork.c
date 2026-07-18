/* =========================================================================
 * Created on: <Fri Jul 17 14:44:12 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:17 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/threadctl/atfork.c -
 *
 * Figure 12.17 pthread_atfork example
 * ========================================================================= */
#include "apue.h"
#include <pthread.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare(void) {
  int err;

  printf("preparing locks...\n");
  if ((err = pthread_mutex_lock(&lock1)) != 0)
    err_cont(err, "can't lock lock1 in prepare handler");
  if ((err = pthread_mutex_lock(&lock2)) != 0)
    err_cont(err, "can't lock lock2 in prepare handler");
}

void parent(void) {
  int err;

  printf("parent unlocking locks...\n");
  if ((err = pthread_mutex_unlock(&lock1)) != 0)
    err_cont(err, "can't unlock lock1 in parent handler");
  if ((err = pthread_mutex_unlock(&lock2)) != 0)
    err_cont(err, "can't unlock lock2 in parent handler");
}

void child(void) {
  int err;

  printf("child unlocking locks...\n");
  if ((err = pthread_mutex_unlock(&lock1)) != 0)
    err_cont(err, "can't unlock lock1 in child handler");
  if ((err = pthread_mutex_unlock(&lock2)) != 0)
    err_cont(err, "can't unlock lock2 in child handler");
}

void *thr_fn(void *arg) {
  printf("thread started...\n");
  pause();
  return (0);
}

int main(void) {
  int err;
  pid_t pid;
  pthread_t tid;

  if ((err = pthread_atfork(prepare, parent, child)) != 0)
    err_exit(err, "can't install fork handlers");
  if ((err = pthread_create(&tid, NULL, thr_fn, 0)) != 0)
    err_exit(err, "can't create thread");

  sleep(2);
  printf("parent about to fork...\n");

  if ((pid = fork()) < 0)
    err_quit("fork failed");
  else if (pid == 0) /* child */
    printf("child returned from fork\n");
  else /* parent */
    printf("parent returned from fork\n");
  exit(0);
}
