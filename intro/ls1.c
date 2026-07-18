/* =========================================================================
 * Created on: <Fri Jul 17 14:16:11 +01 2026>
 * Time-stamp: <Fri Jul 17 14:22:20 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/intro/ls1.c -
 *
 * Figure 1.3: List all the files (i.e., directory entries) in a directory.
 * ========================================================================= */
#include "apue.h"
#include <dirent.h>

int main(int argc, char *argv[]) {
  DIR *dirp;
  struct dirent *dent;

  if (argc != 2)
    err_quit("usage: ls directory_name");

  if ((dirp = opendir(argv[1])) == NULL)
    err_sys("can't open %s", argv[1]);

  while ((dent = readdir(dirp)) != NULL)
    printf("%s\n", dent->d_name);

  closedir(dirp);
  exit(0);
}
