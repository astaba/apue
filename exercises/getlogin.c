/* =========================================================================
 * Created on: <Thu Jul 16 05:04:19 +01 2026>
 * Time-stamp: <Fri Jul 17 14:05:28 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/exercises/getlogin.c -
 *
 * Figure C.14 [[file:../daemons/README.org::#exercise-13-3]] Solution.
 * 
 * Call daemonize and then obtain login name
 * ========================================================================= */
#include "apue.h"

int main(void) {
  FILE *fp;
  char *p;

  daemonize("getlog");
  p = getlogin();
  fp = fopen("/tmp/getlog.out", "w");
  if (fp != NULL) {
    if (p == NULL)
      fprintf(fp, "no login name\n");
    else
      fprintf(fp, "login name: %s\n", p);
  }
  exit(0);
}
