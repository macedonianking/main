#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "main_sqlite3.h"
#include "main_utils.h"

#define NAME_SQLITE3_DB	"test.db"


static void main_sqlite3_test_open(const char *dbName);
static int 	main_sqlite3_test_open_callback(void *data, int argc, char **argv, char **names);
static int 	main_sqlite3_get_database_version(sqlite3 *db);
static int 	main_sqlite3_common_callback(void *data, int argc, char **argv, char **names);

void main_sqlite3_test()
{
	main_sqlite3_test_open(NAME_SQLITE3_DB);
}

void main_sqlite3_test_open(const char *name)
{
	sqlite3 *db;
	int rc;
	char *zErrMsg;
	int user_version;
	struct main_sqlite3_open_data data;

	db = NULL;
	if (rc = sqlite3_open_v2(name, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL))
	{
		fprintf(stdout, "open database failure: %s reason=%s\n", name, sqlite3_errmsg(db));
		goto FINISH;
	}

	user_version = main_sqlite3_get_database_version(db);
	if (user_version == -1)
	{
		fprintf(stderr, "main_sqlite3_get_database_version failure\n");
		goto FINISH;
	}

	data.hasPrintHeader = 0;
	data.row = 0;

	rc = sqlite3_exec(db, "PRAGMA user_version;", main_sqlite3_test_open_callback, (void*) &data,  &zErrMsg);
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

int main_sqlite3_get_database_version(sqlite3 *db)
{
	struct main_sqlite3_common_data data;
	int rc;
	char *zErrMsg;

	memset(&data, 0, sizeof(data));
	data.name = "user_version";
	data.type = TYPE_INT;

	rc = sqlite3_exec(db, "PRAGMA user_version;", main_sqlite3_common_callback, (void*) &data, &zErrMsg);
	if (SQLITE_OK != rc)
	{
		fprintf(stderr, "sqlite3_exec failure:%s\n", zErrMsg);
		return -1;
	}
	return data.m_i;
}

int main_sqlite3_common_callback(void *data, int argc, char **argv, char **names)
{
	struct main_sqlite3_common_data *ptr;
	int i;
	int index;
	int n;
	int r;

	ptr = (struct main_sqlite3_common_data*) data;
	if (ptr == NULL || ptr->name == NULL)
	{
		return 1;
	}

	index = -1;
	for (i = 0; i < argc; ++i)
	{
		if (strcmp(names[i], ptr->name) == 0)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		return 1;
	}

	r = 0;
	switch(ptr->type)
	{
		case TYPE_CHAR: {
			ptr->m_c = argv[index][0];
			break;
		}
		case TYPE_SHORT: {
			ptr->m_s = (short) atoi(argv[index]);
			break;
		}
		case TYPE_INT: {
			ptr->m_i = (int) atoi(argv[index]);
			break;
		}
		case TYPE_LONG: {
			ptr->m_l = (long) atol(argv[index]);
			break;
		}
		case TYPE_FLOAT: {
			ptr->m_f = (float) atof(argv[index]);
			break;
		}
		case TYPE_DOUBLE: {
			ptr->m_d = (double) atof(argv[index]);
			break;
		}
		case TYPE_TEXT: {
			n = strlen(argv[index]) + 1;
			ptr->m_t = (char *) malloc(sizeof(char) * n);
			if (ptr->m_t != NULL) {
				strcpy(ptr->m_t, argv[index]);
			}
			break;
		}
		default:
		{
			r = 1;
			break;
		}
	}
	return r;
}