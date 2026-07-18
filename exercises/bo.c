/* =========================================================================
 * Created on: <Thu Jul 16 05:26:00 +01 2026>
 * Time-stamp: <Fri Jul 17 14:05:28 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/exercises/bo.c -
 *
 * Figure C.22 [[file:../sockets/README.org::#exercise-16-1]] Solution.
 * 
 * Determine byte order on system
 * ========================================================================= */
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  uint32_t i = 0x04030201;
  unsigned char *cp = (unsigned char *)&i;

  if (*cp == 1)
    printf("little-endian\n");
  else if (*cp == 4)
    printf("big-endian\n");
  else
    printf("who knows?\n");
  exit(0);
}
