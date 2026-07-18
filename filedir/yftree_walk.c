/* =========================================================================
 * Created on: <Wed Dec 10 14:53:21 +01 2025>
 * Time-stamp: <Fri Jun 19 17:50:40 +01 2026 by owner>
 * Author    : owner
 * Desc      : ~/coding/c_prog/apue.3e/filedir/yftree_walk.c -
 *
 * Practice File-Tree-Walk from APUE Figure 4.22
 *
 * Implementing a File-Tree-Walk on a Unix system. The main() function
 * calls the walker fwt() passing it the pathname of the initial point
 * and the user-defined callback function. The purpose of the walker
 * is to dynamically allocate a buffer for a fullpath based on
 * system-defined sizes unknown at compile time, make sure the
 * argument pathname fits in and then call the recursing function
 * (passing it the callback function) in a global scope provided with
 * a fullpath-buffer (resizeable as needed) and its capacity. In turn,
 * the recursing function will stat() each path, and conditionally
 * invoke the callback function on the basis of either the type of the
 * stat() output, or the type of the pathname, or the output of the
 * callback function. The callback function has a strict contract:
 * either return null to authorize a recursive file-tree-walk or
 * anything other to terminate the walk. On the other hand the
 * recursing function can delegate some error handling to the callback
 * function and makes sure any value return by the callback is
 * funneled up the call stack to the main() function for final
 * interpretation before exit. At the end the main() function uses all
 * global variables updated by the callback function to display the
 * final report.
 * ========================================================================= */
#include "apue.h"
#include <dirent.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

typedef int Worker_f(const char *, const struct stat *, int);

static int myftw(const char *pathname, Worker_f *callback);
static int ftw_recurser(Worker_f *callback);
static Worker_f worker;

static long nreg, ndir, nblk, nchr, nlnk, nfif, nsok, ntot;

int main(int argc, char *argv[argc + 1]) {
  if (argc != 2) /* Validate command line argument */
    err_quit("Usage: %s <initial_pathname>", argv[0]);
  /* Start the walk */
  int ret = myftw(argv[1], worker);
  /* Optionally interpret the ret value before incidentally reassigning. */
  /* Keep talling */
  ntot = nreg + ndir + nblk + nchr + nlnk + nfif + nsok;
  if (ntot == 0)
    ntot = 1; /* Gard against dividing by zero and keeps all counts null. */
  /* Display report */
  printf("regular files   = %7ld → %5.2f %%\n", nreg, nreg * 100.0 / ntot);
  printf("directories     = %7ld → %5.2f %%\n", ndir, ndir * 100.0 / ntot);
  printf("block files     = %7ld → %5.2f %%\n", nblk, nblk * 100.0 / ntot);
  printf("character files = %7ld → %5.2f %%\n", nchr, nchr * 100.0 / ntot);
  printf("symbolic links  = %7ld → %5.2f %%\n", nlnk, nlnk * 100.0 / ntot);
  printf("pipes or FIFOs  = %7ld → %5.2f %%\n", nfif, nfif * 100.0 / ntot);
  printf("sockets         = %7ld → %5.2f %%\n", nsok, nsok * 100.0 / ntot);

  exit(ret);
}

static char *pathbuf;
static size_t pathbuf_size;

int myftw(const char *pathname, Worker_f *callback) {
  char *tmp = NULL;
  int ret = 0;

  pathbuf = path_alloc(&pathbuf_size);

  if (pathbuf_size <= strlen(pathname)) {
    pathbuf_size = 2 * strlen(pathname);
    tmp = realloc(pathbuf, sizeof(char) * pathbuf_size);
    if (tmp == NULL) {
      free(pathbuf);
      err_sys("realloc() failed on '%s'", pathname);
    }
    pathbuf = tmp;
  }
  strcpy(pathbuf, pathname);

  ret = ftw_recurser(callback);
  free(pathbuf);
  pathbuf = NULL;
  return ret;
}

#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_NS 4

#define NAME_MAX 255

int ftw_recurser(Worker_f *callback) {
  int ret = 0;
  struct stat statbuf;
  DIR *dirp;
  struct dirent *dent;
  size_t currpath_len = 0;
  char *tmp = NULL;

  /* WARN: lstat() symbolic links, don't follow them with stat() */
  if (lstat(pathbuf, &statbuf) == -1)
    return callback(pathbuf, &statbuf, FTW_NS);
  if (S_ISDIR(statbuf.st_mode) == 0)
    return callback(pathbuf, &statbuf, FTW_F);

  if ((ret = callback(pathbuf, &statbuf, FTW_D)) != 0)
    return ret;

  currpath_len = strlen(pathbuf);
  while (pathbuf_size <= (currpath_len + NAME_MAX + 2)) {
    pathbuf_size *= 2;
    tmp = realloc(pathbuf, sizeof(char) * pathbuf_size);
    if (tmp == NULL) {
      free(pathbuf);
      err_sys("realloc() failed on '%s'", pathbuf);
    }
    pathbuf = tmp;
  }
  pathbuf[currpath_len] = '/';
  pathbuf[currpath_len + 1] = '\0';

  if ((dirp = opendir(pathbuf)) == NULL)
    return callback(pathbuf, &statbuf, FTW_DNR);

  errno = 0;
  while ((dent = readdir(dirp)) != NULL) {
    if (!strcmp(dent->d_name, ".") || !strcmp(dent->d_name, ".."))
      continue;
    /* Now we have a supported dir-entry fullpath must be amended */
    strcpy((pathbuf + currpath_len + 1), dent->d_name);
    /* Start recursive invocations funneling up all returned values */
    if ((ret = ftw_recurser(callback)) != 0)
      break;
  }
  if (errno != 0)
    err_ret("readdir() failed on directory '%s'", pathbuf);

  /* Restore the fullpath to parent directory from before readdir() */
  pathbuf[currpath_len] = '\0';
  /* Close the directory entry */
  if (closedir(dirp) == -1)
    err_ret("closedir() failed on '%s'", pathbuf);

  return ret;
}

int worker(const char *pathname, const struct stat *statbuf, int pathtype) {
  switch (pathtype) {
  case FTW_F: /* file-tree-walk met a File (any other than directory) */
    switch (statbuf->st_mode & S_IFMT) {
      /* clang-format off */
    case S_IFREG:  nreg++; break;
    case S_IFBLK:  nblk++; break;
    case S_IFCHR:  nchr++; break;
    case S_IFIFO:  nfif++; break;
    case S_IFLNK:  nlnk++; break;
    case S_IFSOCK: nsok++; break;
    case S_IFDIR:  err_dump("Hit S_IFDIR: directory path must be FTW_D");
      /* clang-format on */
    }
    break;

  case FTW_D: /* file-tree-walk met a Directory */
    ndir++;
    break;

  case FTW_DNR: /* file-tree-walk met a Directory Not Readable */
    err_ret("cannot read directory '%s'", pathname);
    break;

  case FTW_NS: /* file-tree-walk could Not Stat */
    err_ret("stat() failed on '%s'", pathname);
    break;

  default:
    err_dump("unknown pathtype '%d' on '%s'", pathtype, pathname);
  }

  return 0;
}
