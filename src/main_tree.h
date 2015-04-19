#ifndef MAIN_TREE_H
#define MAIN_TREE_H

struct main_tree_node
{
	struct main_tree_node *parent;
	struct main_tree_node *left;
	struct main_tree_node *right;
	int v;
};

/**
 * 二叉搜索树测试入口
 */
void main_tree_test();

void main_tree_release(struct main_tree_node *node);
/**
 * 增加一个节点，返回ROOT节点
 */
struct main_tree_node *main_tree_add(struct main_tree_node *node, int v);
/**
 * 从二叉树中删除一个节点
 */
void main_tree_del(struct main_tree_node **head, struct main_tree_node *node);
void main_tree_node_release(struct main_tree_node *node);
void main_tree_transplant(struct main_tree_node **head, struct main_tree_node *u,
		struct main_tree_node *v);
/**
 * 计算节点个数
 */
int main_tree_size(struct main_tree_node *node);
/**
 * 获取二叉树节点深度
 */
int main_tree_depth(struct main_tree_node *node);
/**
 * 执行二叉搜索
 */
struct main_tree_node *main_tree_search(struct main_tree_node *node, int v);

struct main_tree_node *main_tree_minimum(struct main_tree_node *node);
struct main_tree_node *main_tree_maximum(struct main_tree_node *node);
struct main_tree_node *main_tree_next(struct main_tree_node *node);
struct main_tree_node *main_tree_prev(struct main_tree_node *node);

#endif // MAIN_TREE_H
