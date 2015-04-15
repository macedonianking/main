#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "main_hash_table.h"
#include "main_config.h"

struct main_hash_list_node
{
	struct main_hash_list_node 	*next;
	int							value;
};

struct main_hash_table
{
	struct main_hash_list_node	**ptr;
	int							size;
	int	(*hash)(struct main_hash_table *, int v);
};

static void main_hash_table_add(struct main_hash_table *table, int value);
static void main_hash_table_del(struct main_hash_table *table, int value);
static void main_hash_table_release(struct main_hash_table *table);
static void main_hash_list_release(struct main_hash_list_node *list);
static void main_hash_list_print(struct main_hash_list_node *node);
static void main_hash_table_print(struct main_hash_table *table);

int main_hash_table_hash_impl(struct main_hash_table *table, int value)
{
	return value % (table->size);
}

/**
 * 散列表测试入口
 */
void main_hash_table_test()
{
	struct main_hash_table table;
	int size;
	int i;
	int buffer0[] = {5, 28, 19, 15, 20, 33, 12, 17, 10};

	table.size = 9;
	size = table.size * sizeof(struct main_hash_list_node*);
	table.ptr = (struct main_hash_list_node**) malloc(size);
	memset(table.ptr, 0, size);
	table.hash = &main_hash_table_hash_impl;

	size = ARRAY_SIZE(buffer0);
	for (i = 0; i != size; ++i)
	{
		main_hash_table_add(&table, buffer0[i]);
	}
	main_hash_table_print(&table);

	main_hash_table_release(&table);
}

void main_hash_table_add(struct main_hash_table *table, int value)
{
	int h;
	struct main_hash_list_node *p;

	h = table->hash(table, value);
	p = (struct main_hash_list_node *) malloc(sizeof(struct main_hash_list_node));
	p->next = table->ptr[h];
	p->value = value;
	table->ptr[h] = p;
}

void main_hash_table_del(struct main_hash_table *table, int value)
{
	int h;
	struct main_hash_list_node **pp;
	struct main_hash_list_node *next;

	h = table->hash(table, value);
	pp = &table->ptr[h];
	while (*pp != NULL && (*pp)->value != value)
	{
		pp = &((*pp)->next);
	}

	if (*pp == NULL)
	{
		return;
	}

	next = (*pp)->next;
	free(*pp);
	*pp = next;
}

void main_hash_list_release(struct main_hash_list_node *list)
{
	struct main_hash_list_node *next;

	while (list != NULL)
	{
		next = list->next;
		list->next = NULL;
		free(list);
		list = next;		
	}
}

void main_hash_table_release(struct main_hash_table *table)
{
	int i;

	for (i = 0; i != table->size; ++i)
	{
		main_hash_list_release(table->ptr[i]);
		table->ptr[i] = NULL;
	}
	free(table->ptr);
	table->ptr = NULL;
}

void main_hash_list_print(struct main_hash_list_node *node)
{
	int isFirst;

	while (node != NULL)
	{
		if (isFirst)
		{
			fprintf(stdout, "%-2d", node->value);
			isFirst = 0;
		}
		else
		{
			fprintf(stdout, " %-2d", node->value);
		}
		node = node->next;
	}
}

void main_hash_table_print(struct main_hash_table *table)
{
	int i = 0;

	fprintf(stdout, "Hash table: [size=%d]\n", table->size);
	for (i = 0; i != table->size; ++i)
	{
		fprintf(stdout, "%2d :", i);
		main_hash_list_print(table->ptr[i]);
		fprintf(stdout, "\n");
	}
}