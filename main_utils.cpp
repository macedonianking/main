#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

#include "main_utils.h"

int *main_random_integer_buffer(int n, int s, int e)
{
	int *ptr;
	int i;
	int t;

	if (n <= 0)
	{
		return NULL;
	}

	if (e < s)
	{
		t = s;
		s = e;
		e = t;
	} 
	else if (e == s)
	{
		return NULL;
	}

	ptr = (int*) malloc(sizeof(int) * n);
	srand((unsigned)clock());
	for (i = 0; i < n; ++i)
	{
		ptr[i] = rand() % (e - s) + s;
	}

	return ptr;
}