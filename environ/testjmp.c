/* =========================================================================
 * Created on: <Sun Jun 28 19:47:04 +01 2026>
 * Time-stamp: <Sun Jun 28 19:49:11 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/environ/testjmp.c -
 *
 * Figure 7.13 Effect of longjmp on various types of variables
 * ========================================================================= */
#include "apue.h" /* IWYU pragma: keep */
#include <setjmp.h>

static void f1(int, int, int, int);
static void f2(void);

static jmp_buf jmpbuffer;
static int globval;

int main(void) {
  int autoval;
  register int regival;
  volatile int volaval;
  static int statval;

  globval = 1;
  autoval = 2;
  regival = 3;
  volaval = 4;
  statval = 5;

  if (setjmp(jmpbuffer) != 0) {
    printf("after longjmp:\n");
    printf("globval = %d, autoval = %d, regival = %d,"
           " volaval = %d, statval = %d\n",
           globval, autoval, regival, volaval, statval);
    exit(0);
  }

  /*
   * Change variables after setjmp, but before longjmp.
   */
  globval = 95;
  autoval = 96;
  regival = 97;
  volaval = 98;
  statval = 99;

  f1(autoval, regival, volaval, statval); /* never returns */
  exit(0);
}

static void f1(int i, int j, int k, int l) {
  printf("in f1():\n");
  printf("globval = %d, autoval = %d, regival = %d,"
         " volaval = %d, statval = %d\n",
         globval, i, j, k, l);
  f2();
}

static void f2(void) {
  /* clang-format off */
  longjmp(jmpbuffer, 1);
  /* clang-format on */
}
