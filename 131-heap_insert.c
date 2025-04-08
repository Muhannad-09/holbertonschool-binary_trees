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
 * get_insertion_parent - finds the parent where new node should be inserted
 * @root: pointer to root
 * @size: total nodes + 1 (where to insert)
 * Return: pointer to parent node
 */
heap_t *get_insertion_parent(heap_t *root, size_t size)
{
	size_t mask;
	heap_t *parent = root;

	mask = 1UL << (sizeof(size_t) * 8 - __builtin_clzll(size) - 2);
	while (mask > 1)
	{
		if (size & mask)
			parent = parent->right;
		else
			parent = parent->left;
		mask >>= 1;
	}
	return (parent);
}

/**
 * bubble_up - swaps node with parents until heap condition is restored
 * @node: pointer to inserted node
 * Return: pointer to final node
 */
heap_t *bubble_up(heap_t *node)
{
	int tmp;

	while (node->parent && node->n > node->parent->n)
	{
		tmp = node->n;
		node->n = node->parent->n;
		node->parent->n = tmp;
		node = node->parent;
	}
	return (node);
}

/**
 * heap_insert - inserts a value into a Max Binary Heap
 * @root: double pointer to root node
 * @value: value to insert
 * Return: pointer to inserted node or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	size_t size;
	heap_t *parent, *new_node;

	if (!root)
		return (NULL);

	if (!*root)
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}

	size = binary_tree_size(*root) + 1;
	parent = get_insertion_parent(*root, size);

	if (size & 1)
		new_node = parent->right = binary_tree_node(parent, value);
	else
		new_node = parent->left = binary_tree_node(parent, value);

	if (!new_node)
		return (NULL);

	return (bubble_up(new_node));
}
