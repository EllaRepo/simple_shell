#include "shell.h"

/**
 * cd_error - error message for cd
 * @sh: shell parameters structure
 *
 * Return: None
 */
void cd_error(sh_t *sh)
{
	char *err;

	err = " : 1 : can not cd to ";
	print(sh->shell_name, STDERR_FILENO);
	print(err, STDERR_FILENO);
	print(sh->current_command[1], STDERR_FILENO);
	print("\n", STDERR_FILENO);
}
