#include "monty.h"

/**
 * rotr - Rotates the last node
 * @stack: Pointer to a pointer
 * @ln: the line number of of the opcode.
 */
void rotr(stack_t **stack, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;

	tmp = *stack;

	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *stack;
	tmp->prev->next = NULL;
	tmp->prev = NULL;
	(*stack)->prev = tmp;
	(*stack) = tmp;
}

/**
 * rot_fun - Rotates the first node.
 * @stack: Pointer to a pointer
 * @ln: the line number of of the opcode.
 */
void rot_fun(stack_t **stack, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;

	tmp = *stack;
	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *stack;
	(*stack)->prev = tmp;
	*stack = (*stack)->next;
	(*stack)->prev->next = NULL;
	(*stack)->prev = NULL;
}

/**
 * pop_top - node will be added to the stack.
 * @stack: Pointer to a pointer
 * @line_number: the line number of of the opcode.
 */
void pop_top(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL)
		more_err(7, line_number);

	tmp = *stack;
	*stack = tmp->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(tmp);
}


/**
 * print_str - Prints a string.
 * @stack: Pointer to a pointer
 * @ln: the line number of of the opcode.
 */
void str_printing(stack_t **stack, __attribute__((unused))unsigned int ln)
{
	int ascii;
	stack_t *tmp;

	if (stack == NULL || *stack == NULL)
	{
		printf("\n");
		return;
	}

	tmp = *stack;
	while (tmp != NULL)
	{
		ascii = tmp->n;
		if (ascii <= 0 || ascii > 127)
			break;
		printf("%c", ascii);
		tmp = tmp->next;
	}
	printf("\n");
}

/**
 * char_printing - Prints the Ascii value.
 * @stack: Pointer to a pointer
 * @line_number: the line number of of the opcode.
 */
void char_printing(stack_t **stack, unsigned int line_number)
{
	int ascii;

	if (stack == NULL || *stack == NULL)
		string_error(11, line_number);

	ascii = (*stack)->n;
	if (ascii < 0 || ascii > 127)
		string_error(10, line_number);
	printf("%c\n", ascii);
}
