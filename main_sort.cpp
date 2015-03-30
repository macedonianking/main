#include <stdio.h>
#include <stdlib.h>

#include "main_sort.h"

#include "main_config.h"
#include "main_print.h"

void main_money_find_test();

void main_sort_test()
{
	int buffer1[] = { 3, 2, 4, 1, 5 };
	int buffer2[] = { 3, 5, 4, 1, 2 };
	int buffer3[] = { 3, 5, 4, 1, 2 };
	int buffer4[] = { 5, 2 };
	int buffer5[] = { 3, 5, 4, 1, 2 };
	const char *str;
	int n;

	main_sort_insert(buffer1, ARRAY_SIZE(buffer1));
	main_print_int_buffer(buffer1, ARRAY_SIZE(buffer1));
	main_sort_select(buffer2, ARRAY_SIZE(buffer2));
	main_print_int_buffer(buffer2, ARRAY_SIZE(buffer2));
	main_sort_linear_insert(buffer3, ARRAY_SIZE(buffer3));
	main_print_int_buffer(buffer3, ARRAY_SIZE(buffer3));
	main_sort_linear_insert(buffer4, ARRAY_SIZE(buffer4));
	main_print_int_buffer(buffer4, ARRAY_SIZE(buffer4));
	main_sort_divide_merge(buffer5, ARRAY_SIZE(buffer5));
	main_print_int_buffer(buffer5, ARRAY_SIZE(buffer5));

	// main_money_find_test();
	n = 0;
	str = main_find_maximum_word("main_money_find_test()", &n);
	if (str != NULL)
	{
		fwrite(str, n, 1, stdout);
		fputc('\n', stdout);
	}
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

void main_sort_select(int *ptr, int n)
{
	int i, j;
	int min;
	int t;

	for (i = 0; i < n; ++i)
	{
		min = i;
		for (j = i + 1; j < n; ++j)
		{
			if (ptr[j] < ptr[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			t = ptr[min];
			ptr[min] = ptr[i];
			ptr[i] = t;
		}
	}
}

void main_sort_binary_insert(int *ptr, int n)
{
	int i, j;
	int s, e, m;
	int t;

	for (i = 1; i < n; ++i)
	{
		s = 0;
		e = i;
		while (s < e)
		{
			m = s + (e - s) / 2;
			if (ptr[m] <= ptr[i])
			{
				s = m + 1;
			}
			else
			{
				e = m;
			}
		}

		t = ptr[i];
		for (j = i; j > e; --j)
		{
			ptr[j] = ptr[j - 1];
		}
		ptr[j] = t;
	}
}

void main_sort_linear_insert(int *ptr, int n)
{
	int i, j;
	int t;
	int m;

	for (i = 0; i < n; ++i)
	{
		for (j = i; j > 0 && ptr[j - 1] > ptr[i]; --j)
			;
		t = ptr[i];
		for (m = i; m != j; --m)
		{
			ptr[m] = ptr[m - 1];
		}
		ptr[m] = t;
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

int main_buffer_sum(int *ptr, int n)
{
	int s;

	s = 0;
	while (n-- > 0)
	{
		s += *ptr++;
	}
	return s;
}

int main_find_maximum_delta(int *ptr, int n, int *out)
{
	int i;
	int delta;
	int max;

	if (n < 2)
	{
		return 1;
	}

	delta = ptr[1] - ptr[0];
	max = delta;
	for (i = 2; i < n; ++i)
	{
		delta = ptr[i] - ptr[i - 1];
		if (max < delta)
		{
			max = delta;
		}
	}
	*out = max;

	return 0;
}

int main_find_same_value_size(int *ptr, int n)
{
	int size;
	int status; // last value is difference from left
	int i;

	size = 0;
	status = 1;
	for (i = 1; i < n; ++i)
	{
		if (status && (ptr[i] == ptr[i - 1]))
		{
			++size;
		}
		status = ptr[i] != ptr[i - 1];
	}

	return size;
}

int main_buffer_negative_size(int *ptr, int n)
{
	int size;
	int i;

	size = 0;
	for (i = 0; i < n; ++i)
	{
		if (ptr[i] < 0)
		{
			++size;
		}
	}

	return size;
}

int main_buffer_last_even_index(int *ptr, int n)
{
	int i;
	int r;

	r = -1;
	for (i = 0; i < n; ++i)
	{
		if ((ptr[i] % 2) == 0)
		{
			r = i;
		}
	}

	return r;
}

int main_buffer_max_even_index(int *ptr, int n)
{
	int i;
	int r;

	r = -1;
	for (i = 0; i < n; ++i)
	{
		if (ptr[i] % 2 == 0)
		{
			if (r == -1 || ptr[r] < ptr[i])
			{
				r = i;
			}
		}
	}

	return r;
}

int main_string_is_palindrom(const char *str)
{
	const char *end;

	end = str;
	while (*end != '\0')
	{
		++end;
	}
	--end;

	while (str < end && *str == *end)
	{
		++str;
		--end;
	}

	return str < end && *str != *end;
}


double main_pow_integer(double v, int n)
{
	double r;

	r = v;
	if (n > 0)
	{
		while (n--)
		{
			r *= v;
		}
	}
	else
	{
		while (n++)
		{
			r /= v;
		}
	}

	return r;
}

void main_buffer_find_max_and_min(int *ptr, int n, int *max, int *min)
{
	int i;

	if (n <= 0)
	{
		return;
	}

	max = ptr;
	min = ptr;
	for (i = 1; i < n; ++i)
	{
		if (*max < ptr[i])
		{
			max = ptr + i;
		}

		if (ptr[i] < *min)
		{
			min = ptr + i;
		}
	}
}

#define WORD_STATE_IN 	0
#define WORD_STATE_OFF	1

const char *main_find_maximum_word(const char *str, int *outN)
{
	int state;
	int n;
	int maxN;
	const char *head;
	const char *maxHead;

	state = WORD_STATE_OFF;
	head = NULL;
	n = 0;
	maxN = 0;
	maxHead = NULL;

	while (*str != '\0')
	{
		if (('a' <= *str && *str <= 'z') 
			|| ('A' <= *str && *str <= 'Z'))
		{
			if (state == WORD_STATE_OFF)
			{
				state = WORD_STATE_IN;
				head = str;
				n = 1;
			}
			else
			{
				++n;
				if (n > maxN)
				{
					maxN = n;
					maxHead = head;
				}
			}
		}
		else
		{
			if (state == WORD_STATE_IN)
			{
				state = WORD_STATE_OFF;
			}
		}
		++str;
	}

	if (maxN > 0)
	{
		*outN = maxN;
	}

	return maxHead;
}

void main_sort_divide_merge(int *ptr, int n)
{
	int m;
	int *p, *q, *r, *iter;
	int t;

	if (n < 2)
	{
		return;
	}

	m = n / 2;
	main_sort_divide_merge(ptr, m);
	main_sort_divide_merge(ptr + m, n - m);

	p = ptr;
	q = ptr + m;
	r = ptr + n;
	while (p < q && q < r)
	{
		if (*p <= *q)
		{
			++p;
		}
		else
		{
			t = *q;
			iter = q;
			while (iter != p)
			{
				*iter = *(iter - 1);
				--iter;
			}
			*iter = t;
			++q;
			++p;
		}
	}
}