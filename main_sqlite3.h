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

void main_sqlite3_test();

#endif // MAIN_SQLITE_H