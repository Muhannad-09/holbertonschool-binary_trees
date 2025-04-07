#include "binary_trees.h"
#include <stdlib.h>

/**
 * avl_successor - Finds the in-order successor
 * @node: Pointer to the root
 * Return: Pointer to successor
 */
avl_t *avl_successor(avl_t *node)
{
	avl_t *current = node;

	while (current && current->left)
		current = current->left;
	return (current);
}

/**
 * avl_remove_node - Removes a node from the AVL tree
 * @root: Pointer to root
 * @value: Value to remove
 * Return: New root after deletion and balancing
 */
avl_t *avl_remove(avl_t *root, int value)
{
	avl_t *successor;
	int balance;

	if (!root)
		return (NULL);

	if (value < root->n)
		root->left = avl_remove(root->left, value);
	else if (value > root->n)
		root->right = avl_remove(root->right, value);
	else
	{
		if (!root->left || !root->right)
		{
			avl_t *temp = root->left ? root->left : root->right;

			if (!temp)
			{
				temp = root;
				root = NULL;
			}
			else
			{
				*root = *temp;
			}
			free(temp);
		}
		else
		{
			successor = avl_successor(root->right);
			root->n = successor->n;
			root->right = avl_remove(root->right, successor->n);
		}
	}

	if (!root)
		return (NULL);

	
	balance = binary_tree_balance(root);

	if (balance > 1 && binary_tree_balance(root->left) >= 0)
		return (binary_tree_rotate_right(root));
	if (balance > 1 && binary_tree_balance(root->left) < 0)
	{
		root->left = binary_tree_rotate_left(root->left);
		return (binary_tree_rotate_right(root));
	}
	if (balance < -1 && binary_tree_balance(root->right) <= 0)
		return (binary_tree_rotate_left(root));
	if (balance < -1 && binary_tree_balance(root->right) > 0)
	{
		root->right = binary_tree_rotate_right(root->right);
		return (binary_tree_rotate_left(root));
	}

	return (root);
}
