/* =========================================================================
 * Created on: <Fri Jun 26 18:47:16 +01 2026>
 * Time-stamp: <Sun Jul 12 20:35:13 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/intro/shell2.c -
 *
 * Figure 1.10: Read commands from standard input and execute
 * them. This version: catch SIGINT before the kernel execute the
 * default action and handles it with a call to a custom function.
 * See [[file:yshell2.c][Figure 1.7]], [[file:shell1.c][Figure 1.7]]
 * ========================================================================= */
#include "apue.h"
#include <sys/wait.h>

static void sig_int(int); /* our signal-catching function */

int main(void) {
  char buf[MAXLINE]; /* from apue.h */
  pid_t pid;
  int status;

  if (signal(SIGINT, sig_int) == SIG_ERR)
    err_sys("signal error");

  printf("%% "); /* print prompt (printf requires %% to print %) */
  while (fgets(buf, MAXLINE, stdin) != NULL) {

    if (buf[strlen(buf) - 1] == '\n')
      buf[strlen(buf) - 1] = 0; /* replace newline with null */

    if ((pid = fork()) < 0) {
      err_sys("fork error");
    } else if (pid == 0) { /* child */
      execlp(buf, buf, (char *)0);
      err_ret("couldn’t execute: %s", buf);
      exit(127);
    }

    /* parent */
    if ((pid = waitpid(pid, &status, 0)) < 0)
      err_sys("waitpid error");
    printf("%% ");
  }
  exit(0);
}

void sig_int(int signo) {
  /* Async-Signal UNSAFE: */
  printf("interrupt\n%% ");
}
