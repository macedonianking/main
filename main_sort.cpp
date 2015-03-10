#include "main_sort.h"

#include <stdio.h>
#include <stdlib.h>

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