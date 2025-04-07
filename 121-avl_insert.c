#include "binary_trees.h"

/**
 * avl_insert - Inserts a value in an AVL Tree
 * @tree: Double pointer to the root node
 * @value: Value to insert
 *
 * Return: Pointer to the created node, or NULL on failure
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *new_node;
	int balance;

	if (!tree)
		return (NULL);

	if (!*tree)
	{
		*tree = binary_tree_node(NULL, value);
		return (*tree);
	}

	if (value < (*tree)->n)
	{
		new_node = avl_insert(&(*tree)->left, value);
		if (!new_node)
			return (NULL);
		(*tree)->left->parent = *tree;
	}
	else if (value > (*tree)->n)
	{
		new_node = avl_insert(&(*tree)->right, value);
		if (!new_node)
			return (NULL);
		(*tree)->right->parent = *tree;
	}
	else
	{
		/* Value already exists */
		return (*tree);
	}

	balance = binary_tree_balance(*tree);

	if (balance > 1 && value < (*tree)->left->n)
	{
		*tree = binary_tree_rotate_right(*tree);
	}
	else if (balance < -1 && value > (*tree)->right->n)
	{
		*tree = binary_tree_rotate_left(*tree);
	}
	else if (balance > 1 && value > (*tree)->left->n)
	{
		(*tree)->left = binary_tree_rotate_left((*tree)->left);
		(*tree)->left->parent = *tree;
		*tree = binary_tree_rotate_right(*tree);
	}
	else if (balance < -1 && value < (*tree)->right->n)
	{
		(*tree)->right = binary_tree_rotate_right((*tree)->right);
		(*tree)->right->parent = *tree;
		*tree = binary_tree_rotate_left(*tree);
	}

	return (new_node);
}
