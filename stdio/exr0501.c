/* =========================================================================
 * Created on: <Fri Jun 26 16:54:25 +01 2026>
 * Time-stamp: <Sat Jun 27 13:59:52 +01 2026 by owner>
 * Author    : owner
 * Desc      : ~/coding/c_prog/apue.3e/stdio/exr0501.c -
 *
 * Exercise 5.1: Implement setbuf using setvbuf.
 * ========================================================================= */
#include "../include/apue.h"

void my_setbuf(FILE *restrict fp, char *restrict buf) {
  int mode;

  mode = fp ? _IOFBF : _IONBF;

  if (setvbuf(fp, buf, mode, BUFSIZ) != 0)
    err_sys("setvbuf() failed");
}
/* FIXME: (1) No way to let the system force line-buffering on
   terminal dectection like setbuf() would allow. (2) No way to let
   the system use the optimized st_blksize. (3) Provide test
   example. */

/* Implementation of setbuf using setvbuf */
void my_setbuf2(FILE *restrict fp, char *restrict buf) {
  int mode;

  /* The buffering mode depends entirely on whether 'buf' is provided */
  if (buf == NULL) {
    mode = _IONBF;
  } else {
    mode = _IOFBF;
  }

  /* Per ISO C/POSIX specifications, setbuf returns no value, but if
   * setvbuf fails internally, we trap it. */
  if (setvbuf(fp, buf, mode, BUFSIZ) != 0) {
    perror("setvbuf failed");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  char my_buffer[BUFSIZ];

  printf("Testing my_setbuf...\n");

  /* Test 1: Turn on Full Buffering with a custom allocation space */
  my_setbuf(stdout, my_buffer);
  printf("This prompt is now trapped in full buffering.");

  /* Force physical output to prove it works */
  fflush(stdout);

  /* Test 2: Turn off Buffering entirely (Equivalent to passing NULL) */
  my_setbuf2(stdout, NULL);
  printf("\nThis text hits the terminal screen instantly!\n");

  return 0;
}
