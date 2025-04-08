#include "binary_trees.h"

/**
 * heap_insert - inserts a value into a Max Binary Heap
 * @root: double pointer to the root node of the Heap
 * @value: value to store in the node to be inserted
 *
 * Return: pointer to the created node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	size_t size = 0, mask;
	heap_t *parent, *new_node;
	int tmp;

	if (!root)
		return (NULL);

	if (*root == NULL)
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}

	size = binary_tree_size(*root) + 1;
	mask = 1UL << (sizeof(size_t) * 8 - __builtin_clzll(size) - 2);
	parent = *root;

	while (mask > 1)
	{
		if (size & mask)
			parent = parent->right;
		else
			parent = parent->left;
		mask >>= 1;
	}

	if (size & 1)
		parent->right = binary_tree_node(parent, value);
	else
		parent->left = binary_tree_node(parent, value);

	new_node = (size & 1) ? parent->right : parent->left;

	while (new_node->parent && new_node->n > new_node->parent->n)
	{
		tmp = new_node->n;
		new_node->n = new_node->parent->n;
		new_node->parent->n = tmp;
		new_node = new_node->parent;
	}

	return (new_node);
}
