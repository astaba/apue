/* =========================================================================
 * Created on: <Fri Jul 17 15:34:35 +01 2026>
 * Time-stamp: <Fri Jul 17 16:28:16 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc2/opend.fe/opend.h -
 *
 * Figure 17.20 The opend.h header, version 1
 * ========================================================================= */
#include "apue.h"
#include <errno.h>

#define CL_OPEN "open" /* client's request for server */

extern char errmsg[];  /* error message string to return to client */
extern int oflag;      /* open() flag: O_xxx ... */
extern char *pathname; /* of file to open() for client */

int cli_args(int, char **);
void handle_request(char *, int, int);
