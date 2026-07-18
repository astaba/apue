/* =========================================================================
 * Created on: <Sat Jun 27 13:20:24 +01 2026>
 * Time-stamp: <Sun Jun 28 04:12:47 +01 2026 by owner>
 * Author    : owner
 * Desc      : ~/coding/c_prog/apue.3e/stdio/exr0505.c -
 *
 * Exercise 5.5: How would you use the =fsync= function (Section 3.13)
 * with a standard I/O stream?
 * ========================================================================= */
#include "apue.h" /* IWYU pragma: keep */

int main(void) {
  FILE *fp;
  int fd;

  fp = fopen("critical_data.log", "w");
  if (fp == NULL)
    err_sys("fopen() failed");

  /* Write transaction records to the stream */
  fputs("Transaction ID: 98234-SUCCESS\n", fp);
  fputs("Amount: $5000.00\n", fp);

  /* STEP 1: Flush user-space stdio buffers into the kernel page
   * cache.  If you skip this, fsync() will run on an empty kernel
   * cache!
   */

  /* abort(); */
  if (fflush(fp) != 0) {
    fclose(fp);
    err_sys("fflush() failed");
  }
  /* abort(); */

  /* STEP 2: Extract the raw file descriptor from the FILE pointer. */
  fd = fileno(fp);
  if (fd == -1) {
    fclose(fp);
    err_sys("fileno() failed");
  }

  /* STEP 3: Force the kernel to commit dirty pages to persistent
   * hardware. */

  if (fsync(fd) == -1) {
    fclose(fp);
    err_sys("fsync() failed");
  }

  printf("Data successfully anchored to physical storage.\n");
  fclose(fp);
  return 0;
}
