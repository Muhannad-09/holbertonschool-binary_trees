#include "binary_trees.h"

/**
 * binary_tree_is_complete - checks if a binary tree is complete
 * @tree: pointer to the root node of the tree to check
 *
 * Return: 1 if the tree is complete, 0 otherwise
 */
int binary_tree_is_complete(const binary_tree_t *tree)
{
	const binary_tree_t *queue[1024];
	int front = 0, rear = 0;
	int null_found = 0;

	if (!tree)
		return (0);

	queue[rear++] = tree;

	while (front < rear)
	{
		const binary_tree_t *current = queue[front++];

		if (current == NULL)
		{
			null_found = 1;
		}
		else
		{
			if (null_found)
				return (0);
			queue[rear++] = current->left;
			queue[rear++] = current->right;
		}
	}

	return (1);
}
