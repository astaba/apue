/* =========================================================================
 * Created on: <Sun Jun 28 19:55:13 +01 2026>
 * Time-stamp: <Sun Jun 28 19:56:54 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/environ/opendata.c -
 *
 * Figure 7.14 Incorrect usage of an automatic variable
 * ========================================================================= */
#include <stdio.h>

FILE *open_data(void) {
  FILE *fp;
  char databuf[BUFSIZ]; /* setvbuf makes this the stdio buffer */

  if ((fp = fopen("datafile", "r")) == NULL)
    return (NULL);

  if (setvbuf(fp, databuf, _IOLBF, BUFSIZ) != 0)
    return (NULL);

  return (fp); /* error */
}
