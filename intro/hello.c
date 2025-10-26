/* Figure 1.6: Print the process ID */

#include "apue.h"

int main(void) {
  printf("hello world from process ID %ld\n", (long)getpid());
  exit(0);
}
