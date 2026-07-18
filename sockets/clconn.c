/* =========================================================================
 * Created on: <Fri Jul 17 14:51:39 +01 2026>
 * Time-stamp: <Fri Jul 17 14:53:55 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/sockets/clconn.c -
 *
 * Figure 16.10 Connect with retry
 * ========================================================================= */
#include "apue.h"
#include <sys/socket.h>

#define MAXSLEEP 128

int connect_retry(int sockfd, const struct sockaddr *addr, socklen_t alen) {
  int numsec;

  /*
   * Try to connect with exponential backoff.
   */
  for (numsec = 1; numsec <= MAXSLEEP; numsec <<= 1) {
    if (connect(sockfd, addr, alen) == 0) {
      /*
       * Connection accepted.
       */
      return (0);
    }

    /*
     * Delay before trying again.
     */
    if (numsec <= MAXSLEEP / 2)
      sleep(numsec);
  }
  return (-1);
}
