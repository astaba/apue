/* =========================================================================
 * Created on: <Thu Jun 25 18:59:16 +01 2026>
 * Time-stamp: <Fri Jun 26 18:30:53 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/stdio/exr0504.c -
 *             Initially named getcharbug.c
 *
 * Exercise 5.4: The following code works correctly on some machines,
 * but not on others. What could be the problem?
 * ========================================================================= */
#include <stdio.h>

int main(void) {
  char c; /* FIXME: int c; */

  while ((c = getchar()) != EOF)
    putchar(c);
}
