/* Figure 1.3: List all the files (i.e., directory entries) in a directory. */

#include "../include/apue.h"
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
