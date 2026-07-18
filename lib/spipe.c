/* =========================================================================
 * Created on: <Fri Jul 17 14:53:05 +01 2026>
 * Time-stamp: <Fri Jul 17 14:53:55 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/lib/spipe.c -
 *
 * Figure 17.2 Creating a full-duplex pipe
 * ========================================================================= */
#include "apue.h"
#include <sys/socket.h>

/*
 * Returns a full-duplex pipe (a UNIX domain socket) with
 * the two file descriptors returned in fd[0] and fd[1].
 */
int fd_pipe(int fd[2]) { return (socketpair(AF_UNIX, SOCK_STREAM, 0, fd)); }
