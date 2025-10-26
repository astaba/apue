/* Figure 1.5: Buffered I/O behaving right like unbuffered I/O */

#include "apue.h"

int main(void) {
  int c;

  while ((c = getc(stdin)) != EOF)
    if (putc(c, stdout) == EOF)
      err_sys("output error");

  if (ferror(stdin))
    err_sys("input error");

  exit(0);
}
