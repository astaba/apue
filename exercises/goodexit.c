/* =========================================================================
 * Created on: <Thu Jul 16 04:53:16 +01 2026>
 * Time-stamp: <Fri Jul 17 14:05:28 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/exercises/goodexit.c -
 *
 * Figure C.12 [[file:../threads/README.org::#exercise-11-1]] Solution.
 * 
 * Correct use of thread return value
 * ========================================================================= */
#include "apue.h"
#include <pthread.h>

struct foo {
  int a, b, c, d;
};

void printfoo(const char *s, const struct foo *fp) {
  fputs(s, stdout);
  printf("  structure at 0x%lx\n", (unsigned long)fp);
  printf("  foo.a = %d\n", fp->a);
  printf("  foo.b = %d\n", fp->b);
  printf("  foo.c = %d\n", fp->c);
  printf("  foo.d = %d\n", fp->d);
}

void *thr_fn1(void *arg) {
  struct foo *fp;

  if ((fp = malloc(sizeof(struct foo))) == NULL)
    err_sys("can't allocate memory");
  fp->a = 1;
  fp->b = 2;
  fp->c = 3;
  fp->d = 4;
  printfoo("thread:\n", fp);
  return ((void *)fp);
}

int main(void) {
  int err;
  pthread_t tid1;
  struct foo *fp;

  err = pthread_create(&tid1, NULL, thr_fn1, NULL);
  if (err != 0)
    err_exit(err, "can't create thread 1");
  err = pthread_join(tid1, (void *)&fp);
  if (err != 0)
    err_exit(err, "can't join with thread 1");
  printfoo("parent:\n", fp);
  exit(0);
}
