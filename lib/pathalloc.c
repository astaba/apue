/* =========================================================================
 * Created on: <Fri Jul 17 14:25:15 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:19 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/lib/pathalloc.c -
 *
 * Figure 2.16 Dynamically allocate space for a pathname
 * ========================================================================= */
#include "apue.h"
#include <errno.h>
#include <limits.h>

#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;

/* If PATH_MAX is indeterminate, no guarantee this is adequate */
#define PATH_MAX_GUESS 1024

/**
 * @brief Allocates memory for a maximum-length pathname.
 * This function calculates the largest possible pathname size supported by the
 * system (accounting for `PATH_MAX` variability and POSIX versions), allocates
 * that memory, and returns the pointer.
 *
 * @param `sizep` An optional output parameter (pass-by-reference). If non-NULL,
 * the function writes the calculated, allocated buffer size (in bytes,
 * including the null terminator) into the memory location pointed to
 * by `sizep.` The caller should pass NULL if the allocated size is
 * not required, to prevent a segmentation fault.
 *
 * @return `char *` A pointer to the dynamically allocated pathname buffer.
 *
 * @throws Terminates the program via `err_sys()` on internal errors (e.g.,
 * `pathconf` failure, `malloc` failure).
 */
char *path_alloc(size_t *sizep) /* also return allocated size, if nonnull */
{
  char *ptr;
  size_t size;

  if (posix_version == 0)
    posix_version = sysconf(_SC_VERSION);

  if (xsi_version == 0)
    xsi_version = sysconf(_SC_XOPEN_VERSION);

  if (pathmax == 0) { /* first time through */
    errno = 0;
    if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
      if (errno == 0)
        pathmax = PATH_MAX_GUESS; /* it's indeterminate */
      else
        err_sys("pathconf error for _PC_PATH_MAX");
    } else {
      pathmax++; /* add one since it's relative to root */
    }
  }

  /*
   * Before POSIX.1-2001, we aren't guaranteed that PATH_MAX includes
   * the terminating null byte.  Same goes for XPG3.
   */
  if ((posix_version < 200112L) && (xsi_version < 4))
    size = pathmax + 1;
  else
    size = pathmax;

  if ((ptr = malloc(size)) == NULL)
    err_sys("malloc error for pathname");
  /*
   * The next "if" clause has two purposes:
   * (1) gards against seg fault,
   * (2) makes the output parameter optional */
  if (sizep != NULL)
    *sizep = size;
  return (ptr);
}
