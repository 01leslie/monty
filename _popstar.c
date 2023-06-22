#include "monty.h"

void add(stack_t **stack, unsigned int l)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't add, stack too short\n", l);
        exit(EXIT_FAILURE);
    }

    (*stack)->next->n += (*stack)->n;
    pop(stack, l);
}

void pop(stack_t **stack, unsigned int l)
{
    stack_t *tmp;

    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pop an empty stack\n", l);
        exit(EXIT_FAILURE);
    }

    tmp = *stack;
    *stack = (*stack)->next;
    if (*stack != NULL)
        (*stack)->prev = NULL;
    free(tmp);
}

void pall(stack_t **stack, unsigned int l)
{
    stack_t *current = *stack;

    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}

int monty()
{
    stack_t *stack = NULL;
    instruction_t instruction;

 
    instruction.opcode = "push";
    instruction.f = NULL;
    stack_t *new_node = malloc(sizeof(stack_t));
    new_node->n = 1;
    new_node->prev = NULL;
    new_node->next = NULL;
    stack = new_node;

    new_node = malloc(sizeof(stack_t));
    new_node->n = 2;
    new_node->prev = stack;
    new_node->next = NULL;
    stack->next = new_node;

    instruction.opcode = "add";
    instruction.f = &add;
    instruction.f(&stack, 3);

    instruction.opcode = "pall";
    instruction.f = &pall;
    instruction.f(&stack, 5)
    stack = NULL;
    new_node = malloc(sizeof(stack_t));
    new_node->n = 1;
    new_node->prev = NULL;
    new_node->next = NULL;
    stack = new_node;

    new_node = malloc(sizeof(stack_t));
    new_node->n = 2;
    new_node->prev = stack;
    new_node->next = NULL;
    stack->next = new_node;

    instruction.opcode = "add";
    instruction.f = &add;
    instruction.f(&stack, 3);

    instruction.opcode = "pall";
    instruction.f = &pall;
    instruction.f(&stack, 5);

    return 0;
}
