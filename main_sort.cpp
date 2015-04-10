#include <stdio.h>
#include <stdlib.h>

#include "main_sort.h"

#include <time.h>
#include "main_config.h"
#include "main_print.h"
#include "main_utils.h"

#define F_MAIN_TEST

// 测试代码声明
#ifdef F_MAIN_TEST
static void main_test_find_maximum_linear_buffer();
static void main_test_heap_sort();
#endif // F_MAIN_TEST

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

	// 测试代码调用
	#ifdef F_MAIN_TEST
	main_test_find_maximum_linear_buffer();
	main_test_heap_sort();
	#endif
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

void main_find_maximum_linear_subarray_normal(const int *ptr, int n, int *l, int *r, int *v)
{
	int i, j;
	int max, maxL, maxR;
	int sum;

	*l = *r = -1;
	*v = 0;

	if (n <= 0)
	{
		return;
	}

	max = ptr[0];
	maxL = 0;
	maxR = 1;
	for (i = 0; i < n; ++i)
	{
		sum = ptr[i];
		j = i + 1;
		if (max < sum)
		{
			max = sum;
			maxL = i;
			maxR = j;
		}
		else if (max == sum)
		{
			if ((j - i) < (maxR - maxL))
			{
				maxL = i;
				maxR = j;
			}
		}

		while (j < n)
		{
			sum += ptr[j];
			++j;
			if (max < sum)
			{
				max = sum;
				maxL = i;
				maxR = j;
			}
			else if (max == sum)
			{
				if ((j - i) < (maxR - maxL))
				{
					maxL = i;
					maxR = j;
				}
			}
		}
	}
	*l = maxL;
	*r = maxR;
	*v = max;
}

static int main_find_maximum_linear_subarray_divide_impl(int *ptr, int s, int e, int *l, int *r, int *v)
{
	int m;
	int outL, outR, outV;
	int maxL, maxR, max;
	int t;
	int i;

	if (e <= s)
	{
		return 1;
	}

	m = s + (e - s) / 2;
	maxL = maxR = -1;
	if (!(main_find_maximum_linear_subarray_divide_impl(ptr, s, m, &outL, &outR, &outV)))
	{
		if (maxL == -1 || max < outV)
		{
			maxL = outL;
			maxR = outR;
			max = outV;
		}
	}

	if (!main_find_maximum_linear_subarray_divide_impl(ptr, m + 1, e, &outL, &outR, &outV))
	{
		if (maxL == -1 || max < outV)
		{
			maxL = outL;
			maxR = outR;
			max = outV;
		}
	}

	outV = ptr[m];
	outL = m;
	outR = m + 1;
	t = outV;
	i = outL - 1;
	while (i >= s)
	{
		t += ptr[i];
		if (outV < t)
		{
			outL = i;
			outV = t;
		}
		--i;
	}

	i = outR;
	t = outV;
	while (i < e)
	{
		t += ptr[i];
		++i;
		if (t > outV)
		{
			outR = i;
			outV = t;
		}
	}

	if (maxL == -1 || max < outV)
	{
		maxL = outL;
		maxR = outR;
		max = outV;
	}

	*l = maxL;
	*r = maxR;
	*v = max;
	return 0;
}

/**
 * 分治法
 */
void main_find_maximum_linear_subarray_divide(int *ptr, int n, int *l, int *r, int *v)
{
	if (n > 0)
	{
		main_find_maximum_linear_subarray_divide_impl(ptr, 0, n, l, r, v);
	}
}

void main_find_maximum_linear_subarray_literal(const int *ptr, int n, int *l, int *r, int *s)
{
	int outL, outR, outS;
	int iterL, iterR, iterS;
	int v;
	int i, j;

	if (n <= 0) 
	{
		return; 
	}

	outL = 0;
	outR = 1;
	outS = ptr[0];

	for (i = 1; i < n; ++i)
	{
		iterL = i;
		iterR = i + 1;
		iterS = ptr[i];
		v = iterS;
		for (j = i - 1; j >= outL; --j)
		{
			v += ptr[j];
			if (iterS < v)
			{
				iterS = v;
				iterL = j;
			}
		}

		if (outS < iterS)
		{
			outS = iterS;
			outL = iterL;
			outR = iterR;
		}
	}

	*l = outL;
	*r = outR;
	*s = outS;
}

// 测试代码
#ifdef F_MAIN_TEST

void main_test_find_maximum_linear_buffer()
{
	int *ptr;
	int l, r, v;

	if (!(ptr = main_random_integer_buffer(10, -5, 5)))
	{
		return;
	}

	main_print_int_buffer(ptr, 10);
	main_find_maximum_linear_subarray_normal(ptr, 10, &l, &r, &v);
	if (l != -1 && r != -1)
	{
		fprintf(stdout, "normal:l=%d, r=%d, v=%d\n", l, r, v);
	}

	l = r = -1;
	main_find_maximum_linear_subarray_divide(ptr, 10, &l, &r, &v);
	if (l != -1 && r != -1)
	{
		fprintf(stdout, "divide:l=%d, r=%d, v=%d\n", l, r, v);
	}
	else
	{
		fprintf(stdout, "failure\n");
	}

	l = r = -1;
	main_find_maximum_linear_subarray_literal(ptr, 10, &l, &r, &v);
	if (l != -1 && r != -1)
	{
		fprintf(stdout, "literal:l=%d, r=%d, v=%d\n", l, r, v);
	}
	else
	{
		fprintf(stderr, "literal failure");
	}

	free(ptr);
	ptr = NULL;
}

#endif // F_MAIN_TEST

static int main_is_maximum_heap_recursive(int *ptr, int n, int i)
{
	int j;

	if (n < i)
	{
		return 0;
	}

	j = i * 2 + 1;
	if (j < n)
	{
		if (ptr [i] < ptr[j] || main_is_maximum_heap_recursive(ptr, n, j) != 0) 
		{
			return 1;
		}
	}

	j += 1;
	if (j < n)
	{
		if (ptr [i] < ptr[j] || main_is_maximum_heap_recursive(ptr, n, j) != 0) 
		{
			return 1;
		}
	}

	return 0;
}

int main_is_maximum_heap(int *ptr, int n)
{
	return main_is_maximum_heap_recursive(ptr, n, 0);
}

int main_is_minimum_heap(int *ptr, int n)
{
	int limit;
	int i;
	int l, r;

	limit = n >> 1;
	for (i = 0; i < limit; ++i)
	{
		l =	(i << 1) + 1;
		r = l + 1;
		if (l < n && ptr[i] > ptr[l])
		{
			return 1;
		}

		if (r < n && ptr[i] > ptr[r])
		{
			return 1;
		}
	}

	return 0;
}

void main_max_heapify(int *ptr, int n, int i)
{
	int l, r;
	int max;
	int t;

	max = i;
	l = 2 * i + 1;
	r = l + 1;
	if (l < n && ptr[max] < ptr[l])
	{
		max = l;
	}

	if (r < n && ptr[max] < ptr[r])
	{
		max = r;
	}

	if (max != i)
	{
		t = ptr[i];
		ptr[i] = ptr[max];
		ptr[max] = t;
		main_max_heapify(ptr, n, max);
	}
}

void main_min_heapify(int *ptr, int n, int i)
{
	int l, r;
	int min;
	int t;

	min = i;
	l = (i << 1) + 1;
	r = l + 1;
	if (l < n && ptr[l] < ptr[min])
	{
		min = l;
	}

	if (r < n && ptr[r] < ptr[min])
	{
		min = r;
	}

	if (min != i)
	{
		t = ptr[min];
		ptr[min] = ptr[i];
		ptr[i] = t;
		main_min_heapify(ptr, n, min);
	}
}

void main_max_heapify_iter(int *ptr, int n, int i)
{
	int l, r;
	int max;
	int t;

	while (true)
	{
		max = i;
		l = (i << 1) + 1;
		r = l + 1;
		if (l < n && ptr[max] < ptr[l])
		{
			max = l;
		}

		if (r < n && ptr[max] < ptr[r])
		{
			max = r;
		}

		if (max == i)
		{
			break;
		}
		else
		{
			t = ptr[i];
			ptr[i] = ptr[max];
			ptr[max] = t;
		}
	}
}

void main_min_heapify_iter(int *ptr, int n, int i)
{
	int l, r;
	int min;
	int t;

	while (true)
	{
		min = i;
		l = (i << 1) + 1;
		r = l + 1;
		if (l < n && ptr[l] < ptr[min])
		{
			min = l;
		}

		if (r < n && ptr[r] < ptr[min])
		{
			min = r;
		}

		if (min == i)
		{
			break;
		}
		else
		{
			t = ptr[i];
			ptr[i] = ptr[min];
			ptr[min] = t;
		}
	}
}

#ifdef F_MAIN_TEST
#define F_MAIN_TEST_BUFFER_SIZE	10
#define F_MAIN_TEST_BUFFER_FM	-10
#define F_MAIN_TEST_BUFFER_TO	10

void main_test_heap_sort()
{
	int buffer0[] = {23, 17, 14, 6, 13, 10, 1, 5, 7, 12};
	int buffer1[] = {27, 17, 3, 16, 13, 10, 1, 5, 7, 12,
					 4, 8, 9, 0};
	int n;
	int *buffer;

	n = main_is_maximum_heap(buffer0, ARRAY_SIZE(buffer0));
	if (n == 0)
	{
		fprintf(stdout, "buffer0 is maximum heap\n");
	}
	else
	{
		fprintf(stdout, "buffer0 is not maximum heap\n");
	}
	main_max_heapify(buffer1, ARRAY_SIZE(buffer1), 2);
	n = main_is_maximum_heap(buffer1, ARRAY_SIZE(buffer1));
	if (n == 0)
	{
		fprintf(stdout, "buffer1 is maximum heap\n");
	}
	else
	{
		fprintf(stdout, "buffer1 is not maximum heap\n");
	}

	buffer = main_random_integer_buffer(F_MAIN_TEST_BUFFER_SIZE, 
										F_MAIN_TEST_BUFFER_FM,
										F_MAIN_TEST_BUFFER_TO);
	main_build_max_heapify(buffer, F_MAIN_TEST_BUFFER_SIZE);
	n = main_is_maximum_heap(buffer, F_MAIN_TEST_BUFFER_SIZE);
	if (n == 0)
	{
		fprintf(stdout, "buffer is maximum heap\n");
	}
	else
	{
		fprintf(stdout, "buffer is not maximum heap\n");
	}

	main_build_min_heapify(buffer, F_MAIN_TEST_BUFFER_SIZE);
	n = main_is_minimum_heap(buffer, F_MAIN_TEST_BUFFER_SIZE);
	if (n == 0)
	{
		fprintf(stdout, "buffer is minimum heap\n");
	}
	else
	{
		fprintf(stdout, "buffer is not minimum heap\n");
	}

	main_heap_sort(buffer, F_MAIN_TEST_BUFFER_SIZE);
	fprintf(stdout, "Heap sort:\n");
	main_print_int_buffer(buffer, F_MAIN_TEST_BUFFER_SIZE);

	delete buffer;
	buffer = NULL;
}
#endif // F_MAIN_TEST

void main_build_max_heapify(int *ptr, int n)
{
	int i;
	int m;

	m = n >> 1;
	for (i = m; i >= 0; --i)
	{
		main_max_heapify(ptr, n, i);
	}
}

void main_build_min_heapify(int *ptr, int n)
{
	int i;
	int m;

	m = n >> 1;
	for (i = m; i >= 0; --i)
	{
		main_min_heapify(ptr, n, i);
	}
}

void main_heap_sort(int *ptr, int n)
{
	int i;
	int t;

	/**
	 * 构建最大堆
	 */
	main_build_max_heapify(ptr, n);
	for (i = n - 1; i > 0; --i)
	{
		t = ptr[i];
		ptr[i] = ptr[0];
		ptr[0] = t;

		/**
		 * 维护最大堆的性质
		 */
		main_max_heapify(ptr, i, 0);
	}
}