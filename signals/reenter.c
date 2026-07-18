/* =========================================================================
 * Created on: <Fri Jul 17 14:37:54 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:19 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/signals/reenter.c -
 *
 * Figure 10.5 Call a nonreentrant function from a signal handler
 * ========================================================================= */
#include "apue.h"
#include <pwd.h>

static void my_alarm(int signo) {
  struct passwd *rootptr;

  printf("in signal handler\n");
  if ((rootptr = getpwnam("root")) == NULL)
    err_sys("getpwnam(root) error");
  alarm(1);
}

int main(void) {
  struct passwd *ptr;

  signal(SIGALRM, my_alarm);
  alarm(1);
  for (;;) {
    if ((ptr = getpwnam("sar")) == NULL)
      err_sys("getpwnam error");
    if (strcmp(ptr->pw_name, "sar") != 0)
      printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
  }
}
