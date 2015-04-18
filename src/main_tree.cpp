#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "main_tree.h"
#include "main_utils.h"
#include "main_print.h"

// 测试遍历顺序的代码
static void main_tree_tree_walk_test();
// 中序遍历代码
static void main_tree_inorder_tree_walk_test(struct main_tree_node *node);
// 先序遍历代码
static void main_tree_preorder_tree_walk_test(struct main_tree_node *node);
// 测试后续遍历方法
static void main_tree_postorder_tree_walk_test(struct main_tree_node *node);
// 用stack实现的中序遍历
static void main_tree_inorder_tree_walk_iter_test(struct main_tree_node *node);

void main_tree_test()
{
	main_tree_tree_walk_test();
}

/**
 * 二叉搜索树中序遍历的例子
 */
void main_tree_tree_walk_test()
{
	int buffer[] = { 6, 5, 2, 5, 7, 8 };
	struct main_tree_node *head;

	head = NULL;
	for (int i = 0; i != ARRAY_SIZE(buffer); ++i)
	{
		head = main_tree_add(head, buffer[i]);
	}

	/**
	 * 三种遍历顺序
	 */
	fprintf(stdout, "Middle traversal:\n");
	main_tree_inorder_tree_walk_test(head);
	fprintf(stdout, "\n");

	fprintf(stdout, "Front traversal:\n");
	main_tree_preorder_tree_walk_test(head);
	fprintf(stdout, "\n");

	fprintf(stdout, "Back traversal:\n");
	main_tree_postorder_tree_walk_test(head);
	fprintf(stdout, "\n");

	/**
	 * Inorder tree walk
	 */
	fprintf(stdout, "Inorder tree walk:\n");
	main_tree_inorder_tree_walk_iter_test(head);
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

	if (node->left)
	{
		main_tree_release(node->left);
		node->left = NULL;
	}

	if (node->right)
	{
		main_tree_release(node->right);
		node->right = NULL;
	}
	node->parent = NULL;
	free(node);
}

/**
 * 增加节点，返回ROOT节点
 */
struct main_tree_node *main_tree_add(struct main_tree_node *node, int v)
{
	struct main_tree_node *p;
	struct main_tree_node *h;

	p = (struct main_tree_node*) malloc(sizeof(struct main_tree_node));
	p->left = p->right = p->parent = NULL;
	p->v = v;

	if (!node)
	{
		return p;
	}

	h = node;
	while (node)
	{
		if (v < node->v)
		{
			if (node->left)
			{
				node = node->left;
			}
			else
			{
				node->left = p;
				p->parent = node;
				break;
			}
		}
		else
		{
			if (node->right)
			{
				node = node->right;
			}
			else
			{
				node->right = p;
				p->parent = node;
				break;
			}
		}
	}
	return h;
}

void main_tree_inorder_tree_walk_test(struct main_tree_node *node)
{
	if (!node)
	{
		return;
	}

	main_tree_inorder_tree_walk_test(node->left);
	fprintf(stdout, "%d ", node->v);
	main_tree_inorder_tree_walk_test(node->right);
}

void main_tree_preorder_tree_walk_test(struct main_tree_node *node)
{
	if (!node)
	{
		return;
	}

	fprintf(stdout, "%d ", node->v);
	main_tree_preorder_tree_walk_test(node->left);
	main_tree_preorder_tree_walk_test(node->right);
}

void main_tree_postorder_tree_walk_test(struct main_tree_node *node)
{
	if (!node)
	{
		return;
	}

	main_tree_postorder_tree_walk_test(node->left);
	main_tree_postorder_tree_walk_test(node->right);
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
				stack[i] = INORDER_TREE_WALK_STATE_NONE;
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
				stack[i] = INORDER_TREE_WALK_STATE_NONE;
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
int main_tree_depth(struct main_tree_node *node)
{
	int n;
	int max;

	n = 0;
	max = 0;
	main_tree_depth_recursive(node, &n, &max);
	return max;
}

/**
 * 二叉树搜索
 */
struct main_tree_node *main_tree_search(struct main_tree_node *node, int v)
{
	while (node && node->v != v)
	{
		if (v < node->v)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}
	return node;
}

/**
 * 二叉树最大节点
 */
struct main_tree_node *main_tree_minimum(struct main_tree_node *node)
{
	if (!node)
	{
		return node;
	}

	while (node->left)
	{
		node = node->left;
	}
	return node;
}

/**
 * 二叉树最小节点
 */
struct main_tree_node *main_tree_maximum(struct main_tree_node *node)
{
	if (!node)
	{
		return NULL;
	}

	while (node->right)
	{
		node = node->right;
	}
	return node;
}

/**
 * 二叉树后继
 */
struct main_tree_node *main_tree_next(struct main_tree_node *node)
{
	struct main_tree_node *p;

	if (node->right)
	{
		return main_tree_minimum(node->right);
	}

	p = node->parent;
	while (p && p->left != node)
	{
		node = p;
		p = node->parent;
	}
	return p;
}

/**
 * 二叉树前驱
 */
struct main_tree_node *main_tree_prev(struct main_tree_node *node)
{
	struct main_tree_node *p;

	if (node->left)
	{
		return main_tree_maximum(node->left);
	}

	p = node->parent;
	while (p && p->right != node)
	{
		node = p;
		p = node->parent;
	}
	return p;
}
