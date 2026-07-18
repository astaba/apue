/* =========================================================================
 * Created on: <Fri Jul 17 15:38:31 +01 2026>
 * Time-stamp: <Fri Jul 17 15:39:09 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/ipc2/opend/opend.h -
 *
 * Figure 17.26 The opend.h header, version 2
 * ========================================================================= */
#include "apue.h"
#include <errno.h>

#define CS_OPEN "/tmp/opend.socket" /* well-known name */
#define CL_OPEN "open"              /* client's request for server */

extern int debug;      /* nonzero if interactive (not daemon) */
extern char errmsg[];  /* error message string to return to client */
extern int oflag;      /* open flag: O_xxx ... */
extern char *pathname; /* of file to open for client */

typedef struct { /* one Client struct per connected client */
  int fd;        /* fd, or -1 if available */
  uid_t uid;
} Client;

extern Client *client;  /* ptr to malloc'ed array */
extern int client_size; /* # entries in client[] array */

int cli_args(int, char **);
int client_add(int, uid_t);
void client_del(int);
void loop(void);
void handle_request(char *, int, int, uid_t);
