/* apue.3e/fileio/seek_f0301.c */
/* Rehearsed: Tue Dec  9 14:27:22 +01 2025 */
/* Figure 3.1: Tets whether standard input is capable of seeking. */

#include "../include/apue.h"

int main(void) {
  if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
    printf("Cannot seek.\n");
  else
    printf("Seek OK!\n");

  exit(0);
}
