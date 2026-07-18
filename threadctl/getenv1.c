/* =========================================================================
 * Created on: <Fri Jul 17 14:43:29 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:18 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/threadctl/getenv1.c -
 *
 * Figure 12.11 A nonreentrant version of getenv
 * ========================================================================= */
#include <limits.h>
#include <string.h>

#define MAXSTRINGSZ 4096

static char envbuf[MAXSTRINGSZ];

extern char **environ;

char *getenv(const char *name) {
  int i, len;

  len = strlen(name);
  for (i = 0; environ[i] != NULL; i++) {
    if ((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '=')) {
      strncpy(envbuf, &environ[i][len + 1], MAXSTRINGSZ - 1);
      return (envbuf);
    }
  }
  return (NULL);
}
