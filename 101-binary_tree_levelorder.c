#include "binary_trees.h"

/**
 * enqueue_node - adds a node to the end of a singly linked list (queue)
 * @tail: pointer to the current tail of the list
 * @node: pointer to binary_tree_t node to enqueue
 *
 * Return: pointer to the new tail node
 */
linked_list_t *enqueue_node(linked_list_t *tail, binary_tree_t *node)
{
	linked_list_t *new_node = malloc(sizeof(*new_node));

	if (!new_node)
		return (NULL);

	new_node->tree_node = node;
	new_node->next = NULL;

	if (tail)
		tail->next = new_node;

	return new_node;
}

/**
 * pop_stack - removes the first node in a linked list (queue)
 * @head: a double pointer to the start of the list
 *
 * Return: pointer to binary_tree_t node held in the popped node
 */
binary_tree_t *pop_stack(linked_list_t **head)
{
	binary_tree_t *ptr;
	linked_list_t *temp;

	if (!head || !*head)
		return (NULL);

	ptr = (*head)->tree_node;
	temp = (*head)->next;
	free(*head);
	*head = temp;

	return (ptr);
}

/**
 * binary_tree_levelorder - goes through a binary tree using level-order traversal
 * @tree: pointer to the root node of the tree
 * @func: pointer to a function to call for each node
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	linked_list_t *head = NULL, *tail = NULL;
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
		current = pop_stack(&head);
		func(current->n);

		if (current->left)
			tail = enqueue_node(tail, current->left);
		if (current->right)
			tail = enqueue_node(tail, current->right);

		
		if (!head)
			tail = NULL;
	}
}
