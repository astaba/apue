/* =========================================================================
 * Created on: <Fri Jul 17 14:39:16 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:19 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/signals/tsleep2.c -
 *
 * Figure 10.9 Calling sleep2 from a program that catches other signals
 * ========================================================================= */
#include "apue.h"

unsigned int sleep2(unsigned int);
static void sig_int(int);

int main(void) {
  unsigned int unslept;

  if (signal(SIGINT, sig_int) == SIG_ERR)
    err_sys("signal(SIGINT) error");
  unslept = sleep2(5);
  printf("sleep2 returned: %u\n", unslept);
  exit(0);
}

static void sig_int(int signo) {
  int i, j;
  volatile int k;

  /*
   * Tune these loops to run for more than 5 seconds
   * on whatever system this test program is run.
   */
  printf("\nsig_int starting\n");
  for (i = 0; i < 300000; i++)
    for (j = 0; j < 4000; j++)
      k += i * j;
  printf("sig_int finished\n");
}
