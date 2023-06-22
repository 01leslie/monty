#include "monty.h"

/**
 * deallocate_linked_list - Deallocate memory for the linked list.
 *
 * Description: This function deallocates the memory allocated for the linked list.
 * It starts by setting the pointer 's' to point to the top of the linked list.
 * It then iterates through the linked list, assigning the next node to 's' and
 * freeing the current node pointed to by 'p'. This process continues until 's'
 * becomes NULL, indicating the end of the linked list. By freeing each node, the
 * memory allocated for the linked list is properly deallocated.
 */

void deallocate_linked_list(void)
{
	stack_t *s;
	stack_t *p;

	s = top;
	while (s)
	{
		p = s;
		s = s->next;
		free(p);
	}
}

/**
 * deallocate_token_array - Deallocate memory for a token array.
 * @ar: The token array to be deallocated.
 *
 * Description: This function deallocates the memory allocated for a token array.
 * It iterates through the array using the index variable 'index' and frees each
 * individual token by calling free(ar[index]). After freeing all the tokens, it
 * frees the memory allocated for the array itself by calling free(ar).
 */

void deallocate_token_array(char **ar)
{
	int index;

	for (index = 0; ar[index]; index++)
		free(ar[index]);
	free(ar);
}

/**
 * stackpush_ - Perform stack push operation.
 * @ar: The token array containing the push opcode and argument.
 * @l: Pointer to the line number.
 * @line: Pointer to the line buffer.
 * @file: Pointer to the file pointer.
 *
 * Return: 1 if successful, 0 otherwise.
 *
 * Description: This function performs the stack push operation. It creates a new
 * node of type stack_t and assigns it the value specified in the argument of the
 * push opcode. It then calls the h_opcode() function to handle the opcode with the
 * token array and the new node. If the push operation is successful, the token array
 * is deallocated and the line number is incremented. If the push operation fails,
 * the token array is deallocated, the line buffer and file are freed, and an opcode
 * error is raised.
 */

int stackpush_(char **ar, unsigned int *l,
		char **line, FILE **file)
{
	stack_t *new_node;

	new_node = (stack_t *) malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		deallocate_token_array(ar);
		main_end(line, file);
		error_exit("Error: malloc failed\n");
	}
	if (ar[1] != NULL)
	{
		if (!_num(ar[1]))
		{
			deallocate_token_array(ar);
			main_end(line, file);
			opcode_error(*l);
		}
		new_node->n = atoi(ar[1]);
		new_node->prev = NULL;
		new_node->next = NULL;
		h_opcode(ar, &new_node, *l);
		deallocate_token_array(ar);
		ar = NULL;
		*l = *l + 1;
		return (1);
	}
	else
	{
		deallocate_token_array(ar);
		main_end(line, file);
		opcode_error(*l);
	}
	return (0);
}

/**
 * error_exit - Printing custom error for not found command
 * @error_message: command-line args
 *
 * Return: void
 */
int error_exit(char *e)
{
	int size = strlen(e);

	write(STDERR_FILENO, e, size);
	exit(EXIT_FAILURE);
}

/**
 * file_error - Printing custom error for not found command
 * @file_name: counter
 *
 * Return: void
 */
int file_error(char *file_name)
{
	char *error_str;
	int size = strlen("Error: Can't open file ") +
		strlen(file_name) + strlen("\n") + 1;

	alloc_str(&error_str, size, "error_not_found Error: malloc error");
	strcpy(error_str, "Error: Can't open file ");
	strcat(error_str, file_name);
	strcat(error_str, "\n\0");

	write(STDERR_FILENO, error_str, strlen(error_str));
	free(error_str);
	exit(EXIT_FAILURE);
}
