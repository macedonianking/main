#ifndef MAIN_SORT_H
#define MAIN_SORT_H

// 堆左子
#define HEAP_L(x)	(((x) << 1) + 1)
// 堆右子
#define HEAP_R(x)	(((x) << 1) + 2)
// 堆父成员
#define HEAP_P(x)	(((x)- 1) >> 1)

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

int  main_is_maximum_heap(int *ptr, int n);
int  main_is_maximum_heap(int *ptr, int n);

/**
 * 使用递归形式的代码
 */
void main_max_heapify(int *ptr, int n, int i);
void main_min_heapify(int *ptr, int n, int i);

/**
 * 使用循环形式的代码
 */
void main_max_heapify_iter(int *ptr, int n, int i);
void main_min_heapify_iter(int *ptr, int n, int i);

/**
 * 构建最大堆，最小堆
 */
void main_build_max_heapify(int *ptr, int n);
void main_build_min_heapify(int *ptr, int n);

/**
 * 堆排序，将根节点与最后节点互换，然后执行main_maximum_heapify
 * 维护最大堆的属性
 */
void main_heap_sort(int *ptr, int n);

/**
 * 快速排序
 */
void main_quick_sort(int *ptr, int n);

#endif // MAIN_SORT_H