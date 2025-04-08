#include "binary_trees.h"

/**
 * heap_extract - Extracts the root node of a Max Binary Heap
 * @root: Double pointer to the root node
 *
 * Return: Value stored in the root node, or 0 on failure
 */
int heap_extract(heap_t **root)
{
	heap_t *last, *tmp;
	int value, size, level;

	if (!root || !*root)
		return (0);

	value = (*root)->n;
	size = binary_tree_size(*root);
	if (size == 1)
	{
		free(*root);
		*root = NULL;
		return (value);
	}

	last = *root;
	for (level = 1 << (31 - __builtin_clz(size)); level > 1; level >>= 1)
	{
		if (size & level)
			last = last->right;
		else
			last = last->left;
	}

	(*root)->n = last->n;
	tmp = last->parent;
	if (tmp->left == last)
		tmp->left = NULL;
	else
		tmp->right = NULL;
	free(last);

	tmp = *root;
	while (1)
	{
		heap_t *largest = tmp;
		if (tmp->left && tmp->left->n > largest->n)
			largest = tmp->left;
		if (tmp->right && tmp->right->n > largest->n)
			largest = tmp->right;
		if (largest == tmp)
			break;
		value = tmp->n;
		tmp->n = largest->n;
		largest->n = value;
		tmp = largest;
	}

	return ((*root)->n);
}
