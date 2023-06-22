#include "monty.h"

/**
 * push_ - Pushes an element onto the stack.
 * @stack: Pointer to the top of the stack.
 * @l: Unused parameter.
 *
 * Description: This function is responsible for pushing an element onto the stack.
 * If the stack is empty, the element becomes the top of the stack.
 * Otherwise, the element is inserted at the top, and the previous top is updated accordingly.
 */

void push_(stack_t **stack,
		__attribute((unused)) unsigned int l)
{
	if (top == NULL)
	{
		top = *stack;
		return;
	}
	else
	{
		(*stack)->next = top;
		top->prev = *stack;
		top = *stack;
		return;
	}
}

/**
 * pall_ - Prints all the elements in the stack.
 * @stack: Pointer to the top of the stack.
 * @l: Unused parameter.
 *
 * Description: This function prints all the elements in the stack.
 * It starts from the top and traverses through the stack, printing each element.
 */

void pall_(__attribute((unused)) stack_t **stack,
		__attribute((unused)) unsigned int l)
{
	stack_t *s;

	s = top;
	while (s)
	{
		pr_num(s->n);
		s = s->next;
	}
}

/**
 * pr_num - Print a number to the standard output.
 * @l: The number to be printed.
 *
 * Description: This function converts the given number to a string using the int_to_str()
 * function. It then allocates memory for a new string to hold the number and a new line
 * character. The number string is copied into the new string, followed by the new line
 * character. Finally, the new string is written to the standard output using the write()
 * function, and the allocated memory is freed.
 */

void pr_num(int l)
{
	char *number_str = int_to_str(l);
	char *str;
	int size = strlen(number_str) + strlen("\n\0");

	str = (char *) malloc(sizeof(char) + size);
	if (str == NULL)
	{
		printf("malloc\n");
		exit(EXIT_FAILURE);
	}
	strcpy(str, number_str);
	strcat(str, "\n\0");
	write(STDOUT_FILENO, str, strlen(str));
	free(number_str);
	free(str);
}

/**
 * count_tok - Counts the number of tokens in a string.
 * @input: Input string to tokenize.
 * @delimiter: Delimiter used for tokenization.
 *
 * Description: This function counts the number of tokens in a string by splitting it
 * based on the specified delimiter. It uses strtok() to extract each token and keeps
 * track of the count. The function returns the total number of tokens found.
 */

size_t count_tok(char *input, char *delimiter)
{
	char *t;
	size_t c;

	c = 0;
	t = strtok(input, delimiter);
	while (t != NULL)
	{
		c++;
		t = strtok(NULL, delimiter);
	}
	return (c);
}

/**
 * tokenize_str - Tokenizes a string based on a delimiter.
 * @input: Input string to tokenize.
 * @delimiter: Delimiter used for tokenization.
 *
 * Description: This function tokenizes a string by splitting it into individual tokens
 * based on the specified delimiter. It allocates memory for the token array and copies
 * each token into the array. The function returns the token array.
 */

char **tokenize_str(char *input, char *delimiter)
{
	char *h, *t;
	char **ar;
	size_t c, i, f;

	ar = NULL;
	alloc_str(&h, strlen(input) + 1,
			"tokenize_str() Error: h maoloc failure");
	strcpy(h, input);
	c = count_tok(h, delimiter);
	ar = alloc_array(ar, c + 1,
			"tokenize_str() Error: ar** maoloc failure");
	strcpy(h, input);
	t = strtok(h, delimiter);
	for (i = 0; i < c; i++)
	{
		ar[i] = (char *) malloc(sizeof(char) *
				strlen(t) + 1);
		if (ar[i] == NULL)
		{
			for (f = 0;
					f < i;
					f++)
				free(ar[f]);
			free(h);
			free(ar);
			perror("tokenize_str() Error: ar maoloc failure");
			return (NULL);
		}
		strcpy(ar[i], t);
		t = strtok(NULL, delimiter);
	}
	free(h);
	ar[c] = NULL;
	return (ar);
}
