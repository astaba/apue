/* =========================================================================
 * Created on: <Fri Jul 17 15:39:19 +01 2026>
 * Time-stamp: <Fri Jul 17 15:40:12 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc2/opend/main.c -
 *
 * Figure 17.28 The server main function, version 2
 * ========================================================================= */
#include "opend.h"
#include <syslog.h>

int debug, oflag, client_size, log_to_stderr;
char errmsg[MAXLINE];
char *pathname;
Client *client = NULL;

int main(int argc, char *argv[]) {
  int c;

  log_open("open.serv", LOG_PID, LOG_USER);

  opterr = 0; /* don't want getopt() writing to stderr */
  while ((c = getopt(argc, argv, "d")) != EOF) {
    switch (c) {
    case 'd': /* debug */
      debug = log_to_stderr = 1;
      break;

    case '?':
      err_quit("unrecognized option: -%c", optopt);
    }
  }

  if (debug == 0)
    daemonize("opend");

  loop(); /* never returns */
}
