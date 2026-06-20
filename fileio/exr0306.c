/* =========================================================================
 * Created on: <Thu Dec  4 19:54:38 +01 2025>
 * Time-stamp: <Mon Jun 15 21:44:20 +01 2026 by owner>
 * Author    : owner
 * Desc      : ~/coding/c_prog/apue.3e/fileio/exr0306.c -
 *
 * Exercise 3.6: If you open a file for read–write with the append
 * flag, can you still read from anywhere in the file using lseek? Can
 * you use lseek to replace existing data in the file? Write a program
 * to verify this.
 *
 * My answer: with O_APPEND you can still read from wherever you want
 * using lseek() but when it comes to write lseek() has no
 * effect. Atomic behavior takes precedence to set File Table Entry
 * offset to the last updated file size from v-node before writting at
 * the end, always at the and.
 * ========================================================================= */
#include "../include/apue.h"
#include <fcntl.h>

int main(int argc, char *argv[argc + 1]) {
  if (argc == 1)
    err_quit("Usage: %s <textfile>", argv[0]);
  const char *filename = argv[1];

  int fd = open(filename, O_RDWR | O_APPEND);
  if (fd == -1)
    err_sys("open error");

  char buf[4096];

  /* 1st read from 0 */
  ssize_t read_bytes = read(fd, buf, 10);
  if (read_bytes < 0)
    err_sys("read error");
  buf[read_bytes] = '\0';
  printf(" --- FIRST read (0 - 9) ---\n%s\n", buf);

  off_t offset = lseek(fd, 0, SEEK_CUR);
  printf(" --- After 1st read, Current offset: %zu\n", offset);

  /* 2nd read from 0 */
  lseek(fd, 0, SEEK_SET);
  read_bytes = read(fd, buf, 62);
  if (read_bytes < 0)
    err_sys("read error");
  buf[read_bytes] = '\0';
  printf(" --- SECOND read (0 - 61) ---\n%s\n", buf);

  offset = lseek(fd, 0, SEEK_CUR);
  printf(" --- After 2nd read, Current offset: %zu\n", offset);

  /* 1st Write: presumable from 62 */
  char *msg1 = "FIRST WRITE!\n";
  if (write(fd, msg1, strlen(msg1)) != strlen(msg1))
    err_sys("write error");

  offset = lseek(fd, 0, SEEK_CUR);
  printf(" --- After 1st write, Current offset: %zu\n", offset);

  /* 2nd Write: presumable from -186 */
  lseek(fd, -186, SEEK_END);
  char *msg2 = "SECOND WRITE!\n";
  if (write(fd, msg2, strlen(msg2)) != strlen(msg2))
    err_sys("write error");

  offset = lseek(fd, 0, SEEK_CUR);
  printf(" --- After 2nd write, Current offset: %zu\n", offset);

  close(fd);

  return EXIT_SUCCESS;
}
