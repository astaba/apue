/* =========================================================================
 * Created on: <Wed Jun 24 20:27:56 +01 2026>
 * Time-stamp: <Wed Jun 24 20:29:02 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/stdio/tempfiles.c -
 *
 * Figure 5.12 Demonstrate tmpnam and tmpfile functions
 * ========================================================================= */
#include "apue.h"

int main(void) {
  char name[L_tmpnam], line[MAXLINE];
  FILE *fp;

  printf("%s\n", tmpnam(NULL)); /* first temp name */

  tmpnam(name); /* second temp name */
  printf("%s\n", name);

  if ((fp = tmpfile()) == NULL) /* create temp file */
    err_sys("tmpfile error");
  fputs("one line of output\n", fp); /* write to temp file */
  rewind(fp);                        /* then read it back */
  if (fgets(line, sizeof(line), fp) == NULL)
    err_sys("fgets error");
  fputs(line, stdout); /* print the line we wrote */

  exit(0);
}
