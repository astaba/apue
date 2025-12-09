/* apue.3e/fileio/nohole_uf0302.c */
/* Rehearsed: Tue Dec  9 15:34:26 +01 2025 */
/* Utility code to create a nohole file needed by seek.c demonstration */
/* Created on: Sun Nov  9 15:56:47 +01 2025 */

/* #include "apue.h" */
#include "../include/apue.h"
#include <fcntl.h>

#define TARGET_SIZE 16394

static char template[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, char *argv[]) {
  int fd;
  size_t i;
  size_t len = strlen(template);
  size_t chunks_nbr = TARGET_SIZE / len;
  size_t remainder = TARGET_SIZE % len;

  if ((fd = creat("file.nohole", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    err_sys("creat error");

  for (i = 0; i < chunks_nbr; i++)
    if (write(fd, template, len) != len)
      err_sys("write error");
  if (write(fd, template, remainder) != remainder)
    err_sys("write error");

  exit(0);
}
