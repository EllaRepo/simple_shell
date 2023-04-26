#include "shell.h"

/**
 * non_interactive - handles non_interactive mode
 * @sh: shell parameters structure
 * Return: void
 */

void non_interactive(sh_t *sh)
{
	int i;
	size_t n = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&sh->line, &n, stdin) != -1)
		{
			remove_newline(sh->line);
			remove_comment(sh->line);
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
		free(sh->line);
		free_env(sh);
		exit(sh->status);
	}
}
