/* =========================================================================
 * Created on: <Sun Jul 12 20:16:11 +01 2026>
 * Time-stamp: <Sun Jul 12 20:37:17 +01 2026 by owner>
 * Author    : owner
 * Desc      : ~/coding/c_prog/apue.3e/intro/yshell2.c -
 *
 * Figure 1.10: Read commands from standard input and execute
 * them. This version: catch SIGINT before the kernel execute the
 * default action and handles it with a call to a custom function.
 * See [[file:shell1.c][Figure 1.7]], [[file:shell2.c][Figure 1.10]]
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

  while (1) {
    printf("%% "); /* print prompt (printf requires %% to print %) */
    if (fgets(buf, MAXLINE, stdin) == NULL)
      break;

    if (buf[strlen(buf) - 1] == '\n')
      buf[strlen(buf) - 1] = 0; /* replace newline with null */

    if ((pid = fork()) < 0) {
      err_sys("fork error");
    } else if (pid == 0) { /* child */
      execlp(buf, buf, (char *)0);
      err_ret("couldn't execute: %s", buf);
      exit(127);
    }

    /* parent */
    if ((pid = waitpid(pid, &status, 0)) < 0)
      err_sys("waitpid error");
  }
  exit(0);
}

void sig_int(int signo) {

  /* Async-Signal UNSAFE:
   * See [[file:../stdio/README.org::#toy-shell-stdio-experiment]] */

  printf("\tCaught SIGINT\n%% ");

  /* NOTE: Because of standard I/O line-buffering the preceding printf
   * will only display up until the '\n'. Then fflush() call is
   * required to flush "%% " from standard I/O internal output buffer
   * (for stdout stream) to the kernel cache (which of course displays
   * it right away). */

  /* TEST: To better experiment the way line-buffered I/O is flushed
   * between internal input buffer and internal output buffer: (1)
   * change the preceding "%% " prompt to "$ " (or anything different
   * from the initial one); (2) then comment out the fflush call */

  fflush(stdout);
}
