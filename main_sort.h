#ifndef MAIN_SORT_H
#define MAIN_SORT_H

struct main_money_count
{
	int 	value;
	int 	count;
};

int *main_binary_search(int *ptr, int n, int v);

void main_sort_bubble(int *ptr, int n);
void main_sort_insert(int *ptr, int n);
void main_sort_select(int *ptr, int n);
void main_sort_binary_insert(int *ptr, int n);
void main_sort_linear_insert(int *ptr, int n);
void main_sort_divide_merge(int *ptr, int n);

void main_sort_test();

/**
 * @param buffer
 * @param count
 * @param money
 */
void main_money_size_find(struct main_money_count *buffer, int count, int *money);

int main_buffer_sum(int *ptr, int n);

/**
 * @return int: 0 for success
 *				1 for failure.
 *
 */
int main_find_maximum_delta(int *ptr, int n, int *out);

int main_find_same_value_size(int *ptr, int n);

int main_buffer_negative_size(int *ptr, int n);

int main_buffer_last_even_index(int *ptr, int n);

int main_buffer_max_even_index(int *ptr, int n);

/**
 * @return : 0 for success
 *		   : 1 for failure
 */
int main_string_is_palindrom(const char *ptr);

/**
 *
 */
double main_pow_integer(double v, int n);

void main_buffer_find_max_and_min(int *ptr, int n, int *min, int *max);

/**
 *
 */
const char* main_find_maximum_word(const char *str, int *outN);

/**
 * 寻找最大连续字数组，使用穷举法
 *
 * @param l, r, v: out value
 * @return
 */
void main_find_maximum_linear_subarray_normal(const int *ptr, int n, int *l, int *r, int *v);

/**
 * 寻找最大连续字数组，使用分治法
 */
void main_find_maximum_linear_subarray_divide(const int *ptr, int n, int *l, int *r, int *v);

/**
 * 寻找最大连续字数组，使用迭代法(算法复杂度:Omega(n))
 */
void main_find_maximum_linear_subarray_literal(const int *ptr, int n, int *l, int *r, int *v);

int* main_random_integer_buffer(int n, int s, int e);

int  main_is_maximum_heap(int *ptr, int n);

#endif // MAIN_SORT_H