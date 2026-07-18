/* =========================================================================
 * Created on: <Fri Jun 26 16:54:25 +01 2026>
 * Time-stamp: <Sun Jul 12 20:01:21 +01 2026 by owner>
 * Author    : owner
 * Desc      : ~/coding/c_prog/apue.3e/stdio/exr0501.c -
 *
 * Exercise 5.1: Implement setbuf using setvbuf.
 * ========================================================================= */
#include "apue.h"

/* Implementation of setbuf using setvbuf */
static void my_setbuf(FILE *fp, char *buf) {
  /* static void my_setbuf(FILE *restrict fp, char *restrict buf) { */
  /* Check this compilation error */

  if (setvbuf(fp, buf, (buf == NULL) ? _IONBF : _IOFBF, BUFSIZ) != 0)
    err_sys("setvbuf() failed");
}
/* FIXME: (1) No way to let the system force line-buffering on
   terminal dectection like setbuf() would allow. (2) No way to let
   the system use the optimized st_blksize. (3) Provide test
   example. */

int main(void) {
  char my_buffer[BUFSIZ];

  printf("Testing my_setbuf...\n");

  /* Test 1: Turn on Full Buffering with a custom allocation space */
  my_setbuf(stdout, my_buffer);
  printf("This prompt is now trapped in full buffering.");
  /* abort(); */

  /* Force physical output to prove it works */
  fflush(stdout);
  /* abort(); */

  /* Test 2: Turn off Buffering entirely (Equivalent to passing NULL) */
  my_setbuf(stdout, NULL);
  printf("This text hits the terminal screen instantly!");
  /* abort(); */

  return 0;
}
