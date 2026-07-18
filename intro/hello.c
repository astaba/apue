/* =========================================================================
 * Created on: <Fri Jul 17 14:19:22 +01 2026>
 * Time-stamp: <Fri Jul 17 14:22:20 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/intro/hello.c -
 *
 * Figure 1.6: Print the process ID
 * ========================================================================= */
#include "apue.h"

int main(void) {
  printf("hello world from process ID %ld\n", (long)getpid());
  exit(0);
}
