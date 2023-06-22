#include "monty.h"

/**
 * invert_str - Inverts the order of characters in a string.
 * @str: Input string to invert.
 *
 * Description: This function reverses the order of characters in a string.
 * It swaps the characters from the beginning and end of the string until
 * the midpoint is reached.
 */

void invert_str(char *str)
{
	int i, len;
	char tmp;

	len = 0;
	while (str[len] != '\0')
		len++;
	len--;
	for (i = 0; i < len; i++, len--)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
	}
}

/**
 * int_to_str - Converts an integer to a string.
 * @m: Integer to convert.
 *
 * Description: This function converts an integer to a string representation.
 * It dynamically allocates memory for the resulting string and performs
 * the conversion digit by digit. The resulting string is then inverted.
 * The function returns the converted string.
 */

char *int_to_str(int m)
{
	char *str = malloc(sizeof(char) * (32 + 1));
	int i = 0;
	int neg = 0;

	if (m < 0)
	{
		neg = 1;
		m = -(m);
	}
	do {
		str[i++] = m % 10 + '0';
		m /= 10;
	} while (m > 0);

	if (neg)
	{
		str[i] = '-';
		i++;
	}
	str[i] = '\0';
	invert_str(str);

	return (str);
}

/**
 * _num - Check if a string represents a valid number.
 * @num: The string to be checked.
 *
 * Description: This function checks if the given string represents a valid number.
 * It first checks if the string is empty, in which case it returns 0. If the string
 * starts with a negative or positive sign, it advances the pointer to the next
 * character. If the string is now empty, it returns 0.
 *
 * The function then checks if the string starts with a '0'. If it does, it checks
 * if the next character is the null terminator, in which case it returns 1 since
 * '0' is a valid number. Otherwise, it returns 0 because a valid number should not
 * have leading zeros.
 *
 * Finally, the function iterates through the remaining characters of the string.
 * If any character is not a digit, it returns 0. If a '0' is encountered and the
 * next character is not the null terminator, it returns 0 because a valid number
 * should not have leading zeros. If all characters pass the checks, it returns 1,
 * indicating that the string represents a valid number.
 */

int _num(char *num)
{
	if (*num == '\0')
		return (0);

	if (*num == '-' || *num == '+')
	{
		num++;
		if (*num == '\0')
			return (0);
	}

	if (*num == '0')
		return (num[1] == '\0');

	while (*num != '\0')
	{
		if (!isdigit(*num))
			return (0);
		if (*num == '0' && *(num + 1) != '\0')
			return (0);
		num++;
	}
	return (1);
}

/**
 * main_end - Perform cleanup operations at the end of the program.
 * @line: Pointer to the line buffer.
 * @file: Pointer to the file pointer.
 *
 * Description: This function is responsible for performing cleanup operations at
 * the end of the program. It calls the deallocate_linked_list() function to free
 * the memory allocated for the linked list. It also closes the file pointed to by
 * the file pointer using the fclose() function. Finally, it frees the memory
 * allocated for the line buffer using the free() function.
 */

void main_end(char **line, FILE **file)
{
	deallocate_linked_list();
	fclose(*file);
	free(*line);
}
