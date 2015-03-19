#include <stdio.h>
#include <stdlib.h>

#include "main_sort.h"

#include "main_config.h"
#include "main_print.h"

void main_money_find_test();

void main_sort_test()
{
	int buffer[] = { 3, 2, 4, 1, 5 };

	main_sort_insert(buffer, ARRAY_SIZE(buffer));
	main_print_int_buffer(buffer, ARRAY_SIZE(buffer));

	// main_money_find_test();
}

int *main_binary_search(int *ptr, int n, int v)
{
	int *e, *m;

	e = ptr + n;
	while (ptr < e)
	{
		m = ptr + (e - ptr) / 2;
		if (*m == v)
		{
			return m;
		}
		else if (*m < v)
		{
			ptr = m + 1;
		}
		else
		{
			e = m;
		}
	}

	return NULL;
}

int main_binary_search_impl(int *ptr, int n, int v)
{
	int s, e, m, r;

	s = 0;
	e = n;
	r = -1;
	while (s < e)
	{
		m = s + (e - s) / 2;
		if (ptr[m] == v)
		{
			r = m;
			break;
		}
		else if (ptr[m] < v)
		{
			s = m + 1;
		}
		else
		{
			e = m;
		}
	}
	return r;
}

void main_sort_bubble(int *ptr, int n)
{
	int i, j;
	int t;

	for (j = n - 1; j > 0; --j)
	{
		for (i = 0; i < j; ++i)
		{
			if (ptr[i] > ptr[i + 1])
			{
				t = ptr[i];
				ptr[i] = ptr[i + 1];
				ptr[i + 1] = t;
			}
		}
	}
}

void main_sort_insert(int *ptr, int n)
{
	int i, j;
	int v;

	for (i = 1; i < n; ++i)
	{
		j = i;
		v = ptr[j];
		while (v < ptr[j - 1] && j > 0)
		{
			ptr[j] = ptr[j - 1];
			--j;
		}
		ptr[j] = v;
	}
}

void main_money_size_find(struct main_money_count *ptr, int count, int *money)
{
	struct main_money_count *end;

	end = ptr + count;
	while (ptr < end && *money > 0)
	{
		if (ptr->value <= *money)
		{
			ptr->count += *money / ptr->value;
			*money %= ptr->value;
		}
		++ptr;
	}
}

void main_money_find_test()
{
	struct main_money_count buffer[] = {
		{ 25, 0 },
		{ 10, 0 },
		{ 5, 0 },
		{ 1, 0 }
	};
	struct main_money_count *ptr, *end;
	int i;
	int m;
	bool is_first;

	for (i = 0; i < 1000; ++i)
	{
		end = buffer + ARRAY_SIZE(buffer);
		for (ptr = buffer; ptr != end; ++ptr)
		{
			ptr->count = 0;
		}

		m = i;
		main_money_size_find(buffer, ARRAY_SIZE(buffer), &m);

		fprintf(stdout, "%d=", i);
		is_first = true;
		for (ptr = buffer, end = buffer + ARRAY_SIZE(buffer); ptr != end; ++ptr)
		{
			if (0 == ptr->count)
			{
				continue;
			}

			if (is_first)
			{
				fprintf(stdout, "%d * %d", ptr->count, ptr->value);
				is_first = false;
			}
			else
			{
				fprintf(stdout, "+ %d * %d", ptr->count, ptr->value);
			}
		}
		fprintf(stdout, "\n");
	}	
}