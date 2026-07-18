/* =========================================================================
 * Created on: <Fri Jul 17 14:53:15 +01 2026>
 * Time-stamp: <Fri Jul 17 14:53:55 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc2/sendmsg.c -
 *
 * Figure 17.4 Post a message to an XSI message queue
 * ========================================================================= */
#include "apue.h"
#include <sys/msg.h>

#define MAXMSZ 512

struct mymesg {
  long mtype;
  char mtext[MAXMSZ];
};

int main(int argc, char *argv[]) {
  key_t key;
  long qid;
  size_t nbytes;
  struct mymesg m;

  if (argc != 3) {
    fprintf(stderr, "usage: sendmsg KEY message\n");
    exit(1);
  }
  key = strtol(argv[1], NULL, 0);
  if ((qid = msgget(key, 0)) < 0)
    err_sys("can't open queue key %s", argv[1]);
  memset(&m, 0, sizeof(m));
  strncpy(m.mtext, argv[2], MAXMSZ - 1);
  nbytes = strlen(m.mtext);
  m.mtype = 1;
  if (msgsnd(qid, &m, nbytes, 0) < 0)
    err_sys("can't send message");
  exit(0);
}
