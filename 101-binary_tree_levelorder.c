#include "binary_trees.h"

/**
 * enqueue_node - adds a node to the end of a singly linked list
 * @head: a double pointer to the head of the list
 * @node: a pointer to binary_tree_t node
 *
 * Return: nothing
 */
linked_list_t *enqueue_node(linked_list_t *head, binary_tree_t *node)
{
	linked_list_t *new_node = NULL;

	if (head == NULL)
		return (NULL);

	new_node = malloc(sizeof(*new_node));

	if (!new_node)
		return (NULL);

	new_node->tree_node = node;
	new_node->next = NULL;

	if (!head->next)
	{
		head->next = new_node;
		return (new_node);
	}

	while (head->next)
		head = head->next;

	head->next = new_node;
	return (new_node);
}

/**
 * pop_stack - removes the first node in a linked list
 * @head: a double pointer to the start of the list
 *
 * Return: a pointer to binary_tree_t node held in the 'popped' node
 */
binary_tree_t *pop_stack(linked_list_t **head)
{
	binary_tree_t *ptr;
	linked_list_t *temp;

	if (!head || !(*head))
		return (NULL);

	ptr = (*head)->tree_node;

	if ((*head)->next)
	{
		temp = (*head)->next;
		free(*head);
		*head = temp;
	}
	else
	{
		free(*head);
		*head = NULL;
	}

	return (ptr);
}

/**
 * binary_tree_levelorder - prints a binary tree one level at a time
 * @tree: a pointer to the root
 * @func: a pointer to a function for each tree node
 *
 * Return: nothing
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	linked_list_t **head = NULL;
	linked_list_t *new_node;
	binary_tree_t *next_node;

	new_node = malloc(sizeof(*new_node));

	if (!new_node)
		return;

	new_node->tree_node = (binary_tree_t *)tree;
	new_node->next = NULL;
	head = &new_node;

	if (tree->left)
		if (!enqueue_node(*head, tree->left))
			return;
	if (tree->right)
		if (!enqueue_node(*head, tree->right))
			return;

	while (*head)
	{
		next_node = pop_stack(head);
		func(next_node->n);
		if (!*head)
			break;
		next_node = (*head)->tree_node;
		if (next_node->left)
			if (!enqueue_node(*head, next_node->left))
				return;
		if (next_node->right)
			if (!enqueue_node(*head, next_node->right))
				return;
	}
}
