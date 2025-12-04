/* Figure 3.2: Create a file with a hole in it by changing the file offset. */
/* Usage:
 *    $ ./hole
 *    $ ls -l file.hole  # check its size
 *    $ od -c file.hole  # let’s look at the actual contents
 *    $ ./nohole         # Create the nohole file and optionally look inside
 *    $ ls -l file.hole  file.nohole  # Compare sizes
 * */

/* #include "apue.h" */
#include "../include/apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void) {
  int fd;

  if ((fd = creat("file.hole", FILE_MODE)) < 0)
    err_sys("creat error");

  if (write(fd, buf1, 10) != 10)
    err_sys("buf1 write error");
  /* offset now = 10 */

  if (lseek(fd, (1 << 14), SEEK_SET) == -1) /* (4 * 4096) = 16384 */
    err_sys("lseek error");
  /* offset now = 16384 */

  if (write(fd, buf2, 10) != 10)
    err_sys("buf2 write error");
  /* offset now = 16384 + 10 */

  exit(0);
}
