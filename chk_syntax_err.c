#include "shell.h"

/**
 * start_char - finds index of the first char
 * @line: input string
 * @index: index
 *
 * Return: -1 if there is an error
 *          0 in other case
 */
int start_char(char *line, int *index)
{
	for (*index = 0; line[*index]; *index += 1)
	{
		if (line[*index] == ' ' || line[*index] == '\t')
			continue;

		if (line[*index] == ';')
			return (-1);

		break;
	}

	return (0);
}
/**
 * print_syntax_err - prints syntax error
 * @sh: shell parameter structure
 * @index: index of the error
 *
 * Return: None
 */
void print_syntax_err(sh_t *sh, int index)
{
	char *err = ": syntax error near unexpected token ";

	print(sh->shell_name, STDERR_FILENO);
	print(err, STDERR_FILENO);
	print("`;", STDERR_FILENO);
	if (sh->line[index + 1] == ';')
		print(";", STDERR_FILENO);
	print("'\n", STDERR_FILENO);
	sh->status = 2;
	if (sh->line)
		free(sh->line);
	sh->line = NULL;
}
/**
 * check_reapeted_sep - prints syntax error
 * @sh: shell parameter structure
 * @index: index of the error
 *
 * Return: -1 if sep is repeated
 *          0 if not
 */
int check_reapeted_sep(sh_t *sh, int *index)
{
	for (*index = 0; sh->line[*index]; *index += 1)
	{
		if (sh->line[*index] == ';' && sh->line[*index + 1] == ';')
			return (-1);
	}
	return (0);
}
/**
 * chk_syntax_err - checks syntax error and prints
 * @sh: shell parameter structure
 *
 * Return: 1 if error found
 *         0 if not
 */
int chk_syntax_err(sh_t *sh)
{
	int index = 0, i;

	i = start_char(sh->line, &index);
	if (i == -1)
	{
		print_syntax_err(sh, index);
		return (1);
	}
	i = check_reapeted_sep(sh, &index);
	if (i == -1)
	{
		print_syntax_err(sh, index);
		return (1);
	}
	return (0);
}
