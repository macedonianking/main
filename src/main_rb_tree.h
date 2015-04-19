/*

 * main_rb_tree.h
 *
 *  Created on: 2015年4月19日
 *      Author: lhb
 */

#ifndef MAIN_RB_TREE_H

#define MAIN_RB_COLOR_B 0x0000
#define MAIN_RB_COLOR_R	0x0001

struct main_rb_tree_node
{
	struct main_rb_tree_node *p;
	struct main_rb_tree_node *l;
	struct main_rb_tree_node *r;
	int color;
	int v;
};

struct main_rb_tree
{
	struct main_rb_tree_node *head;
};

void main_rb_tree_test();

// 红黑树左旋
void main_rb_tree_rotate_l(struct main_rb_tree *tree, struct main_rb_tree_node *x);
// 红黑树右旋
void main_rb_tree_rotate_r(struct main_rb_tree *tree, struct main_rb_tree_node *y);

#endif // MAIN_RB_TREE_H
