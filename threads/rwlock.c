/* =========================================================================
 * Created on: <Tue Jun 30 03:42:02 +01 2026>
 * Time-stamp: <Tue Jul  7 19:48:15 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/threads/rwlock.c -
 *
 * Figure 11.14 Using reader–writer locks
 * ========================================================================= */
#include <pthread.h>
#include <stdlib.h>

struct job {
  struct job *j_next;
  struct job *j_prev;
  pthread_t j_id; /* tells which thread handles this job */
                  /* ... more stuff here ... */
};

/* A manager interface to centralize matedata about job-struct-based
   doubly-linked lists. It holds the lock for concurrent and safe
   access of the linked list. Also holds the first and last node in
   the linked list to enable the producer thread to append jobs at the
   tail while the consumer thread pops jobs from the head without any
   thread having to walk the whole list. */
struct queue {
  struct job *q_head;
  struct job *q_tail;
  pthread_rwlock_t q_lock;
};

/*
 * Initialize a queue.
 */
int queue_init(struct queue *qp) {
  int err;

  qp->q_head = NULL;
  qp->q_tail = NULL;
  err = pthread_rwlock_init(&qp->q_lock, NULL);
  if (err != 0)
    return (err);
  /* ... continue initialization ... */
  return (0);
}

/*
 * Insert a job at the head of a jobs doubly-linked list and update
 * accordingly the queue (the manager interface for the metadata about
 * that very linked list).
 */
void job_insert(struct queue *qp, struct job *jp) {
  pthread_rwlock_wrlock(&qp->q_lock);
  jp->j_next = qp->q_head;
  jp->j_prev = NULL;

  if (qp->q_head != NULL)
    qp->q_head->j_prev = jp;
  else
    qp->q_tail = jp; /* list was empty */

  qp->q_head = jp;
  pthread_rwlock_unlock(&qp->q_lock);
}

/*
 * Append a job on the tail of a jobs doubly-linked list and update
 * accordingly the queue (the manager interface for the metadata about
 * that very linked list).
 */
void job_append(struct queue *qp, struct job *jp) {
  pthread_rwlock_wrlock(&qp->q_lock);
  jp->j_next = NULL;
  jp->j_prev = qp->q_tail;

  if (qp->q_tail != NULL)
    qp->q_tail->j_next = jp;
  else
    qp->q_head = jp; /* list was empty */

  qp->q_tail = jp;
  pthread_rwlock_unlock(&qp->q_lock);
}

/*
 * Remove the given job from a queue.
 */
void job_remove(struct queue *qp, struct job *jp) {
  pthread_rwlock_wrlock(&qp->q_lock);
  if (jp == qp->q_head) {
    qp->q_head = jp->j_next;
    if (qp->q_tail == jp)
      qp->q_tail = NULL;
    else
      jp->j_next->j_prev = jp->j_prev;
  } else if (jp == qp->q_tail) {
    qp->q_tail = jp->j_prev;
    jp->j_prev->j_next = jp->j_next;
  } else {
    jp->j_prev->j_next = jp->j_next;
    jp->j_next->j_prev = jp->j_prev;
  }
  pthread_rwlock_unlock(&qp->q_lock);
}

/*
 * Find a job for the given thread ID.
 */
struct job *job_find(struct queue *qp, pthread_t id) {
  struct job *jp;

  if (pthread_rwlock_rdlock(&qp->q_lock) != 0)
    return (NULL);

  for (jp = qp->q_head; jp != NULL; jp = jp->j_next)
    if (pthread_equal(jp->j_id, id))
      break;

  pthread_rwlock_unlock(&qp->q_lock);
  return (jp);
}
