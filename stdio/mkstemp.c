/* =========================================================================
 * Created on: <Wed Jun 24 20:29:34 +01 2026>
 * Time-stamp: <Mon Jul 13 11:43:43 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/stdio/mkstemp.c -
 *
 * Figure 5.13: shows how to use (and how not to use) the mkstemp
 * function.
 * ========================================================================= */
#include "apue.h"
#include <errno.h>

void make_temp(char *template);

int main() {
  /* right way: good_template Type is char[15]: A 15-byte array on the
     stack containing the string */
  char good_template[] = "/tmp/tmpXXXXXX";
  /* wrong way: bad_template Type is pointer (8 bytes) on the stack,
     pointing to a string on the read-only data segment. */
  char *bad_template = "/tmp/tmpXXXXXX";

  printf("trying to create first temp file...\n");
  make_temp(good_template);
  printf("trying to create second temp file...\n");
  make_temp(bad_template);
  exit(0);
}

void make_temp(char *template) {
  int fd;
  struct stat sbuf;

  if ((fd = mkstemp(template)) < 0) /* Create tmp file */
    err_sys("can't create temp file");
  /* Display filename of successfully created tmp file */
  printf("temp name = %s\n", template);

  /* NOTE: Close tmp file and check its persistence to prove that
     unlike tmpfile(), after mkstemp() successfully returns it
     behooves to the caller to remove the tmp file. */
  close(fd);

  /* Check tmp file existence: if exists then unlink */
  if (stat(template, &sbuf) < 0) {
    if (errno == ENOENT)
      printf("file doesn't exist\n");
    else
      err_sys("stat() failed");
  } else {
    printf("file exists\n");
    unlink(template);
  }
}
