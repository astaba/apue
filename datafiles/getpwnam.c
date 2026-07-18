/* =========================================================================
 * Created on: <Sun Jun 28 18:46:54 +01 2026>
 * Time-stamp: <Sun Jun 28 18:49:13 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/datafiles/getpwnam.c -
 *
 * Figure 6.2: shows an implementation of the function getpwnam.
 * ========================================================================= */
#include <pwd.h>
#include <stddef.h>
#include <string.h>

struct passwd *getpwnam(const char *name) {
  struct passwd *ptr;

  setpwent();

  while ((ptr = getpwent()) != NULL)
    if (strcmp(name, ptr->pw_name) == 0)
      break; /* found a match */

  endpwent();

  return (ptr); /* ptr is NULL if no match found */
}
