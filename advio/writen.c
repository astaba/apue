/* =========================================================================
 * Created on: <Fri Jul 17 14:48:13 +01 2026>
 * Time-stamp: <Fri Jul 17 14:51:17 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/advio/writen.c -
 *
 * Figure 14.24 The readn and writen functions
 * ========================================================================= */
#include "apue.h"

ssize_t /* Write "n" bytes to a descriptor  */
writen(int fd, const void *ptr, size_t n) {
  size_t nleft;
  ssize_t nwritten;

  nleft = n;
  while (nleft > 0) {
    if ((nwritten = write(fd, ptr, nleft)) < 0) {
      if (nleft == n)
        return (-1); /* error, return -1 */
      else
        break; /* error, return amount written so far */
    } else if (nwritten == 0) {
      break;
    }
    nleft -= nwritten;
    ptr += nwritten;
  }
  return (n - nleft); /* return >= 0 */
}
