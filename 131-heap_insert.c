#include "binary_trees.h"

/**
 * binary_tree_size - measures the size of a binary tree
 * @tree: pointer to the root node
 * Return: size or 0 if NULL
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
	if (!tree)
		return (0);
	return (1 + binary_tree_size(tree->left) + binary_tree_size(tree->right));
}

/**
 * heap_insert - inserts a value into a Max Binary Heap
 * @root: double pointer to root node
 * @value: value to insert
 * Return: pointer to inserted node or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	size_t size, mask;
	heap_t *parent, *new_node;
	int temp;

	if (!root)
		return (NULL);

	if (!*root)
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
		new_node = parent->right = binary_tree_node(parent, value);
	else
		new_node = parent->left = binary_tree_node(parent, value);

	if (!new_node)
		return (NULL);

	while (new_node->parent && new_node->n > new_node->parent->n)
	{
		temp = new_node->n;
		new_node->n = new_node->parent->n;
		new_node->parent->n = temp;
		new_node = new_node->parent;
	}

	return (new_node);
}
