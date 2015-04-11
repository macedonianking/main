#include <stdio.h>
#include <stdlib.h>

#include "main_priority_queue.h"
#include "main_utils.h"
#include "main_sort.h"
#include "main_print.h"

static void main_max_priority_queue_test_take();

void main_priority_queue_test()
{
	main_max_priority_queue_test_take();
}

int main_max_priority_queue_take(int *ptr, int *n)
{
	int r;

	if (*n <= 0)
	{
		return 0;
	}

	r = ptr[0];
	ptr[0] = ptr[*n - 1];
	--*n;
	main_max_heapify(ptr, *n, 0);
	return r;
}

void main_max_priority_queue_test_take()
{
	int *ptr;
	int n;

	n = 10;
	ptr = main_random_integer_buffer(n, -10, 10);
	main_build_max_heapify(ptr, n);
	fprintf(stdout, "main_max_priority_queue_test_take:");
	main_print_int_buffer(ptr, n);
	while (n > 0)
	{
		fprintf(stdout, "%d\n", main_max_priority_queue_take(ptr, &n));
	}

	free(ptr);
	ptr = NULL;
}

void main_max_priority_queue_increase_key(int *ptr, int n, int i, int new_key)
{
	int k;
	int t;

	if (ptr[i] < new_key)
	{
		return;
	}

	ptr[i] = new_key;

	while (i > 0)
	{
		k = (i - 1) >> 1;
		if (ptr[k] >= ptr[i])
		{
			break;
		}

		t = ptr[k];
		ptr[k] = ptr[i];
		ptr[i] = t;
		i = k;
	}
}

void main_max_priority_queue_insert(int *ptr, int *n, int v)
{
	int i;
	int k;
	int t;

	i = *n;
	++*n;
	ptr[i] = v;

	while (i > 0)
	{
		k = (i - 1) >> 1;
		if (ptr[k] >= ptr[i])
		{
			break;
		}

		t = ptr[k];
		ptr[k] = ptr[i];
		ptr[i] = t;
		i = k;
	}
}