#include "monty.h"

/**
 * error_opcode_not_found - Printing custom error for not found command
 * @l: counter
 * @non_valid_opcode: string
 * @ar: array
 * Return: void
 */
int error_opcode_not_found(unsigned int l, char *non_valid_opcode,
		char **ar)
{
	char *error_str;
	char *l_str = int_to_str(l);
	int size = strlen("L") + strlen(l_str) +
		strlen(": unknown instruction ") + strlen(non_valid_opcode)
		+ strlen("\n") + 1;

	alloc_str(&error_str, size, "error_not_found Error: malloc error");
	strcpy(error_str, "L");
	strcat(error_str, l_str);
	strcat(error_str, ": unknown instruction ");
	strcat(error_str, non_valid_opcode);
	strcat(error_str, "\n\0");

	write(STDERR_FILENO, error_str, strlen(error_str));
	free(error_str);
	free(l_str);
	deallocate_token_array(ar);
	exit(EXIT_FAILURE);
}

/**
 * opcode_error - Printing custom error for not found command
 * @l: counter
 *
 * Return: void
 */
int opcode_error(unsigned int l)
{
	char *error_str;
	char *l_str = int_to_str(l);
	int size = strlen("L") + strlen(l_str) +
		strlen(": usage: push integer") + strlen("\n") + 1;

	alloc_str(&error_str, size, "error_not_found Error: malloc error");
	strcpy(error_str, "L");
	strcat(error_str, l_str);
	strcat(error_str, ": usage: push integer");
	strcat(error_str, "\n\0");

	write(STDERR_FILENO, error_str, strlen(error_str));
	free(error_str);
	free(l_str);
	exit(EXIT_FAILURE);
}

stack_t *top = NULL;

/**
 * main - short description
 *
 * Description: long description
 *
 * @w: argument_1 description
 * @v: argument_2 description
 *
 * Return: return description
 */
int main(int w, char **v)
{
	FILE *file;
	char *line = NULL;
	size_t b = 0;
	ssize_t read = 0;
	unsigned int l = 1;
	char **ar = NULL;

	if (w != 2)
		error_exit("USAGE: monty file\n");
	file = fopen(v[1], "r");
	if (file == NULL)
		file_error(v[1]);
	while ((read = getline(&line, &b, file)) != -1)
	{
		ar = tokenize_str(line, " \n");
		if (ar != NULL &&  ar[0] != NULL)
		{
			if (_instruct(ar))
			{
				if (strcmp(ar[0], "push") == 0)
					if (stackpush_(ar,
								&l, &line, &file))
						continue;
				h_opcode(ar, NULL, l);
			}
			else
			{
				main_end(&line, &file);
				error_opcode_not_found(l, ar[0],
						ar);
			}
		}
		deallocate_token_array(ar);
		l++;
	}
	main_end(&line, &file);
	return (0);
}

/**
 * _instruct - Check if the token array contains a valid opcode.
 * @ar: The token array.
 *
 * Return: 1 if the opcode is valid, 0 otherwise.
 *
 * Description: This function checks if the token array contains a valid opcode
 * by comparing it with the list of supported opcodes in the opcodes array.
 * If the token array is NULL or the first element is NULL, it returns 0.
 * If a valid opcode is found in the token array, it returns 1.
 */

int _instruct(char **ar)
{
	int opcode_index;
	const instruction_t opcodes[] = {
		{"push", push_},
		{"pall", pall_},
		{NULL, NULL}
	};

	if (ar == NULL)
		return (0);
	if (ar[0] == NULL)
		return (0);

	for (opcode_index = 0; opcodes[opcode_index].opcode != NULL;
			opcode_index++)
		if (strcmp(ar[0],
					opcodes[opcode_index].opcode) == 0)
			return (1);
	return (0);
}

/**
 * h_opcode - Handle opcode based on the token array.
 * @ar: The token array.
 * @stack: Pointer to the stack.
 * @l: The current line number.
 *
 * Return: 1 if the opcode is handled, 0 otherwise.
 *
 * Description: This function handles the opcode based on the token array by
 * comparing it with the list of supported opcodes in the opcodes array. If the
 * token array is NULL or the first element is NULL, it returns 0. If a matching
 * opcode is found in the token array, it calls the corresponding function from
 * the opcodes array and passes the stack and line number as arguments. It then
 * returns 1. If no matching opcode is found, it returns 0.
 */

int h_opcode(char **ar,
		stack_t **stack, unsigned int l)
{
	int opcode_index;
	const instruction_t opcodes[] = {
		{"push", push_},
		{"pall", pall_},
		{NULL, NULL}
	};
	if (ar == NULL)
		return (0);
	if (ar[0] == NULL)
		return (0);

	for (opcode_index = 0; opcodes[opcode_index].opcode != NULL;
			opcode_index++)
	{
		if (strcmp(ar[0],
					opcodes[opcode_index].opcode) == 0)
		{
			opcodes[opcode_index].f(stack, l);
			return (1);
		}
	}
	return (0);
}
