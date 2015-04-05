#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "main_utils.h"
#include "main_solutions.h"

static void 	main_solution_compare_sort_method_insert_and_merge();
static int 		main_solution_insert_and_merge_threshold();

void main_solutions_run()
{
	main_solution_compare_sort_method_insert_and_merge();
}

void main_solution_compare_sort_method_insert_and_merge()
{
	int n;

	n = main_solution_insert_and_merge_threshold();
	fprintf(stdout, "insert and merge thresold: %d\n", n);
}

int main_solution_insert_and_merge_threshold()
{
	int n;
	double v1;
	double v2;

	for (n = 2; n < 10000; ++n)
	{
		v1 = 8 * n * n;
		v2 = 64 * n * log2((double)n);

		if (v2 < v1)
		{
			break;
		}
	}

	return n;
}
