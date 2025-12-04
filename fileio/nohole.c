/* Utility code to create a nohole file needed by seek.c demonstration */
/* Created on: Sun Nov  9 15:56:47 +01 2025 */

/* #include "apue.h" */
#include "../include/apue.h"
#include <fcntl.h>

#define FILE_SIZE 16394

int main(void) {
  int fd;
  char template[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  size_t i;
  size_t len = strlen(template);
  size_t chunknumb = FILE_SIZE / len;
  size_t remainder = FILE_SIZE % len;

  if ((fd = creat("file.nohole", FILE_MODE)) < 0)
    err_sys("creat error");

  for (i = 0; i < chunknumb; i++)
    if (write(fd, template, len) != len)
      err_sys("buf1 write error");

  if (write(fd, template, remainder) != remainder)
    err_sys("buf1 write error");

  exit(0);
}
