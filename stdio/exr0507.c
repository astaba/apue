/* =========================================================================
 * Created on: <Sun Jun 28 13:39:23 +01 2026>
 * Time-stamp: <Sun Jun 28 18:45:08 +01 2026 by owner>
 * Author    : owner
 * Desc      : ~/coding/c_prog/apue.3e/stdio/exr0507.c -
 * ========================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

/* Our Custom Cookie Structure */
typedef struct {
  char   *buf;
  size_t  size;
  size_t  offset;
} mem_cookie_t;

/* 1. The Intercepted Read Function */
static int mem_read(void *cookie, char *buf, int nbytes) {
  mem_cookie_t *mem = (mem_cookie_t *)cookie;

  // Check if we are already at the end of our memory block
  if (mem->offset >= mem->size)
    return 0;

  // Don't read past the available buffer boundary
  if (mem->offset + nbytes > mem->size)
    nbytes = mem->size - mem->offset;

  memcpy(buf, mem->buf + mem->offset, nbytes);
  mem->offset += nbytes;
  return nbytes;
}

/* 2. The Intercepted Write Function */
static int mem_write(void *cookie, const char *buf, int nbytes) {
  mem_cookie_t *mem = (mem_cookie_t *)cookie;

  if (mem->offset >= mem->size)
    return 0; // Out of bounds buffer space

  if (mem->offset + nbytes > mem->size)
    nbytes = mem->size - mem->offset;

  memcpy(mem->buf + mem->offset, buf, nbytes);
  mem->offset += nbytes;
  return nbytes;
}

/* 3. The Intercepted Seek Function */
static fpos_t mem_seek(void *cookie, fpos_t offset, int whence) {
  mem_cookie_t *mem = (mem_cookie_t *)cookie;
  fpos_t new_offset = mem->offset;

  switch (whence) {
  case SEEK_SET: new_offset = offset; break;
  case SEEK_CUR: new_offset += offset; break;
  case SEEK_END: new_offset = mem->size + offset; break;
  }

  if (new_offset < 0 || (size_t)new_offset > mem->size)
    return -1; /* Out of bounds */

  mem->offset = (size_t)new_offset;
  return new_offset;
}

/* 4. The Intercepted Close Function */
static int mem_close(void *cookie) {
  // Free the tracking cookie structure allocation
  free(cookie);
  return 0;
}

/* The Final Interface Function */
FILE *my_fmemopen(void *buf, size_t size, const char *mode) {
  // Basic setup for demonstration purposes (ignoring complex mode parsing for clarity)
  mem_cookie_t *cookie = malloc(sizeof(mem_cookie_t));
  if (cookie == NULL)
    return NULL;

  cookie->buf = (char *)buf;
  cookie->size = size;
  cookie->offset = 0;

  // Tie our memory methods directly into the BSD stream generator
  return funopen(cookie, mem_read, mem_write, mem_seek, mem_close);
}
