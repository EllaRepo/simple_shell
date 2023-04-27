#include "shell.h"
/**
 * _loop - loops the functions in utils and helpers
 * @sh: shell parameter list
 *
 * Return: None
 */
void _loop(sh_t *sh)
{
	int i;
	size_t n = 0;

	if (getline(&sh->line, &n, stdin) == -1)
	{
		free(sh->line);
		free_env(sh);
		exit(sh->status);
	}
	remove_newline(sh->line);
	remove_comment(sh->line);
	if (chk_syntax_err(sh))
		return;
	sh->commands = tokenizer(sh->line, ";");
	for (i = 0; sh->commands[i] != NULL; i++)
	{
		sh->current_command = tokenizer(sh->commands[i], " \t");
		if (sh->current_command[0] == NULL)
		{
			free(sh->current_command);
			break;
		}
		sh->cmd_type = parse_command(sh->current_command[0]);
		initializer(sh);
		free(sh->current_command);
	}
	free(sh->commands);
}
/**
 * shell_loop - loops the functions in utils and helpers
 * @sh: shell parameter list
 *
 * Return: None
 */
void shell_loop(sh_t *sh)
{
	while (1)
	{
		print("($) ", STDOUT_FILENO);
		_loop(sh);
	}
}
