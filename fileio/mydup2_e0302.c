/* apue.3e/fileio/mydup2_e0302.c */
/* apue.3e/fileio/mydp2.c */
/* Created on: Wed Dec  3 05:45:11 +01 2025 */
/* Exercise 3.2: Write your own dup2 function that behaves the same way as the
 * dup2 function described in Section 3.12, without calling the fcntl function.
 * Be sure to handle errors correctly. */

#include "../include/apue.h"
#include <errno.h>
#define MAX_TEMP_FDS 1024

int my_dup2(int oldfd, int newfd) {
  int current_fd, i, count = 0;
  int temp_fds[MAX_TEMP_FDS];
  int output;

  /* (1) Make sure oldfd is a valid file descriptor */
  if ((current_fd = dup(oldfd)) == -1)
    return -1;
  else /* Since oldfd is valid close its duplicate */
    close(current_fd);

  /* (2) Check if oldfd and newfd are the same file descriptor */
  if (oldfd == newfd)
    return newfd;

  /* (3) Close the newfd in case it happens to be open (POSIX requirement).
   * Failing to do this will prevent oldfd from ever getting its newfd since
   * during its fd selection process from the smallest free, dup() skips open
   * ones outright. */
  close(newfd);

  /* (4) Loop until dup() returns newfd while storing useless valid fds to
   * cleanup */
  for (;;) {
    if ((current_fd = dup(oldfd)) == -1) /* errno is set by dup() */ {
      output = -1; /* Failure */
      break;
    }

    if (current_fd == newfd) /* dup() output matches target fd */ {
      output = newfd; /* Success */
      break;
    }

    /* dup() output is valid fd but doesn't match the target fd. Store
     * intermediate fds (for later cleanup) up until an artificial limit */
    if (count >= MAX_TEMP_FDS) {
      close(current_fd);
      errno = EMFILE;
      output = -1; /* Failure */
      break;
    }

    temp_fds[count++] = current_fd;
  }

  for (i = 0; i < count; i++) {
    close(temp_fds[i]);
  }

  return output;
}

/* Test driver */
void run_test(const char *title, int expected, int actual, int expected_errno) {
  printf("--- %s ---\n", title);
  if (expected == actual) {
    printf("RESULT: PASS. Returned fd: %d\n", actual);
  } else {
    printf("RESULT: FAIL. Expected fd: %d, ACTUAL fd: %d\n", expected, actual);
    if (actual == -1)
      printf("\tError: %s (Expected errno: %d)\n", strerror(errno),
             expected_errno);
  }
}

int main(int argc, char *argv[]) {
  int fd_source, fd_target, fd_result;
  char buf[256];
  const char *test_file = "test_mydup2.txt";

  FILE *fp = fopen(test_file, "w+");
  if (fp == NULL)
    err_sys("fopen error");

  /* Get fd out of FILE struct */
  fd_source = fileno(fp);
  printf("Source fd (oldfd) is: %d\n", fd_source);
  /* Write to stream and reset offset */
  char *msg = "Hello mydup2!";
  fwrite(msg, sizeof(char), strlen(msg), fp);
  fseek(fp, 0, SEEK_SET);

  /* --- TEST 1: Simple dup (target is 10) --- */
  fd_target = 10;
  fd_result = my_dup2(fd_source, fd_target);
  run_test("TEST 1: Dup to unused fd 10 (Requires 7 dups)", fd_target,
           fd_result, 0);
  if (fd_result != -1) {
    /* Verify the content */
    ssize_t bytes_read = read(fd_target, buf, strlen(msg));
    buf[bytes_read] = '\0';
    printf("  Verification: Read '%s' from fd %d\n", buf, fd_target);
    close(fd_result); /* Close the new descriptor */
  }

  /* --- TEST 2: Invalid oldfd --- */
  fd_result = my_dup2(-5, 50);
  run_test("TEST 2: Invalid oldfd", -1, fd_result, EBADF);

  /* --- TEST 3: oldfd == newfd --- */
  fd_target = fd_source;
  fd_result = my_dup2(fd_source, fd_target);
  run_test("TEST 3: oldfd == newfd", fd_source, fd_result, 0);

  /* Cleanup: close the original file stream and delete disk-file */
  fclose(fp);
  unlink(test_file);

  /* code */
  return EXIT_SUCCESS;
}
