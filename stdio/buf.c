/* =========================================================================
 * Created on: <Tue Jun 23 20:56:29 +01 2026>
 * Time-stamp: <Wed Jun 24 19:42:07 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/stdio/buf.c -
 *
 * Figure 5.11: This program prints the buffering for the three
 * standard streams and for a stream that is associated with a regular
 * file.
 *
 * Modern Version: Re-add missing internal definitions that modern
 * glibc hides from stdio.h
 * ========================================================================= */
#include "apue.h"

/* Explicitly bring in the layout definitions if they are concealed */
struct _IO_FILE_modern {
  int _flags;
  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base; /* Start of reserve area */
  char *_IO_buf_end;  /* End of reserve area */
};
/* Modern internal glibc buffering bitmasks */
#define MODERN_IO_LINE_BUF 0x0200
#define MODERN_IO_UNBUFFERED 0x0002

static void pr_stdio(const char *, FILE *);
static int is_unbuffered(FILE *);
static int is_linebuffered(FILE *);
static int buffer_size(FILE *);

int main(void) {
  FILE *fp;

  /* NOTE: Since the first I/O operation usually causes the buffers to
   * be allocated for a stream, by performing I/O on each stream we
   * effectively change its buffering status */

  fputs("enter any character\n", stdout); /* I/O on stdout */
  if (getchar() == EOF)                   /* I/O on stdin */
    err_sys("getchar error");
  fputs("one line to standard error\n", stderr); /* I/O on stderr */

  /* Display buffering status of standard streams after I/O */
  pr_stdio("stdin", stdin);
  pr_stdio("stdout", stdout);
  pr_stdio("stderr", stderr);

  /* Open file stream on regular disk file */
  if ((fp = fopen("/etc/passwd", "r")) == NULL)
    err_sys("fopen error");
  /* I/O on regular file */
  if (getc(fp) == EOF)
    err_sys("getc error");

  /* Display buffering status of regular file stream after I/O */
  pr_stdio("/etc/passwd", fp);

  exit(0);
}

/**
 * Dsiplay on stdout stream FILE the buffering type of a fp stream
 * FILE together with its buffer size.
 */
static void pr_stdio(const char *name, FILE *fp) {
  printf("stream = %s, ", name);
  if (is_unbuffered(fp))
    printf("unbuffered");
  else if (is_linebuffered(fp))
    printf("line buffered");
  else /* if neither of above */
    printf("fully buffered");
  printf(", buffer size = %d\n", buffer_size(fp));
}

static int is_unbuffered(FILE *fp) {
  struct _IO_FILE_modern *fp_int = (struct _IO_FILE_modern *)fp;
  return (fp_int->_flags & MODERN_IO_UNBUFFERED);
}

static int is_linebuffered(FILE *fp) {
  struct _IO_FILE_modern *fp_int = (struct _IO_FILE_modern *)fp;
  return (fp_int->_flags & MODERN_IO_LINE_BUF);
}

static int buffer_size(FILE *fp) {
  struct _IO_FILE_modern *fp_int = (struct _IO_FILE_modern *)fp;
  /* Calculate size by looking at the memory span of the allocated
   * reserve buffer */
  if (fp_int->_IO_buf_base == NULL || fp_int->_IO_buf_end == NULL)
    return 0;
  return (fp_int->_IO_buf_end - fp_int->_IO_buf_base);
}
