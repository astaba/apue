/* =========================================================================
 * Created on: <Fri Jul 17 14:51:08 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:16 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc1/slock.c -
 *
 * Figure 15.35 Mutual exclusion using a POSIX semaphore
 * ========================================================================= */
#include "slock.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct slock *s_alloc() {
  struct slock *sp;
  static int cnt;

  if ((sp = malloc(sizeof(struct slock))) == NULL)
    return (NULL);
  do {
    snprintf(sp->name, sizeof(sp->name), "/%ld.%d", (long)getpid(), cnt++);
    sp->semp = sem_open(sp->name, O_CREAT | O_EXCL, S_IRWXU, 1);
  } while ((sp->semp == SEM_FAILED) && (errno == EEXIST));
  if (sp->semp == SEM_FAILED) {
    free(sp);
    return (NULL);
  }
  sem_unlink(sp->name);
  return (sp);
}

void s_free(struct slock *sp) {
  sem_close(sp->semp);
  free(sp);
}

int s_lock(struct slock *sp) { return (sem_wait(sp->semp)); }

int s_trylock(struct slock *sp) { return (sem_trywait(sp->semp)); }

int s_unlock(struct slock *sp) { return (sem_post(sp->semp)); }
