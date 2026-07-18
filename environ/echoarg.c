/* =========================================================================
 * Created on: <Sun Jun 28 19:37:08 +01 2026>
 * Time-stamp: <Sun Jun 28 19:46:28 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/environ/echoarg.c -
 *
 * Figure 7.4: This program echoes all its command-line arguments to
 * standard output. Note that the normal echo(1) program doesn’t echo
 * the zeroth argument.
 * ========================================================================= */
#include "apue.h" /* IWYU pragma: keep */

int main(int argc, char *argv[]) {
  int i;

  for (i = 0; i < argc; i++) /* echo all command-line args */
    printf("argv[%d]: %s\n", i, argv[i]);
  exit(0);
}
