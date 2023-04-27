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
			if (chk_syntax_err(sh))
				continue;
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
/**
 * _exec_cmd_from_file - handles file as input
 * @sh: shell parameters structure
 *
 * Return: void
 */
void _exec_cmd_from_file(sh_t *sh)
{
	int i;

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
 * exec_cmd_from_file - handles file as input
 * @sh: shell parameters structure
 * Return: void
 */
void exec_cmd_from_file(sh_t *sh)
{
	int i, fd;
	char *err, t, buff[BUFSIZE], *line;

	fd = open(sh->filename, O_RDONLY);
	if (fd == -1)
	{
		err = ": 0: Can't open ";
		print(sh->shell_name, STDERR_FILENO);
		print(err, STDERR_FILENO);
		print(sh->filename, STDERR_FILENO);
		print("\n", STDERR_FILENO);
		exit(127);
	}
	i = 0;
	while (read(fd, &t, 1) > 0)
	{
		buff[i] = t;
		if (t == '\n')
		{
			buff[i + 1] = '\0';
			line = buff;
			sh->line = _strdup(line);
			_exec_cmd_from_file(sh);
			free(sh->line);
			i = -1;
		}
		i++;
	}
	close(fd);
	free_env(sh);
	exit(sh->status);
}
