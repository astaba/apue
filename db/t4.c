/* =========================================================================
 * Created on: <Thu Jul 16 00:26:08 +01 2026>
 * Time-stamp: <Thu Jul 16 00:26:50 +01 2026 by owner>
 * Author    : W. Richard Stevens and Stephen A. Rago from
 *             "Advanced Programming in the UNIX® Environment" Third Edition
 * Desc      : ~/coding/c_prog/apue.3e/db/t4.c -
 *
 * Figure 20.3: Create a database and write three records to it
 * ========================================================================= */
#include "apue.h"
#include "apue_db.h"
#include <fcntl.h>

int main(void) {
  DBHANDLE db;

  if ((db = db_open("db4", O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) == NULL)
    err_sys("db_open error");

  if (db_store(db, "Alpha", "data1", DB_INSERT) != 0)
    err_quit("db_store error for alpha");
  if (db_store(db, "beta", "Data for beta", DB_INSERT) != 0)
    err_quit("db_store error for beta");
  if (db_store(db, "gamma", "record3", DB_INSERT) != 0)
    err_quit("db_store error for gamma");

  db_close(db);
  exit(0);
}
