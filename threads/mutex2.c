/* =========================================================================
 * Created on: <Mon Jun 29 23:04:39 +01 2026>
 * Time-stamp: <Thu Jul  2 14:15:52 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/threads/mutex2.c -
 *
 * Figure 11.11 Using two mutexes
 * See [[file:mutex1.c]] and [[file:mutex3.c]]
 * ========================================================================= */
#include <pthread.h>
#include <stdlib.h>

#define NHASH 29                               /* The bucket or shelf */
#define HASH(id) (((unsigned long)id) % NHASH) /* The Hash Function */
/* The Hash Table: an array of heads, heads for linked lists. .bss
   automatic layout zeroes out the whole table making each element
   pointer value to NULL */
struct foo *fh[NHASH];
pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo {
  int f_count;
  pthread_mutex_t f_lock;
  int f_id;
  struct foo *f_next; /* protected by hashlock */
                      /* ... more stuff here ... */
};

struct foo *foo_alloc(int id) /* allocate the object */
{
  struct foo *fp; /* foo pointer */
  int idx;        /* Shelf index in the hash table */

  if ((fp = malloc(sizeof(struct foo))) != NULL) {
    fp->f_count = 1;
    fp->f_id = id;
    if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
      free(fp);
      return (NULL);
    }
    /* Determine the shelf (linked list) it belongs to. */
    idx = HASH(id);
    pthread_mutex_lock(&hashlock);
    /* Insert new node at the head */
    fp->f_next = fh[idx];
    fh[idx] = fp;
    pthread_mutex_lock(&fp->f_lock);
    pthread_mutex_unlock(&hashlock);
    /* ... continue initialization ... */
    pthread_mutex_unlock(&fp->f_lock);
  }
  return (fp);
}

void foo_hold(struct foo *fp) /* add a reference to the object */
{
  pthread_mutex_lock(&fp->f_lock);
  fp->f_count++;
  pthread_mutex_unlock(&fp->f_lock);
}

struct foo *foo_find(int id) /* find an existing object */
{
  struct foo *fp;

  pthread_mutex_lock(&hashlock);
  for (fp = fh[HASH(id)]; fp != NULL; fp = fp->f_next) {
    if (fp->f_id == id) {
      foo_hold(fp);
      break;
    }
  }
  pthread_mutex_unlock(&hashlock);
  return (fp);
}

void foo_rele(struct foo *fp) /* release a reference to the object */
{
  struct foo *tfp; /* Temporary foo pointer */
  int idx;

  pthread_mutex_lock(&fp->f_lock);
  if (fp->f_count == 1) { /* last reference */
    pthread_mutex_unlock(&fp->f_lock);
    pthread_mutex_lock(&hashlock);
    pthread_mutex_lock(&fp->f_lock);
    /* need to recheck the condition */
    if (fp->f_count != 1) {
      fp->f_count--;
      pthread_mutex_unlock(&fp->f_lock);
      pthread_mutex_unlock(&hashlock);
      return;
    }
    /* remove from list */
    idx = HASH(fp->f_id); /* Get the right linked list */
    tfp = fh[idx];        /* Start search at the head */
    if (tfp == fp) {      /* Node is at the head */
      fh[idx] = fp->f_next;
    } else { /* Node is in the linked list */
      while (tfp->f_next != fp)
        tfp = tfp->f_next;
      tfp->f_next = fp->f_next;
    }
    pthread_mutex_unlock(&hashlock);
    pthread_mutex_unlock(&fp->f_lock);
    pthread_mutex_destroy(&fp->f_lock);
    free(fp);
  } else {
    fp->f_count--;
    pthread_mutex_unlock(&fp->f_lock);
  }
}
