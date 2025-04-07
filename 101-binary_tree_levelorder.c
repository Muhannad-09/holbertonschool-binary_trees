#include "binary_trees.h"

/**
 * binary_tree_levelorder - goes through a binary tree using level-order traversal
 * @tree: pointer to the root node
 * @func: pointer to a function to call for each node
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	linked_list_t *head = NULL, *tail = NULL;
	linked_list_t *new_node;
	binary_tree_t *current;

	if (!tree || !func)
		return;

	/* Enqueue root node */
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return;
	new_node->tree_node = (binary_tree_t *)tree;
	new_node->next = NULL;
	head = tail = new_node;

	while (head)
	{
		current = head->tree_node;
		func(current->n);

		if (current->left)
		{
			new_node = malloc(sizeof(*new_node));
			if (!new_node)
				break;
			new_node->tree_node = current->left;
			new_node->next = NULL;
			tail->next = new_node;
			tail = new_node;
		}
		if (current->right)
		{
			new_node = malloc(sizeof(*new_node));
			if (!new_node)
				break;
			new_node->tree_node = current->right;
			new_node->next = NULL;
			tail->next = new_node;
			tail = new_node;
		}

		new_node = head;
		head = head->next;
		free(new_node);
	}
}
