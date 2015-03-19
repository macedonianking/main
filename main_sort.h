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

void main_sort_test();

/**
 * @param buffer
 * @param count
 * @param money
 */
void main_money_size_find(struct main_money_count *buffer, int count, int *money);

#endif // MAIN_SORT_H