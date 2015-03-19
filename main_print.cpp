#include <stdio.h>
#include <stdlib.h>

#include "main_print.h"

void main_print_int_buffer(const int *ptr, int n)
{
	if (n-- > 0)
	{
		printf("%d", *ptr++);
		while (n-- > 0)
		{
			printf(" %d", *ptr++);
		}
		printf("\n");
	}
}