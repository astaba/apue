/* =========================================================================
 * Created on: <Fri Jul 17 15:30:40 +01 2026>
 * Time-stamp: <Fri Jul 17 16:29:05 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc2/open.fe/open.h -
 *
 * Figure 17.17 The open.h header
 * ========================================================================= */
#include "apue.h"
#include <errno.h>

#define CL_OPEN "open" /* client's request for server */

int csopen(char *, int);
