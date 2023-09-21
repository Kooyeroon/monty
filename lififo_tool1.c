#include "monty.h"

/**
 * node_swaping - top two elements of the stack will be swaped.
 * @stack: Pointer to a pointer
 * @line_number: the line number of of the opcode.
 */
void node_swaping(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "swap");
	tmp = (*stack)->next;
	(*stack)->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = *stack;
	tmp->next = *stack;
	(*stack)->prev = tmp;
	tmp->prev = NULL;
	*stack = tmp;
}

/**
 * file_opening - opens a file
 * @file_name: the file namepath
 * Return: void
 */

void file_opening(char *file_name)
{
	FILE *fd = fopen(file_name, "r");

	if (file_name == NULL || fd == NULL)
		pri_err(2, file_name);

	read_file(fd);
	fclose(fd);
}


/**
 * nop - Does nothing.
 * @stack: Pointer to a pointer
 * @line_number: the line number of of the opcode.
 */
void nop_fun(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

/**
 * line_parsing - Separates
 * @buffer: line from the give file
 * @line_number: line number
 * @format:  storage format.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */

int line_parsing(char *buffer, int line_number, int format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buffer == NULL)
		pri_err(4);

	opcode = strtok(buffer, delim);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	find_func(opcode, value, line_number, format);
	return (format);
}

/**
 * fun_calling - Calls the function.
 * @func: Pointer to the function
 * @op: string intems opsode
 * @val: string interms of a numeric value.
 * @ln: line numeber
 * @format: Format specifier.
 */
void fun_calling(op_func func, char *op, char *val, int ln, int format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			pri_err(5, ln);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				pri_err(5, ln);
		}
		node = create_node(atoi(val) * flag);
		if (format == 0)
			func(&node, ln);
		if (format == 1)
			add_to_queue(&node, ln);
	}
	else
		func(&head, ln);
}
