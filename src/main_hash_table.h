#ifndef MAIN_HASH_TABLE_H
#define MAIN_HASH_TABLE_H

struct main_hash_list_node
{
	struct main_hash_list_node *next;
	int value;
};

struct main_hash_table
{
	struct main_hash_list_node **ptr;
	int size;
	int (*hash)(struct main_hash_table *, int v);
};

/**
 * 散列表测试入口
 */
void main_hash_table_test();

void main_hash_table_add(struct main_hash_table *table, int value);
void main_hash_table_del(struct main_hash_table *table, int value);
void main_hash_table_release(struct main_hash_table *table);
void main_hash_list_release(struct main_hash_list_node *list);
void main_hash_list_print(struct main_hash_list_node *node);
void main_hash_table_print(struct main_hash_table *table);

#endif // MAIN_HASH_TABLE_H
