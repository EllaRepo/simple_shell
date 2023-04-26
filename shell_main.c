#include "shell.h"

/**
 * init - initializes shell parameters
 * @sh: shell parameters structure
 * @argv: argument vector
 *
 * Return: None
*/
void init(sh_t *sh, char **argv)
{
	unsigned int i;

	sh->commands = NULL;
	sh->line = NULL;
	sh->current_command = NULL;
	sh->shell_name = argv[0];
	sh->cmd_type = 0;
	sh->status = 0;
	for (i = 0; environ[i]; i++)
		;
	sh->envp = malloc(sizeof(char *) * (i + 1));
	for (i = 0; environ[i]; i++)
		sh->envp[i] = _strdup(environ[i]);
	sh->envp[i] = NULL;
}

/**
 * main - the main shell code
 * @argc: number of arguments passed
 * @argv: program arguments to be parsed
 *
 * applies the functions in utils and helpers
 * implements EOF
 * Prints error on Failure
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char **argv)
{
	sh_t sh;
	int i;
	size_t n = 0;

	signal(SIGINT, ctrl_c_handler);
	init(&sh, argv);
	while (1)
	{
		non_interactive(&sh);
		print("($) ", STDOUT_FILENO);
		if (getline(&sh.line, &n, stdin) == -1)
		{
			free(sh.line);
			exit(sh.status);
		}
		remove_newline(sh.line);
		remove_comment(sh.line);
		if (chk_syntax_err(&sh))
			continue;
		sh.commands = tokenizer(sh.line, ";");
		for (i = 0; sh.commands[i] != NULL; i++)
		{
			sh.current_command = tokenizer(sh.commands[i], " \t");
			if (sh.current_command[0] == NULL)
			{
				free(sh.current_command);
				break;
			}
			sh.cmd_type = parse_command(sh.current_command[0]);
			/* initializer -   */
			initializer(&sh);
			free(sh.current_command);
		}
		free(sh.commands);
	}
	free(sh.line);
	free_env(&sh);
	return (sh.status);
}
