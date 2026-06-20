/* =========================================================================
 * Created on: <Tue Dec  9 16:00:23 +01 2025> 
 * Time-stamp: <Mon Jun 15 18:38:55 +01 2026 by owner> 
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/fileio/copy_inout.c - 
 *
 * Figure 3.5: Copy standard input to standard output.
 * ========================================================================= */
#include "../include/apue.h"
#include <fcntl.h>
#include <sys/stat.h>

#define BUFF_SIZE 4096

int main(int argc, char *argv[]) {
  /* Calling our custom set_fl() as followed would force each write() to wait
   * for data to be written on disk before returning instead of queuing data
   * for later write as is the default behavior of write() */
  set_fl(STDOUT_FILENO, O_SYNC);

  ssize_t nbytes;
  char buf[BUFF_SIZE];

  while ((nbytes = read(STDIN_FILENO, buf, BUFF_SIZE)) > 0)
    if (write(STDOUT_FILENO, buf, nbytes) != nbytes)
      err_sys("write error");

  if (nbytes < 0)
    err_sys("read error");

  exit(0);
}
