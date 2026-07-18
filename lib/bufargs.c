/* =========================================================================
 * Created on: <Fri Jul 17 15:36:11 +01 2026>
 * Time-stamp: <Fri Jul 17 15:36:54 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/lib/bufargs.c -
 *
 * Figure 17.23 The buf_args function
 * ========================================================================= */
#include "apue.h"

#define MAXARGC 50    /* max number of arguments in buf */
#define WHITE " \t\n" /* white space for tokenizing arguments */

/*
 * buf[] contains white-space-separated arguments.  We convert it to an
 * argv-style array of pointers, and call the user's function (optfunc)
 * to process the array.  We return -1 if there's a problem parsing buf,
 * else we return whatever optfunc() returns.  Note that user's buf[]
 * array is modified (nulls placed after each token).
 */
int buf_args(char *buf, int (*optfunc)(int, char **)) {
  char *ptr, *argv[MAXARGC];
  int argc;

  if (strtok(buf, WHITE) == NULL) /* an argv[0] is required */
    return (-1);
  argv[argc = 0] = buf;
  while ((ptr = strtok(NULL, WHITE)) != NULL) {
    if (++argc >= MAXARGC - 1) /* -1 for room for NULL at end */
      return (-1);
    argv[argc] = ptr;
  }
  argv[++argc] = NULL;

  /*
   * Since argv[] pointers point into the user's buf[],
   * user's function can just copy the pointers, even
   * though argv[] array will disappear on return.
   */
  return ((*optfunc)(argc, argv));
}
