#include "monty.h"

/**
 * read_file - reads a file
 * @fd: pointer to file descriptor
 * Return: void
 */

void read_file(FILE *fd)
{
	int line_number, format = 0;
	char *buffer = NULL;
	size_t len = 0;

	for (line_number = 1; getline(&buffer, &len, fd) != -1; line_number++)
	{
		format = line_parsing(buffer, line_number, format);
	}
	free(buffer);
}

/**
 * find_func - finds function for the opcode
 * @opcode: opcode
 * @value: argument of opcode
 * @format:  storage format.
 * @ln: line number.
 * Return: void
 */
void find_func(char *opcode, char *value, int ln, int format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", add_to_stack},
		{"pall", print_stack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop_fun},
		{"swap", node_swaping},
		{"add", add_n},
		{"sub", sub_n},
		{"div", div_n},
		{"mul", mul_n},
		{"mod", mod_nodes},
		{"pchar", char_printing},
		{"pstr", str_printing},
		{"rotl", rot_fun},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			fun_calling(func_list[i].f, opcode, value, ln, format);
			flag = 0;
		}
	}
	if (flag == 1)
		pri_err(3, ln, opcode);
}
