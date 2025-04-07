#include "binary_trees.h"

/**
 * avl_insert - inserts a value in an AVL tree
 * @tree: double pointer to the root node
 * @value: value to insert
 *
 * Return: pointer to the new node, or NULL on failure
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	int balance;
	avl_t *new_node;

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
		
		return (NULL);
	}

	
	balance = binary_tree_balance(*tree);

	if (balance > 1 && value < (*tree)->left->n)
		return (binary_tree_rotate_right(*tree));
	if (balance < -1 && value > (*tree)->right->n)
		return (binary_tree_rotate_left(*tree));
	if (balance > 1 && value > (*tree)->left->n)
	{
		(*tree)->left = binary_tree_rotate_left((*tree)->left);
		return (binary_tree_rotate_right(*tree));
	}
	if (balance < -1 && value < (*tree)->right->n)
	{
		(*tree)->right = binary_tree_rotate_right((*tree)->right);
		return (binary_tree_rotate_left(*tree));
	}

	return (new_node);
}
