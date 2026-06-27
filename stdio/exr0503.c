/* =========================================================================
 * Created on: <Fri Jun 26 17:52:38 +01 2026>
 * Time-stamp: <Sat Jun 27 13:09:04 +01 2026 by owner>
 * Author    : owner
 * Desc      : ~/coding/c_prog/apue.3e/stdio/exr0503.c -
 *
 * Example 5.3: What does a return value of 0 from printf mean?
 * ========================================================================= */
#include "../include/apue.h"

int main(int argc, char *argv[argc + 1]) {
  int result;

  /* result will be 0 */
  result = printf("");
  printf("\nresult = %d\n", result);

  /* Prints 0 characters; result will be 0 */
  result = printf("%.0s", "hello");
  printf("\nresult = %d\n", result);

  return 0;
}
