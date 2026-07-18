/* =========================================================================
 * Created on: <Wed Jul 15 02:23:54 +01 2026>
 * Time-stamp: <Wed Jul 15 02:25:40 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/proc/echoall.c -
 *
 * Figure 8.17: Echo all command-line arguments and all environment
 * strings
 * ========================================================================= */
#include "apue.h"	/* IWYU pragma: keep */

int main(int argc, char *argv[]) {
  int i;
  char **ptr;
  extern char **environ;

  for (i = 0; i < argc; i++) /* echo all command-line args */
    printf("argv[%d]: %s\n", i, argv[i]);

  for (ptr = environ; *ptr != 0; ptr++) /* and all env strings */
    printf("%s\n", *ptr);

  exit(0);
}
