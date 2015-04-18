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
static void main_tree_inorder_tree_walk_iter_test(struct main_tree_node *node);

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

/**
 * 计算二叉搜索树节点数目
 */
int main_tree_size(struct main_tree_node *node)
{
	if (!node)
	{
		return 0;
	}

	return 1 + main_tree_size(node->left) + main_tree_size(node->right);
}

#define INORDER_TREE_WALK_STATE_NONE			0
#define INORDER_TREE_WALK_STATE_LEFT			1
#define INORDER_TREE_WALK_STATE_RIGHT			2

/**
 * 二叉搜索树中序遍历，使用迭代的方法
 */
void main_tree_inorder_tree_walk_iter_test(struct main_tree_node *node)
{
	int n;
	int *stack;
	int i;

	n = main_tree_depth(node);
	if (n == 0)
	{
		return;
	}
	stack = (int*) malloc(sizeof(int) * n);
	memset(stack, 0, sizeof(int) * n);

	i = 0;
	while (i >= 0)
	{
		if (INORDER_TREE_WALK_STATE_NONE == stack[i])
		{
			stack[i] = INORDER_TREE_WALK_STATE_LEFT;
			if (node->left)
			{
				node = node->left;
				++i;
			}
		}
		else if (INORDER_TREE_WALK_STATE_LEFT == stack[i])
		{
			stack[i] = INORDER_TREE_WALK_STATE_RIGHT;
			fprintf(stdout, "%d ", node->v);
			if (node->right)
			{
				node = node->right;
				++i;
			}
		}
		else if (INORDER_TREE_WALK_STATE_RIGHT == stack[i])
		{
			node = node->parent;
			--i;
		}
	}

	free(stack);
	stack = NULL;
}

/**
 * 获取节点深度的操作
 */
void main_tree_depth_recursive(struct main_tree_node *node, int *n, int *max)
{
	if (!node)
	{
		return;
	}

	++*n;
	if (*max < *n)
	{
		*max = *n;
	}

	main_tree_depth_recursive(node->left, n, max);
	main_tree_depth_recursive(node->right, n, max);
	--*n;
}

/**
 * 二叉树的深度
 */
int  main_tree_depth(struct main_tree_node *node)
{
	int n;
	int max;

	n = 0;
	max = 0;
	main_tree_depth_recursive(node, &n, &max);
	return max;
}