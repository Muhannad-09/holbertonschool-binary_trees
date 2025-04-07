#include "binary_trees.h"

/**
 * enqueue - create and enqueue a node into the queue
 * @tail: pointer to the current tail
 * @node: binary tree node to enqueue
 *
 * Return: new tail, or NULL on failure
 */
linked_list_t *enqueue(linked_list_t *tail, binary_tree_t *node)
{
	linked_list_t *new = malloc(sizeof(*new));

	if (!new)
		return (NULL);

	new->tree_node = node;
	new->next = NULL;

	if (tail)
		tail->next = new;

	return (new);
}

/**
 * process_children - enqueue left and right children of a node
 * @current: current binary tree node
 * @tail: pointer to current tail of queue
 *
 * Return: updated tail pointer
 */
linked_list_t *process_children(binary_tree_t *current, linked_list_t *tail)
{
	if (current->left)
		tail = tail ? enqueue(tail, current->left) : NULL;
	if (current->right)
		tail = tail ? enqueue(tail, current->right) : NULL;

	return (tail);
}

/**
 * binary_tree_levelorder - level-order traversal of binary tree
 * @tree: pointer to the root node
 * @func: function to call for each node
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	linked_list_t *head = NULL, *tail = NULL, *temp;
	binary_tree_t *current;

	if (!tree || !func)
		return;

	head = malloc(sizeof(*head));
	if (!head)
		return;

	head->tree_node = (binary_tree_t *)tree;
	head->next = NULL;
	tail = head;

	while (head)
	{
		current = head->tree_node;
		func(current->n);
		tail = process_children(current, tail);

		temp = head;
		head = head->next;
		free(temp);

		if (!head)
			tail = NULL;
	}
}
