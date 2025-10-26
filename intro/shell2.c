/* Figure 1.10: Read commands from standard input and execute them. */
/*
 * This version: catch SIGINT before the kernel execute the default action
 * And handle it with a call to a custom function
 * */
#include "apue.h"
#include <stdio.h>
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
  printf("\tCaught SIGINT and print another prompt:\n%% ");
  /* NOTE: Comment out fflush() call and see how preceding printf output gets
   * split on '\n' accross fgets() input wait and protoshell prompt ... */
  fflush(stdout);
}
