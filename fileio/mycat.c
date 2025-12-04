/* Figure 3.5: Copy standard input to standard output. */

/* #include "apue.h" */
#include "../include/apue.h"
#include <fcntl.h>

#define BUFFSIZE 4096

int main(void) {
  /* Calling our custom set_fl() as followed would force each write() to wait
   * for data to be written on disk before returning instead of queuing data
   * for later write as is the default behavior of write() */
  /* set_fl(STDOUT_FILENO, O_SYNC); */

  int n;
  char buf[BUFFSIZE];

  while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    if (write(STDOUT_FILENO, buf, n) != n)
      err_sys("write error");

  if (n < 0)
    err_sys("read error");

  exit(0);
}
