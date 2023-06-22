#include "monty.h"

/**
 * alloc_str - Allocate memory for a string.
 * @string: Pointer to the string.
 * @size_of_malloc: Size of memory to be allocated.
 * @e: Error message in case of failure.
 *
 * Return: Pointer to the allocated string if successful, NULL otherwise.
 *
 * Description: This function allocates memory for a string of size size_of_malloc.
 * If the allocation fails, it prints the error message e using perror() and returns
 * NULL. Otherwise, it assigns the allocated memory to the pointer string and returns
 * the pointer.
 */

char *alloc_str(char **string, size_t size_of_malloc, char *e)
{
	*string = (char *) malloc(sizeof(char) * size_of_malloc);
	if (string == NULL)
	{
		perror(e);
		return (NULL);
	}
	return (*string);
}

/**
 * _tokens_counter - Count the number of tokens in an array.
 * @ar: The array of tokens.
 *
 * Return: The number of tokens in the array.
 *
 * Description: This function counts the number of tokens in the array by iterating
 * through the array until it reaches a NULL element and incrementing a counter.
 * It then returns the final count.
 */

int _tokens_counter(char **ar)
{
	int count = 0;

	while (ar[count])
		count++;
	return (count);
}

/**
 * alloc_array - Allocate memory for an array of strings.
 * @array: Pointer to the array.
 * @size_of_malloc: Size of memory to be allocated.
 * @e: Error message in case of failure.
 *
 * Return: Pointer to the allocated array if successful, NULL otherwise.
 *
 * Description: This function allocates memory for an array of strings of size
 * size_of_malloc. If the allocation fails, it prints the error message e using
 * perror() and returns NULL. Otherwise, it assigns the allocated memory to the
 * pointer array and returns the pointer.
 */

char **alloc_array(char **array, size_t size_of_malloc, char *e)
{
	array = (char **) malloc(sizeof(char *) * size_of_malloc);
	if (array == NULL)
	{
		perror(e);
		return (NULL);
	}
	return (array);
}
