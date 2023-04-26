#include "shell.h"

/**
 * env - prints the current_environnement
 * @sh: shell parameters structure
 *
 *Return: void
 */

void env(sh_t *sh __attribute__((unused)))
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		print(environ[i], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}

/**
 * quit - exits the shell
 * @sh: shell parameters structure
 *
 * Return: void
 */

void quit(sh_t *sh)
{
	int num_token = 0, arg;

	for (; sh->current_command[num_token] != NULL; num_token++)
		;
	if (num_token == 1)
	{
		free(sh->current_command);
		free(sh->line);
		free(sh->commands);
		exit(sh->status);
	}
	else if (num_token == 2)
	{
		arg = _atoi(sh->current_command[1]);
		if (arg == -1)
		{
			print(sh->shell_name, STDERR_FILENO);
			print(": 1: exit: Illegal number: ", STDERR_FILENO);
			print(sh->current_command[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			sh->status = 2;
		}
		else
		{
			free(sh->line);
			free(sh->current_command);
			free(sh->commands);
			exit(arg);
		}
	}
	else
		print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}
