#ifndef MAIN_TREE_H
#define MAIN_TREE_H

struct main_tree_node
{
	struct main_tree_node *parent;
	struct main_tree_node *left;
	struct main_tree_node *right;
	int 				  v;
};

/**
 * 二叉搜索树测试入口
 */
void main_tree_test();

void main_tree_release(struct main_tree_node *node);
void main_tree_add(struct main_tree_node *node, int v);

#endif // MAIN_TREE_H