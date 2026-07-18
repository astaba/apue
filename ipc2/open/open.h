/* =========================================================================
 * Created on: <Fri Jul 17 19:30:56 +01 2026>
 * Time-stamp: <Fri Jul 17 19:47:43 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc2/open/open.h -
 *
 * Figure 17.17.alt The open.h header
 * ========================================================================= */
#include "apue.h"
#include <errno.h>

#define CL_OPEN "open"              /* client's request for server */
#define CS_OPEN "/tmp/opend.socket" /* server's well-known name */

int csopen(char *, int);
