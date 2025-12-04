/* apue.3e/fileio/tracefd.c */
/* Create on: Wed Dec  3 04:23:17 +01 2025 */
/* Description: Trace open file descriptors */
/* NOTE: Internally opendir will run:
 * fd = open( "/proc/self/fd", O_RDONLY | O_DIRECTORY);
 * that fd will become the first free (most likely 3) file descriptor.
 * fd 0, 1, 2 often refer to the same terminal, so all point to /dev/pts/N.
 * The filename /dev/pts/N has nothing to do with "fd 0".
 * FDs do not store filenames; they store references to open file objects.
 * Several FDs can point to the same open file object. */

#include "../include/apue.h"
#include <dirent.h>
#include <unistd.h>

int main(int argc, char *argv[argc + 1]) {
  /* const char *dirpath = "/dev/fd"; */
  const char *dirpath = "/proc/self/fd";

  DIR *dirp = opendir(dirpath);
  if (dirp == NULL)
    err_sys("opendir error");

  struct dirent *entry;
  char linkpath[256];
  char target[256];
  ssize_t len;

  printf("Open file descriptors for PID %d:\n", getpid());

  while ((entry = readdir(dirp)) != NULL) {
    if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
      continue;
    snprintf(linkpath, sizeof(linkpath), "%s/%s", dirpath, entry->d_name);
    len = readlink(linkpath, target, sizeof(target) - 1);
    if (len == -1)
      err_sys("readlink error");
    target[len] = '\0';
    printf("\tfd %-3s → %s\n", entry->d_name, target);
  }

  closedir(dirp);
  return EXIT_SUCCESS;
}
