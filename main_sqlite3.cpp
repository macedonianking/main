#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "main_sqlite3.h"
#include "main_utils.h"
#include "main_string_builder.h"

#define NAME_SQLITE3_DB				"test.db"
#define SQLTIE3_DB_VERSION 			1

static void main_sqlite3_test_open();
static void main_sqlite3_test_close();
static int 	main_sqlite3_test_open_callback(void *data, int argc, char **argv, char **names);
static int 	main_sqlite3_get_database_version(sqlite3 *db);
static void main_sqlite3_set_database_version(sqlite3 *db, int new_version);
static int 	main_sqlite3_common_callback(void *data, int argc, char **argv, char **names);

static void main_sqlite3_open_helper_on_create(struct main_sqlite3_open_helper *helper, sqlite3 *db);
static void main_sqlite3_open_helper_on_upgrade(struct main_sqlite3_open_helper *helper, sqlite3 *db, int old_verson, int new_version);
static void main_sqlite3_open_helper_on_downgrade(struct main_sqlite3_open_helper *helper, sqlite3 *db,int old_verson, int new_version);

static main_sqlite3_open_helper *gHelper = NULL;

void main_sqlite3_test()
{
	main_sqlite3_enter();
	main_sqlite3_leave();
}

void main_sqlite3_enter()
{
	main_sqlite3_test_open();
}

void main_sqlite3_leave()
{
	main_sqlite3_test_close();
}

void main_sqlite3_test_open()
{
	if (gHelper)
	{
		return;
	}

	gHelper = (struct main_sqlite3_open_helper *) malloc(sizeof(struct main_sqlite3_open_helper));
	memset(gHelper, 0, sizeof(*gHelper));
	gHelper->name = NAME_SQLITE3_DB;
	gHelper->version = SQLTIE3_DB_VERSION;
	gHelper->on_create = main_sqlite3_open_helper_on_create;
	gHelper->on_upgrade = main_sqlite3_open_helper_on_upgrade;
	gHelper->on_downgrade = main_sqlite3_open_helper_on_downgrade;
	main_sqlite3_open(gHelper);
}

void main_sqlite3_test_close()
{
	if (!gHelper)
	{
		return;
	}

	sqlite3_close(gHelper->db);
	gHelper->db = NULL;
	free(gHelper);
	gHelper = NULL;
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

void main_sqlite3_set_database_version(sqlite3 *db, int new_version)
{
	char buffer[1024];
	int rc;
	char *zErrMsg;

	snprintf(buffer, 1024, "PRAGMA user_version=%d;", new_version);
	rc = sqlite3_exec(db, buffer, NULL, NULL, &zErrMsg);
	if (SQLITE_OK != rc)
	{
		fprintf(stderr, "main_sqlite3_set_database_version failure:%s\n", zErrMsg);
	}
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

int main_sqlite3_open(struct main_sqlite3_open_helper *helper)
{
	sqlite3 *db;
	int rc;
	int user_version;

	rc = sqlite3_open_v2(helper->name, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
	if (rc != SQLITE_OK)
	{
		fprintf(stdout, "sqlite3_open_v2 faiure\n");
		return -1;
	}

	user_version = main_sqlite3_get_database_version(db);
	if (user_version == -1)
	{
		fprintf(stdout, "main_sqlite3_get_database_version\n");
		goto FAILURE;
	}

	if (user_version != helper->version) {
		if (user_version == 0)
		{
			helper->on_create(helper, db);
		}
		else if (user_version < helper->version)
		{
			helper->on_upgrade(helper, db, user_version, helper->version);
		}
		else
		{
			helper->on_downgrade(helper, db, user_version, helper->version);
		}
		main_sqlite3_set_database_version(db, helper->version);
	}


	helper->db = db;
	return 0;

FAILURE:
	sqlite3_close(db);
	return -1;
}

void main_sqlite3_open_helper_on_create(struct main_sqlite3_open_helper *helper, sqlite3 *db)
{
	struct main_string_builder *builder;
	int rc;
	char *zErrMsg;
	char *text;

	builder = NULL;
	main_string_builder_acquire(1024, &builder);
	main_string_builder_append_text(builder, "CREATE TABLE tbl_user(");
	main_string_builder_append_text(builder, "_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT");
	main_string_builder_append_text(builder, ",name VARCHAR(256) NOT NULL");
	main_string_builder_append_text(builder, ",email VARCHAR(256)");
	main_string_builder_append_text(builder, ",birthday INTEGER DEFAULT 0);");
	text = main_string_builder_data(builder);
	rc = sqlite3_exec(db, text, NULL, NULL, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "main_sqlite3_open_helper_on_create failure\n");
		goto ON_ERROR;
	}

	main_string_builder_release(builder);
	builder = NULL;

	helper->on_upgrade(helper, db, 1, helper->version);
	return;

ON_ERROR:
	if (builder != NULL) {
		main_string_builder_release(builder);
		builder = NULL;
	}
	return;
}

static void main_sqlite3_handle_upgrade_impl(sqlite3 *db, int version)
{

}

void main_sqlite3_open_helper_on_upgrade(struct main_sqlite3_open_helper *helper, 
										 sqlite3 *db, int old_verson, int new_version)
{
	int version;

	version = old_verson + 1;
	while (version <= new_version) {
		main_sqlite3_handle_upgrade_impl(db, version);
		++version;
	}
}

void main_sqlite3_open_helper_on_downgrade(	struct main_sqlite3_open_helper *helper,
											sqlite3 *db, int old_verson, int new_version)
{
	sqlite3_exec(db, "DROP TABLE IF EXISTS tbl_user;", NULL, NULL, NULL);
	helper->on_create(helper, db);
}