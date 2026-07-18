/* =========================================================================
 * Created on: <Tue Dec  9 14:27:22 +01 2025>
 * Time-stamp: <Mon Jun 15 17:38:37 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/fileio/lseek_stdin.c -
 *
 * Figure 3.1: This program tests its standard input to see whether it
 * is capable of seeking.
 * ========================================================================= */
#include "apue.h"

int main(void) {
  if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
    printf("Cannot seek.\n");
  else
    printf("Seek OK!\n");

  exit(0);
}
