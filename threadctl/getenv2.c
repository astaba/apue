/* =========================================================================
 * Created on: <Fri Jul 17 14:43:43 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:18 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/threadctl/getenv2.c -
 *
 * Figure 12.12 A reentrant (thread-safe) version of getenv
 * ========================================================================= */
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

pthread_mutex_t env_mutex;

static pthread_once_t init_done = PTHREAD_ONCE_INIT;

static void thread_init(void) {
  pthread_mutexattr_t attr;

  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&env_mutex, &attr);
  pthread_mutexattr_destroy(&attr);
}

int getenv_r(const char *name, char *buf, int buflen) {
  int i, len, olen;

  pthread_once(&init_done, thread_init);
  len = strlen(name);
  pthread_mutex_lock(&env_mutex);
  for (i = 0; environ[i] != NULL; i++) {
    if ((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '=')) {
      olen = strlen(&environ[i][len + 1]);
      if (olen >= buflen) {
        pthread_mutex_unlock(&env_mutex);
        return (ENOSPC);
      }
      strcpy(buf, &environ[i][len + 1]);
      pthread_mutex_unlock(&env_mutex);
      return (0);
    }
  }
  pthread_mutex_unlock(&env_mutex);
  return (ENOENT);
}
