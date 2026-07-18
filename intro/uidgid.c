/* =========================================================================
 * Created on: <Fri Jul 17 14:19:36 +01 2026>
 * Time-stamp: <Fri Jul 17 14:22:19 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/intro/uidgid.c -
 *
 * Figure 1.9: Print user ID and group ID.
 * ========================================================================= */
#include "apue.h"

int main(void) {
  printf("uid = %d, gid = %d\n", getuid(), getgid());
  exit(0);
}
