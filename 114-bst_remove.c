#include "binary_trees.h"
#include <stdlib.h>

/**
 * min_value_node - gets the minimum value node from a BST
 * @node: subtree root
 *
 * Return: pointer to the minimum value node
 */
bst_t *min_value_node(bst_t *node)
{
	while (node && node->left)
		node = node->left;
	return (node);
}

/**
 * bst_remove - removes a node from a BST
 * @root: pointer to the root node of the tree
 * @value: value to remove
 *
 * Return: pointer to the new root node after deletion
 */
bst_t *bst_remove(bst_t *root, int value)
{
	bst_t *temp;

	if (!root)
		return (NULL);

	if (value < root->n)
		root->left = bst_remove(root->left, value);
	else if (value > root->n)
		root->right = bst_remove(root->right, value);
	else
	{
		if (!root->left)
		{
			temp = root->right;
			if (temp)
				temp->parent = root->parent;
			free(root);
			return (temp);
		}
		else if (!root->right)
		{
			temp = root->left;
			if (temp)
				temp->parent = root->parent;
			free(root);
			return (temp);
		}

		temp = min_value_node(root->right);
		root->n = temp->n;
		root->right = bst_remove(root->right, temp->n);
	}

	return (root);
}
