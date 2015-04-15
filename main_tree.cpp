#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "main_tree.h"
#include "main_utils.h"
#include "main_print.h"

static void main_tree_traversal_test();
static void main_tree_middle_traversal_test(struct main_tree_node *node);
static void main_tree_front_traversal_test(struct main_tree_node *node);
static void main_tree_back_traversal_test(struct main_tree_node *node);

void main_tree_test()
{
	main_tree_traversal_test();
}

/**
 * 二叉搜索树中序遍历的例子
 */
void main_tree_traversal_test()
{
	int buffer[] = { 6, 5, 2, 5, 7, 8 };
	struct main_tree_node *head;

	head = (struct main_tree_node*) malloc(sizeof(struct main_tree_node));
	head->parent = head->left = head->right = NULL;
	head->v = buffer[0];

	for (int i = 1; i != ARRAY_SIZE(buffer); ++i)
	{
		main_tree_add(head, buffer[i]);
	}

	/**
	 * 三种遍历顺序
	 */
	fprintf(stdout, "Middle traversal:\n");
	main_tree_middle_traversal_test(head);
	fprintf(stdout, "\n");

	fprintf(stdout, "Front traversal:\n");
	main_tree_front_traversal_test(head);
	fprintf(stdout, "\n");

	fprintf(stdout, "Back traversal:\n");
	main_tree_back_traversal_test(head);
	fprintf(stdout, "\n");

	main_tree_release(head);
	head = NULL;
}

void main_tree_release(struct main_tree_node *node)
{
	if (!node)
	{
		return;
	}

	if (node->left) {
		main_tree_release(node->left);	
		node->left = NULL;
	}

	if (node->right)
	{
		main_tree_release(node->right);
		node->right = NULL;
	}
	free(node);
}

void main_tree_add(struct main_tree_node *node, int v)
{
	if (v < node->v)
	{
		if (!node->left)
		{
			node->left = (struct main_tree_node*)malloc(sizeof(struct main_tree_node));
			node->left->left = node->left->right = NULL;
			node->left->parent = node;
			node->left->v = v;
		}
		else
		{
			main_tree_add(node->left, v);
		}
	}
	else
	{
		if (!node->right)
		{
			node->right = (struct main_tree_node *) malloc(sizeof(struct main_tree_node));
			node->right->left = node->right->right = NULL;
			node->right->parent = node;
			node->right->v = v;
		}
		else
		{
			main_tree_add(node->right, v);
		}
	}
}

void main_tree_middle_traversal_test(struct main_tree_node *node)
{
	if (!node)
	{
		return;
	}

	main_tree_middle_traversal_test(node->left);
	fprintf(stdout, "%d ", node->v);
	main_tree_middle_traversal_test(node->right);
}

void main_tree_front_traversal_test(struct main_tree_node *node)
{
	if (!node)
	{
		return;
	}

	fprintf(stdout, "%d ", node->v);
	main_tree_front_traversal_test(node->left);
	main_tree_front_traversal_test(node->right);
}

void main_tree_back_traversal_test(struct main_tree_node *node)
{
	if (!node)
	{
		return;
	}

	main_tree_back_traversal_test(node->left);
	main_tree_back_traversal_test(node->right);
	fprintf(stdout, "%d ", node->v);
}