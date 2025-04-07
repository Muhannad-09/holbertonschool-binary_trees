#include "binary_trees.h"
#include <limits.h>

/**
 * tree_height - calculates the height of a binary tree
 * @tree: pointer to root node
 *
 * Return: height of the tree
 */
int tree_height(const binary_tree_t *tree)
{
	int left, right;

	if (!tree)
		return (0);

	left = tree_height(tree->left);
	right = tree_height(tree->right);

	return ((left > right ? left : right) + 1);
}

/**
 * is_avl_helper - checks if a tree is a valid AVL tree
 * @tree: pointer to the root
 * @min: min valid value
 * @max: max valid value
 *
 * Return: 1 if AVL, 0 otherwise
 */
int is_avl_helper(const binary_tree_t *tree, int min, int max)
{
	int lh, rh;

	if (!tree)
		return (1);

	if (tree->n <= min || tree->n >= max)
		return (0);

	lh = tree_height(tree->left);
	rh = tree_height(tree->right);

	if (abs(lh - rh) > 1)
		return (0);

	return (is_avl_helper(tree->left, min, tree->n) &&
		is_avl_helper(tree->right, tree->n, max));
}

/**
 * binary_tree_is_avl - checks if a binary tree is a valid AVL tree
 * @tree: pointer to the root node
 *
 * Return: 1 if valid AVL, 0 otherwise
 */
int binary_tree_is_avl(const binary_tree_t *tree)
{
	if (!tree)
		return (0);

	return (is_avl_helper(tree, INT_MIN, INT_MAX));
}
