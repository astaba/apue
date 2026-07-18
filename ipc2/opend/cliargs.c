/* =========================================================================
 * Created on: <Fri Jul 17 19:05:37 +01 2026>
 * Time-stamp: <Fri Jul 17 19:47:42 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc2/opend/cliargs.c -
 *
 * Figure 17.24.alt The cli_args function
 * ========================================================================= */
#include "opend.h"

/*
 * This function is called by buf_args(), which is called by
 * handle_request().  buf_args() has broken up the client's
 * buffer into an argv[]-style array, which we now process.
 */
int cli_args(int argc, char **argv) {
  if (argc != 3 || strcmp(argv[0], CL_OPEN) != 0) {
    strcpy(errmsg, "usage: <pathname> <oflag>\n");
    return (-1);
  }
  pathname = argv[1]; /* save ptr to pathname to open */
  oflag = atoi(argv[2]);
  return (0);
}
