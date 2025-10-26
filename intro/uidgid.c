/* Figure 1.9: Print user ID and group ID. */

#include "apue.h"

int main(void) {
  printf("uid = %d, gid = %d\n", getuid(), getgid());
  exit(0);
}
