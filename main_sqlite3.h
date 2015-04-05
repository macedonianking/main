#ifndef MAIN_SQLITE_H
#define MAIN_SQLITE_H

#include "sqlite3.h"

struct main_sqlite3_open_data
{
	int		hasPrintHeader;
	int		row;
};

struct main_sqlite3_common_data
{
	const char		*name;
	int				type;
	union
	{
		char 		m_c;
		short		m_s;
		int			m_i;
		long		m_l;
		float  		m_f;
		double		m_d;
		char 		*m_t;
	};
};

struct main_sqlite3_open_helper
{
	int				version;
	const char 		*name;
	void 			(*on_create)(struct main_sqlite3_open_helper *helper, sqlite3 *db);
	void 			(*on_upgrade)(struct main_sqlite3_open_helper *helper, sqlite3 *db, int old_version, int new_version);
	void 			(*on_downgrade)(struct main_sqlite3_open_helper *helper, sqlite3 *db, int old_version, int new_version);
	sqlite3			*db;
};

void main_sqlite3_test();

void main_sqlite3_enter();
void main_sqlite3_leave();

int  main_sqlite3_open(struct main_sqlite3_open_helper *helper);

#endif // MAIN_SQLITE_H