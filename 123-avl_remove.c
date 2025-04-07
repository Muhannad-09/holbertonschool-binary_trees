#include "binary_trees.h"
#include <stdlib.h>

/**
 * avl_successor - Finds the in-order successor
 * @node: Pointer to the root of right subtree
 *
 * Return: Pointer to the successor node
 */
avl_t *avl_successor(avl_t *node)
{
	while (node && node->left)
		node = node->left;
	return (node);
}

/**
 * avl_remove_simple - Removes a node with 0 or 1 children
 * @root: Pointer to node to remove
 *
 * Return: Pointer to new subtree root
 */
avl_t *avl_remove_simple(avl_t *root)
{
	avl_t *temp = root->left ? root->left : root->right;

	if (!temp)
	{
		free(root);
		return (NULL);
	}
	temp->parent = root->parent;
	free(root);
	return (temp);
}

/**
 * avl_remove - Removes a node from an AVL tree
 * @root: Pointer to the root of the tree
 * @value: Value to remove
 *
 * Return: Pointer to the new root after deletion
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
			return (avl_remove_simple(root));

		successor = avl_successor(root->right);
		root->n = successor->n;
		root->right = avl_remove(root->right, successor->n);
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
