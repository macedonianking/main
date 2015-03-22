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

#endif // MAIN_SORT_H