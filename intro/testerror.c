/* Figure 1.8: Demonstrate strerror and perror. */

#include "apue.h"
#include <errno.h>

int main(int argc, char *argv[]) {

  fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
  errno = ENOENT;
  perror(argv[0]);

  exit(0);
}
