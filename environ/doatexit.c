/* =========================================================================
 * Created on: <Sun Jun 28 19:32:58 +01 2026>
 * Time-stamp: <Sun Jun 28 19:36:26 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/environ/doatexit.c -
 *
 * Figure 7.3 demonstrates the use of the atexit function.
 * ========================================================================= */
#include "apue.h"

static void my_exit1(void);
static void my_exit2(void);

int main(void) {
  if (atexit(my_exit2) != 0)
    err_sys("can't register my_exit2");

  if (atexit(my_exit1) != 0)
    err_sys("can't register my_exit1");
  if (atexit(my_exit1) != 0)
    err_sys("can't register my_exit1");

  printf("main is done\n");
  return (0);
}

static void my_exit1(void) {
  /* clang-format off */
  printf("first exit handler\n");
  /* clang-format on */
}

static void my_exit2(void) {
  /* clang-format off */
  printf("second exit handler\n");
  /* clang-format on */
}
