/* =========================================================================
 * Created on: <Sun Jun 28 19:45:19 +01 2026>
 * Time-stamp: <Sun Jun 28 19:46:24 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/environ/cmd2.c -
 *
 * Figure 7.11 Example of setjmp and longjmp
 * ========================================================================= */
#include "apue.h"
#include <setjmp.h>

#define TOK_ADD 5

jmp_buf jmpbuffer;

int main(void) {
  char line[MAXLINE];

  if (setjmp(jmpbuffer) != 0)
    printf("error");
  while (fgets(line, MAXLINE, stdin) != NULL)
    do_line(line);
  exit(0);
}

/* ... */

    void
    cmd_add(void) {
  int token;

  token = get_token();
  if (token < 0) /* an error has occurred */
    longjmp(jmpbuffer, 1);
  /* rest of processing for this command */
}
