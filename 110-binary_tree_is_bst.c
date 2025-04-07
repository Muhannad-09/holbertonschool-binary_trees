#include "binary_trees.h"
#include <limits.h>

/**
 * is_bst_helper - helper to check if a tree is a BST
 * @tree: pointer to the root node
 * @min: minimum allowed value
 * @max: maximum allowed value
 *
 * Return: 1 if valid BST, 0 otherwise
 */
int is_bst_helper(const binary_tree_t *tree, int min, int max)
{
	if (!tree)
		return (1);

	if (tree->n <= min || tree->n >= max)
		return (0);

	return (is_bst_helper(tree->left, min, tree->n) &&
		is_bst_helper(tree->right, tree->n, max));
}

/**
 * binary_tree_is_bst - checks if a binary tree is a valid BST
 * @tree: pointer to the root node of the tree to check
 *
 * Return: 1 if BST, 0 otherwise
 */
int binary_tree_is_bst(const binary_tree_t *tree)
{
	if (!tree)
		return (0);

	return (is_bst_helper(tree, INT_MIN, INT_MAX));
}
