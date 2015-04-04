#include <stdio.h>
#include <stdlib.h>

#include "main_sqlite3.h"

#define NAME_SQLITE3_DB	"test.db"

static void main_sqlite3_test_open(const char *dbName);

void main_sqlite3_test()
{
	main_sqlite3_test_open(NAME_SQLITE3_DB);
}

void main_sqlite3_test_open(const char *name)
{
	sqlite3 *db;
	int rc;

	db = NULL;
	if (rc = sqlite3_open(name, &db))
	{
		fprintf(stdout, "open database failure: %s reason=%s\n", name, sqlite3_errmsg(db));
		if (db != NULL) {
			sqlite3_close(db);
			db = NULL;
		}
		return;
	}

	sqlite3_close(db);
	db = NULL;
}