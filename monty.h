#define MONTY_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern stack_t *top;

char *alloc_str(char **string, size_t size_of_malloc, char *e);
char **alloc_array(char **array, size_t size_of_malloc, char *e);
int _tokens_counter(char **ar);
int _instruct(char **ar);
int h_opcode(char **ar,
		stack_t **stack, unsigned int l);
int main(int w, char **v);
int error_exit(char *e);
int file_error(char *file_name);
int error_opcode_not_found(unsigned int l, char *non_valid_opcode,
		char **ar);
int opcode_error(unsigned int l);
void invert_str(char *str);
char *int_to_str(int m);
int stackpush_(char **ar, unsigned int *l,
		char **line, FILE **file);
void push_(stack_t **stack,
		__attribute((unused)) unsigned int l);
void pr_num(int l);
void pall_(__attribute((unused)) stack_t **stack,
		__attribute((unused)) unsigned int l);
void deallocate_linked_list(void);
void deallocate_token_array(char **ar);
void main_end(char **line, FILE **file);
int _num(char *num);
size_t count_tok(char *input, char *delimiter);
char **tokenize_str(char *input, char *delimiter);
void swap_(stack_t **stack, unsigned int l);
void pop_(stack_t **stack, unsigned int l);
