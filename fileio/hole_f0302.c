/* apue.3e/fileio/hole_f0302.c */
/* Rehearsed: Tue Dec  9 15:34:22 +01 2025 */
/* Figure 3.2: Create a file with a hole in it by changing the file offset. */
/* Usage:
 *    $ ./hole
 *    $ ls -l file.hole  # check its size
 *    $ od -c file.hole  # let’s look at the actual contents
 *    $ ./nohole         # Create the nohole file and optionally look inside
 *    $ ls -l file.hole  file.nohole  # Compare sizes
 * */

#include "../include/apue.h"
#include <fcntl.h>

/* Declare 10-char strings */
static char head_str[] = "abcdefghij";
static char tail_str[] = "ABCDEFGHIJ";

int main(void) {

  int fd;

  if ((fd = creat("file.hole", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    err_sys("creat error");

  if (write(fd, head_str, strlen(head_str)) != strlen(head_str))
    err_sys("head_str write error");
  /* offset is 10 */

  if (lseek(fd, (1 << 14), SEEK_SET) == -1)
    err_sys("lseek error");
  /* Now offset is 2^14= 16384 */

  if (write(fd, tail_str, strlen(tail_str)) != strlen(tail_str))
    err_sys("tail_str write error");
  /* Now offset is 16394 */

  exit(0);
}
