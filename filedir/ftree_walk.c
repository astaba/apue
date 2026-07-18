/* =========================================================================
 * Created on: <Fri Jun 19 12:12:07 +01 2026>
 * Time-stamp: <Fri Jun 19 18:44:20 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/filedir/ftree_walk.c -
 *
 * Figure 4.22 Recursively descend a directory hierarchy, counting
 * file types.
 *
 * @brief Overview of the ftw-style callback-driven traversal framework.
 * This program implements a classic UNIX directory traversal pattern:
 *
 * - The walker (`myftw()` + `dopath()`) navigates the filesystem.
 * - The user-supplied callback (`Myfunc`) specifies what to *do* for each node.
 *
 * This separation gives rise to a small but powerful programming paradigm:
 *    traversal engine  = “how” to visit objects
 *    callback          = “what to do” with each object
 *
 * Benefits:
 *    • Reusable traversal logic
 *    • Declarative, high-level callback logic
 *    • Fast in-place path construction (via mutable global buffer)
 *    • Clean early termination via callback return values
 *
 * Many UNIX tools (e.g., `find`, `du`, `tar`) and APIs (`ftw()`, `nftw()`)
 * are built on this paradigm.
 * ========================================================================= */
#include "apue.h"
#include <dirent.h>
#include <limits.h>
#include <stdlib.h>

/**
 * @brief User-defined callback invoked for every filesystem object visited.
 * This function type defines the customizable "policy" executed by the file
 * tree walker. For each encountered file, directory, or special object,
 * the walker invokes a function of this type, passing the current pathname,
 * corresponding stat information, and a type code describing the object.
 *
 * @param `pathname` The full path (absolute or relative) to the current object.
 * Valid only during the callback; it must not be stored for later use.
 *
 * @param `statptr` Pointer to `struct stat` obtained from `lstat()`. Undefined
 * if `type` equals `FTW_NS` (stat failed).
 *
 * @param `type` One of:
 * - `FTW_F`   : Non-directory file (regular, symlink, block, etc.)
 * - `FTW_D`   : Directory
 * - `FTW_DNR` : Directory exists but cannot be opened
 * - `FTW_NS`  : Stat information unavailable (`lstat` failed)
 *
 * @return `int` 0 to continue traversal. Any non-zero value signals the walker
 * to abort immediately. The returned value is propagated back up the recursion
 * stack.
 */
typedef int Myfunc(const char *, const struct stat *, int);

static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);
static Myfunc myfunc;
static Myfunc user_stop_func; /* Optional alternative to myfunc */

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[]) {
  int ret;

  if (argc != 2)
    err_quit("usage:  ftw  <starting-pathname>");

  ret = myftw(argv[1], myfunc); /* does it all */
  /*
   * Here you could print a message based on ret interpretation, then reassign
   * (or not) ret to a system-explicit value to return. The alternative callback
   * user_stop_func() perfectly fits that use case.
   */

  ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
  if (ntot == 0)
    ntot = 1; /* avoid divide by 0; print 0 for all counts */
  printf("regular files  = %7ld, %5.2f %%\n", nreg, nreg * 100.0 / ntot);
  printf("directories    = %7ld, %5.2f %%\n", ndir, ndir * 100.0 / ntot);
  printf("block special  = %7ld, %5.2f %%\n", nblk, nblk * 100.0 / ntot);
  printf("char special   = %7ld, %5.2f %%\n", nchr, nchr * 100.0 / ntot);
  printf("FIFOs          = %7ld, %5.2f %%\n", nfifo, nfifo * 100.0 / ntot);
  printf("symbolic links = %7ld, %5.2f %%\n", nslink, nslink * 100.0 / ntot);
  printf("sockets        = %7ld, %5.2f %%\n", nsock, nsock * 100.0 / ntot);
  exit(ret);
}

/*
 * Descend through the hierarchy, starting at "pathname".
 * The caller's func() is called for every file.
 */
#define FTW_F 1   /* file-tree-walk met a File (any other than directory) */
#define FTW_D 2   /* file-tree-walk met a Directory */
#define FTW_DNR 3 /* file-tree-walk met a Directory Not Readable */
#define FTW_NS 4  /* file-tree-walk could Not Stat */                        

static char *fullpath; /* contains full pathname for every file */
static size_t pathlen;

/**
 * @brief Entry point for the file tree walker.
 * This is the walker-frontend and its purpose is (1) to layout the walking
 * start point (user provided pathname) in a wide enough buffer and (2) initiate
 * the walker-backend. At the beginning pathname's buffer is allocated
 * dynamically by path_alloc() based on system- and POSIX-compliant variables
 * unknown at compile time. On success, path_alloc() returns the dynamic buffer
 * address and its size from the output parameter. Then we must confirm this
 * buffer's size is wide enough to hold the pathname. On failure, dynamic buffer
 * is reallocated with 2 times the size of pathname. Now that the buffer is
 * definitely big enough too hold the pathname, strcpy() is called to lay it out
 * in the buffer. When myftw() returns the walker-backend, dopath() has in the
 * global scope the starting-pathname secured in a causy buffer resizeable as
 * needed.
 *
 * @param `pathname` The starting directory or file name from which recursive
 * traversal begins.
 *
 * @param `func` The user-supplied callback of type `Myfunc`, executed for every
 * object processed by the walker.
 *
 * @return `int` Returns whatever value the callback ultimately returns. A
 * return of zero indicates that the entire tree was processed without early
 * termination.
 *
 * @throws Terminates the program via `err_sys()` if memory allocation or
 * reallocation fails.
 */
static int myftw(char *pathname, Myfunc *func) {
  fullpath = path_alloc(&pathlen); /* malloc PATH_MAX+1 bytes */
                                   /* ({Prog pathalloc}) */
  if (pathlen <= strlen(pathname)) {
    pathlen = strlen(pathname) * 2;
    if ((fullpath = realloc(fullpath, pathlen)) == NULL)
      err_sys("realloc failed");
  }
  strcpy(fullpath, pathname);

  /* Stevens's NOTE: "Most of the example programs terminate shortly
   * after use; memory cleanup is omitted for clarity."
   * 
   * That is why the following cleanup and graceful exit is omitted:
   *
   * int ret = (dopath(func));
   * free(fullpath);
   * fullpath = NULL;
   * return ret;
   *
   * */

  return (dopath(func));
}

/**
 * @brief Core recursive directory-walking engine.
 * This function performs the actual depth-first traversal of the filesystem.
 * It operates on the global mutable buffer `fullpath`, which always holds the
 * path of the currently visited filesystem object. This buffer is modified
 * in-place to construct child paths during recursion and restored after each
 * recursive call.
 *
 * Traversal behavior:
 *   1. Performs `lstat()` on the current path.
 *   2. If the object is not a directory:
 *        - Invokes the callback with type = `FTW_F.`
 *        - Returns its result.
 *   3. If the object is a directory:
 *        - Invokes the callback with type = `FTW_D.`
 *        - Aborts traversal if the callback returns non-zero.
 *        - Opens the directory and recursively processes each entry.
 *
 * Buffer behavior:
 *   - `fullpath` is mutated by appending "/", then each child entry name.
 *   - After each recursion, the buffer is restored to its previous state.
 *   - If the buffer is too small for deeper paths, it is reallocated.
 *
 * @param `func` The user-defined callback invoked for every visited object.
 *
 * @return `int` Returns 0 on successful traversal of this subtree. Returns
 * non-zero if the callback requests early termination.
 *
 * @throws Terminates the program via `err_sys()` if pathname buffer
 * reallocation fails. Emits warnings with `err_ret()` if directory closing
 * fails.
 *
 * @note Early termination justification.
 * The walker must always test the callback’s return value. A non-zero return
 * signals that the user explicitly requests traversal to stop. This pattern is
 * fundamental to ftw-style traversal and is enforeced by the NULL- or
 * non-zero-return checks in some if-clauses of the dopath() walker-backend.
 *
 * @example Custom early-stop callback.
 * The user_stop_func() example shows how a user-defined callback can end the
 * walk as soon as a specific file is encountered. This demonstrates why the
 * walker must check for non-zero returns.
 */
static int dopath(Myfunc *func) {
  struct stat statbuf;
  struct dirent *dent;
  DIR *dp;
  int ret, n;

  if (lstat(fullpath, &statbuf) < 0) /* stat error */
    return (func(fullpath, &statbuf, FTW_NS));
  if (S_ISDIR(statbuf.st_mode) == 0) /* not a directory */
    return (func(fullpath, &statbuf, FTW_F));

  /*
   * It's a directory.  First call func() for the directory,
   * then process each filename in the directory.
   */
  if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
    return (ret);

  n = strlen(fullpath);
  if (n + NAME_MAX + 2 > pathlen) { /* expand path buffer */
    pathlen *= 2;
    if ((fullpath = realloc(fullpath, pathlen)) == NULL)
      err_sys("realloc failed");
  }
  /* Turn fullpath into a:  */
  fullpath[n++] = '/'; /* directory path (foreslash-terminated)  */
  fullpath[n] = 0;     /* C-conform string (null-terminated) */

  if ((dp = opendir(fullpath)) == NULL) /* can't read directory */
    return (func(fullpath, &statbuf, FTW_DNR));

  while ((dent = readdir(dp)) != NULL) {
    if (strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0)
      continue;                         /* ignore dot and dot-dot */
    strcpy(&fullpath[n], dent->d_name); /* append name after "/" */
    if ((ret = dopath(func)) != 0)      /* recursive */
      break;                            /* time to leave */
  }
  fullpath[n - 1] = 0; /* erase everything from slash onward */

  if (closedir(dp) < 0)
    err_ret("can't close directory %s", fullpath);
  return (ret);
}

/**
 * @brief Example callback used for counting filesystem object types.
 * This function demonstrates how a user-supplied callback can interpret
 * the traversal metadata. It increments global counters based on object
 * classification, and prints diagnostic messages for unreadable or unstatable
 * entries.
 *
 * @param `pathname` The path to the current filesystem object.
 *
 * @param `statptr` Pointer to stat information for the object, provided by
 * `lstat()`.
 *
 * @param `type` Indicator of object type (`FTW_F`, `FTW_D`, `FTW_DNR`,
 * `FTW_NS`).
 *
 * @return `int` Always returns 0, meaning traversal continues uninterrupted.
 */
static int myfunc(const char *pathname, const struct stat *statptr, int type) {
  switch (type) {
  case FTW_F:
    switch (statptr->st_mode & S_IFMT) {
    case S_IFREG:
      nreg++;
      break;
    case S_IFBLK:
      nblk++;
      break;
    case S_IFCHR:
      nchr++;
      break;
    case S_IFIFO:
      nfifo++;
      break;
    case S_IFLNK:
      nslink++;
      break;
    case S_IFSOCK:
      nsock++;
      break;
    case S_IFDIR: /* directories should have type = FTW_D */
      err_dump("for S_IFDIR for %s", pathname);
    }
    break;
  case FTW_D:
    ndir++;
    break;
  case FTW_DNR:
    err_ret("can't read directory %s", pathname);
    break;
  case FTW_NS:
    err_ret("stat error for %s", pathname);
    break;
  default:
    err_dump("unknown type %d for pathname %s", type, pathname);
  }
  return (0);
}

/*
 * Alternative callback function to showcase terminating behavior of the
 * `dopath()` walker-backend. It make `dopath()` to stop walking when
 * "target_file" is found. If 'user_stop_func' returns 1, the walker detects it
 * and halts.
 */
static int user_stop_func(const char *pathname, const struct stat *statptr,
                          int type) {
  if (strcmp(pathname, "/path/to/target_file") == 0) {
    printf("Found target. Stopping walk.\n");
    return 1; /*  Non-zero → immediately abort traversal */
  }
  return 0; /* Zero → continue traversal */
}
