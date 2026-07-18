/* =========================================================================
 * Created on: <Wed Jun 24 19:24:06 +01 2026>
 * Time-stamp: <Mon Jul 13 01:10:55 +01 2026 by owner>
 * Author    : owner
 * Desc      : ~/coding/c_prog/apue.3e/stdio/ybuf.c -
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

static void pr_stdio(FILE *, const char *, FILE *);
static int is_unbuffered(FILE *);
static int is_linebuffered(FILE *);
static int buffer_size(FILE *);

int main(void) {
  FILE *fp_log;
  char filename[] = "std.log";

  /* Open a file stream to output standard streams status in the
   * absence of I/O without using stdout */
  fp_log = fopen(filename, "w");
  if (fp_log == NULL)
    err_sys("fopen() failed");

  /* 1. NOTE: Display buffering status of standard streams without
   * I/O: It brings about the lazy behavior of Standard I/O
   * Library. */

  pr_stdio(fp_log, "stdin", stdin);
  pr_stdio(fp_log, "stdout", stdout);
  pr_stdio(fp_log, "stderr", stderr);

  /* 2. NOTE: Since the first I/O operation usually causes the buffers
   * to be allocated for a stream, by performing I/O on each stream we
   * effectively change its buffering status */

  fputs("enter any character\n", stdout); /* I/O on stdout */
  if (getchar() == EOF)                   /* I/O on stdin */
    err_sys("getchar error");
  fputs("one line to standard error\n", stderr); /* I/O on stderr */

  /* Display buffering status of standard streams after I/O */
  pr_stdio(stdout, "stdin", stdin);
  pr_stdio(stdout, "stdout", stdout);
  pr_stdio(stdout, "stderr", stderr);

  /* Display buffering status of regular file stream after I/O */
  pr_stdio(stdout, filename, fp_log);

  exit(0);
}

/**
 * Dsiplay on stream FILE the buffering type of a fp FILE together
 * with its buffer size.
 */
static void pr_stdio(FILE *stream, const char *name, FILE *fp) {
  fprintf(stream, "stream = %s, ", name);
  if (is_unbuffered(fp))
    fprintf(stream, "unbuffered");
  else if (is_linebuffered(fp))
    fprintf(stream, "line buffered");
  else /* if neither of above */
    fprintf(stream, "fully buffered");
  fprintf(stream, ", buffer size = %d\n", buffer_size(fp));
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
