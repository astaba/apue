/* =========================================================================
 * Created on: <Fri Jul 17 14:19:28 +01 2026>
 * Time-stamp: <Fri Jul 17 14:22:20 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/intro/testerror.c -
 *
 * Figure 1.8: Demonstrate strerror and perror.
 * ========================================================================= */
#include "apue.h"
#include <errno.h>

int main(int argc, char *argv[]) {

  fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
  errno = ENOENT;
  perror(argv[0]);

  exit(0);
}
