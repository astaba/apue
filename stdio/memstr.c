/* =========================================================================
 * Created on: <Thu Jun 25 18:43:45 +01 2026>
 * Time-stamp: <Thu Jun 25 19:35:49 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/stdio/memstr.c -
 *
 * Figure 5.15: It’s instructive to look at how writes to a memory
 * stream operate on a buffer we provide. This program shows a sample
 * program that seeds the buffer with a known pattern to see how
 * writes to the stream behave.
 * ========================================================================= */
#include "../include/apue.h"

#define BSZ 48

int main() {
  FILE *fp;
  char buf[BSZ];

  memset(buf, 'a', BSZ - 2);
  buf[BSZ - 2] = '\0';
  buf[BSZ - 1] = 'X';
  if ((fp = fmemopen(buf, BSZ, "w+")) == NULL)
    err_sys("fmemopen failed");
  printf("initial buffer contents: %s\n", buf);
  fprintf(fp, "hello, world");
  printf("before flush: %s\n", buf);
  fflush(fp);
  printf("after fflush: %s\n", buf);
  printf("len of string in buf = %ld\n", (long)strlen(buf));

  memset(buf, 'b', BSZ - 2);
  buf[BSZ - 2] = '\0';
  buf[BSZ - 1] = 'X';
  /* fp offset is still at strlen("hello, world") + '\0' appended by
     the last fflush() call. Basecally the last routine operating on
     the fp stream. Consequently, the next print skips as much 'b's to
     overwrite the next 'b's. */
  fprintf(fp, "hello, world");
  fseek(fp, 0, SEEK_SET);
  printf("after  fseek: %s\n", buf);
  printf("len of string in buf = %ld\n", (long)strlen(buf));

  memset(buf, 'c', BSZ - 2);
  buf[BSZ - 2] = '\0';
  buf[BSZ - 1] = 'X';
  /* The last fseek() set the offset at the beginning */
  fprintf(fp, "hello, world");
  fclose(fp);
  printf("after fclose: %s\n", buf);
  printf("len of string in buf = %ld\n", (long)strlen(buf));

  return (0);
}
