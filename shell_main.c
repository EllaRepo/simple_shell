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
	sh->filename = argv[1] ? argv[1] : NULL;
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
int main(int argc, char **argv)
{
	sh_t sh;

	signal(SIGINT, ctrl_c_handler);
	init(&sh, argv);
	if (argc == 2)
		exec_cmd_from_file(&sh);
	non_interactive(&sh);
	shell_loop(&sh);

	return (sh.status);
}
