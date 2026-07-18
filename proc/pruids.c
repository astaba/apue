/* =========================================================================
 * Created on: <Fri Jul 17 14:35:53 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:19 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/proc/pruids.c -
 *
 * Figure 8.25 Print real and effective user IDs
 * ========================================================================= */
#include "apue.h"

int main(void) {
  printf("real uid = %d, effective uid = %d\n", getuid(), geteuid());
  exit(0);
}
