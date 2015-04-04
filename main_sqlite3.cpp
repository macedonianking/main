#include <stdio.h>
#include <stdlib.h>

#include "main_sqlite3.h"

#define NAME_SQLITE3_DB	"test.db"

static void main_sqlite3_test_open(const char *dbName);
static int main_sqlite3_test_open_callback(void *data, int argc, char **argv, char **names);

struct main_sqlite3_open_data
{
	int		hasPrintHeader;
	int		row;
};

void main_sqlite3_test()
{
	main_sqlite3_test_open(NAME_SQLITE3_DB);
}

void main_sqlite3_test_open(const char *name)
{
	sqlite3 *db;
	int rc;
	char *zErrMsg;
	struct main_sqlite3_open_data data;

	db = NULL;
	if (rc = sqlite3_open_v2(name, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL))
	{
		fprintf(stdout, "open database failure: %s reason=%s\n", name, sqlite3_errmsg(db));
		goto FINISH;
	}

	data.hasPrintHeader = 0;
	data.row = 0;

	rc = sqlite3_exec(db, "SELECT * FROM tbl_users", main_sqlite3_test_open_callback, (void*) &data,  &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error:%s\n", zErrMsg);
		goto FINISH;
	}

FINISH:
	sqlite3_close(db);
	db = NULL;
}

int main_sqlite3_test_open_callback(void *data, int argc, char **argv, char **names)
{
	struct main_sqlite3_open_data *ptr;
	int i;

	ptr = (struct main_sqlite3_open_data*) data;
	if (!ptr->hasPrintHeader)
	{
		ptr->hasPrintHeader = 1;
		for (i = 0; i < argc; ++i)
		{
			if(i != 0)
			{
				fprintf(stdout, "\t");
			}
			fprintf(stdout, "%s", names[i]);
		}
		fprintf(stdout, "\n");
	}

	for (i = 0; i < argc; ++i)
	{
		if (i != 0)
		{
			fprintf(stdout, "\t");
		}
		fprintf(stdout, "%s", argv[i] ? argv[i] : "NULL");
	}
	++ptr->row;

	return 0;
}