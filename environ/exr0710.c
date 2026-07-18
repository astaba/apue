/* =========================================================================
 * Created on: <Sun Jun 28 20:01:09 +01 2026>
 * Time-stamp: <Sun Jun 28 20:04:00 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/environ/exr0710.c -
 *
 * Exercise 7.10: At the end of Section 7.10, we showed how a function
 * can’t return a pointer to an automatic variable. Is the following
 * code correct?
 * ========================================================================= */
int f1(int val) {

  int num = 0;
  int *ptr = &num;

  if (val == 0) {
    int val;

    val = 5;
    ptr = &val;
  }

  return (*ptr + 1);
}
