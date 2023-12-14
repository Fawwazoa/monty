#include "monty.h"

/**
 * openf - opens file
 * @file_name: file name
 * Return: void
 */

void openf(char *file_name)
{
	FILE *f = fopen(file_name, "r");

	if (file_name == NULL || f == NULL)
		merr(2, file_name);
	readf(f);
	fclose(f);
}



/**
 * readf - reads file
 * @fd: file desciptor
 * Return: void
 */

void readf(FILE *fd)
{
	int ln, format = 0 ;
	char *buffer = NULL;
	size_t len = 0;

	for (ln = 1; getline(&buffer, &len, fd) != -1; ln++){
		format = pline(buffer, ln, format);
	}
	free(buffer);

}
void cfun(op_func func, char *op, char *val, int ln, int format)
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
			merr(5, ln);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				merr(5, ln);
		}
		node = crnode(atoi(val) * flag);
		if (format == 0)
			func(&node, ln);
		if (format == 1)
			add2queue(&node, ln);
	}
	else
		func(&head, ln);
}

void ffunc(char *opcode, char *value, int ln, int format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", add2stack},
		{"pall", pstack},
		{"pint", prtop},
		{"pop", poptop},
		{"nop", nop},
		{"swap", snodes},
		{"add", anodes},
		{"sub", snodes},
		{"div", dnodes},
		{"mul", mulnodes},
		{"mod", modnodes},
		{"pchar", prchar},
		{"pstr", prstr},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			cfun(func_list[i].f, opcode, value, ln, format);
			flag = 0;
		}
	}
	if (flag == 1)
		merr(3, ln, opcode);
}

int pline(char *buffer, int line_number, int format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buffer == NULL)
		merr(4);

	opcode = strtok(buffer, delim);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	ffunc(opcode, value, line_number, format);
	return (format);
}
