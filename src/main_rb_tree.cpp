/*
 * main_rb_tree.cpp
 *
 *  Created on: 2015年4月19日
 *      Author: lhb
 */

#include <stdio.h>
#include <stdlib.h>

#include "main_rb_tree.h"
#include "main_config.h"

void main_rb_tree_test()
{
}

void main_rb_tree_rotate_l(struct main_rb_tree *tree, struct main_rb_tree_node *x)
{
	struct main_rb_tree_node *y;

	y = x->r;
	x->r = y->l;
	if (x->r)
	{
		x->r->p = x;
	}
	y->p = x->p;
	if (!x->p)
	{
		tree->head = y;
	}
	else if (x->p->l == x)
	{
		x->p->l = y;
	}
	else
	{
		x->p->r = y;
	}
	x->p = y;
	y->l = x;
}

void main_rb_tree_rotate_r(struct main_rb_tree *tree, struct main_rb_tree_node *y)
{
	struct main_rb_tree_node *x;

	x = y->l;
	y->l = x->r;
	if (y->l)
	{
		y->l->p = y;
	}
	x->p = y->p;
	if (!x->p)
	{
		tree->head = x;
	}
	else if (x->p->l == y)
	{
		x->p->l = x;
	}
	else
	{
		x->p->r = x;
	}
	y->p = x;
	x->l = y;
}
