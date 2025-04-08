#include "binary_trees.h"

/**
 * binary_tree_is_complete - checks if a binary tree is complete
 * @tree: pointer to the root node
 *
 * Return: 1 if complete, 0 otherwise
 */
int binary_tree_is_complete(const binary_tree_t *tree)
{
	const binary_tree_t **queue;
	size_t front = 0, rear = 0, size = 1024;
	int encountered_null = 0;

	if (!tree)
		return (0);

	queue = malloc(sizeof(binary_tree_t *) * size);
	if (!queue)
		return (0);

	queue[rear++] = tree;

	while (front < rear)
	{
		const binary_tree_t *current = queue[front++];

		if (!current)
			encountered_null = 1;
		else
		{
			if (encountered_null)
			{
				free(queue);
				return (0);
			}
			queue[rear++] = current->left;
			queue[rear++] = current->right;
		}
	}

	free(queue);
	return (1);
}

/**
 * is_max_heap - checks the max-heap property recursively
 * @tree: pointer to the root node
 *
 * Return: 1 if valid max-heap, 0 otherwise
 */
int is_max_heap(const binary_tree_t *tree)
{
	if (!tree)
		return (1);

	if (tree->left)
	{
		if (tree->n < tree->left->n || !is_max_heap(tree->left))
			return (0);
	}
	if (tree->right)
	{
		if (tree->n < tree->right->n || !is_max_heap(tree->right))
			return (0);
	}

	return (1);
}

/**
 * binary_tree_is_heap - checks if a binary tree is a valid max binary heap
 * @tree: pointer to the root node
 *
 * Return: 1 if valid heap, 0 otherwise
 */
int binary_tree_is_heap(const binary_tree_t *tree)
{
	if (!tree)
		return (0);

	if (!binary_tree_is_complete(tree))
		return (0);

	return (is_max_heap(tree));
}
