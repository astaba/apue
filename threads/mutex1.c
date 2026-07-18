/* =========================================================================
 * Created on: <Mon Jun 29 22:44:41 +01 2026>
 * Time-stamp: <Thu Jul  2 12:58:26 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/threads/mutex1.c -
 *
 * Figure 11.10: Using a mutex to protect a data structure.
 * See [[file:mutex2.c]] and [[file:mutex3.c]]
 * ========================================================================= */
#include <pthread.h>
#include <stdlib.h>

struct foo {
  int f_count;
  pthread_mutex_t f_lock;
  int f_id;
  /* ... more stuff here ... */
};

struct foo *foo_alloc(int id) /* allocate the object */
{
  struct foo *fp;

  if ((fp = malloc(sizeof(struct foo))) != NULL) {
    fp->f_count = 1;
    fp->f_id = id;
    if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
      free(fp);
      return (NULL);
    }
    /* ... continue initialization ... */
  }
  return (fp);
}

void foo_hold(struct foo *fp) /* add a reference to the object */
{
  pthread_mutex_lock(&fp->f_lock);
  fp->f_count++;
  pthread_mutex_unlock(&fp->f_lock);
}

/* Release a reference to the object. WARNING: Jumping from unlock to
 * destroy without locking the whole list is a dangerous flaw. See
 * [[file:README.org::#fundamental-flaw-within-foo_rele]] */
void foo_rele(struct foo *fp) {
  pthread_mutex_lock(&fp->f_lock);
  if (--fp->f_count == 0) { /* last reference */
    pthread_mutex_unlock(&fp->f_lock);
    pthread_mutex_destroy(&fp->f_lock);
    free(fp);
  } else {
    pthread_mutex_unlock(&fp->f_lock);
  }
}
