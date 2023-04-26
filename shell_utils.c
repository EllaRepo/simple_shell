#include "shell.h"

/**
 * parse_command - determines the type of the command
 * @sh: shell parameters structure
 *
 * Return: None
 * Description -
 *		EXTERNAL_COMMAND (1) represents commands like /bin/ls
 *		INTERNAL_COMMAND (2) represents commands like exit, env
 *		PATH_COMMAND (3) represents commands found in the PATH like ls
 *		INVALID_COMMAND (-1) represents invalid commands
 */

void parse_command(sh_t *sh)
{
	int i;
	char *internal_command[] = {"env", "exit", "setenv", "unsetenv",
		"cd", NULL};
	char *path = NULL, *command;

	command =  sh->current_command[0];
	for (i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == '/')
		{
			sh->cmd_type = EXTERNAL_COMMAND;
			return;
		}
	}
	for (i = 0; internal_command[i] != NULL; i++)
	{
		if (_strcmp(command, internal_command[i]) == 0)
		{
			sh->cmd_type = INTERNAL_COMMAND;
			return;
		}
	}
	/* @check_path - checks if a command is found in the PATH */
	path = check_path(sh);
	if (path != NULL)
	{
		free(path);
		sh->cmd_type = PATH_COMMAND;
		return;
	}
	sh->cmd_type = INVALID_COMMAND;
}

/**
 * execute_command - executes a command based on it's type
 * @sh: shell parameters struture
 *
 * Return: void
 */
void execute_command(sh_t *sh)
{
	void (*func)(sh_t *sh);

	if (sh->cmd_type == EXTERNAL_COMMAND)
	{
		if (execve(sh->current_command[0], sh->current_command, environ) == -1)
		{
			perror(_getenv("PWD", sh));
			free_mallocs(sh);
			exit(2);
		}
	}
	if (sh->cmd_type == PATH_COMMAND)
	{
		if (execve(check_path(sh),
			sh->current_command, sh->envp) == -1)
		{
			perror(_getenv("PWD", sh));
			free_mallocs(sh);
			exit(2);
		}
	}
	if (sh->cmd_type == INTERNAL_COMMAND)
	{
		func = get_func(sh->current_command[0]);
		func(sh);
	}
	if (sh->cmd_type == INVALID_COMMAND)
	{
		print(sh->shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(sh->current_command[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		sh->status = 127;
	}
}

/**
 * check_path - checks if a command is found in the PATH
 * @sh: shell parameters structure
 *
 * Return: path where the command is found in, NULL if not found
 */
char *check_path(sh_t *sh)
{
	char **path_array = NULL;
	char *temp, *temp2, *path_cpy;
	char *path = _getenv("PATH", sh);
	int i;

	if (path == NULL || _strlen(path) == 0)
		return (NULL);
	path_cpy = malloc(sizeof(*path_cpy) * (_strlen(path) + 1));
	_strcpy(path_cpy, path);
	path_array = tokenizer(path_cpy, ":");
	for (i = 0; path_array[i] != NULL; i++)
	{
		temp2 = _strcat(path_array[i], "/");
		temp = _strcat(temp2, sh->current_command[0]);
		if (access(temp, F_OK) == 0)
		{
			free(temp2);
			free(path_array);
			free(path_cpy);
			return (temp);
		}
		free(temp);
		free(temp2);
	}
	free(path_cpy);
	free(path_array);
	return (NULL);
}

/**
 * get_func - retrieves a function based on the command given and a mapping
 * @command: string to check against the mapping
 *
 * Return: pointer to the proper function, or null on fail
 */
void (*get_func(char *command))(sh_t *)
{
	int i;
	function_map mapping[] = {
		{"env", env}, {"exit", quit}, {"setenv", _setenv},
		{"unsetenv", _unsetenv}, {"cd", cd_sh}
	};

	for (i = 0; i < 5; i++)
	{
		if (_strcmp(command, mapping[i].command_name) == 0)
			return (mapping[i].func);
	}
	return (NULL);
}

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the environment variable
 * @sh: shell parameters
 *
 * Return: the value of the variable as a string
 */
char *_getenv(char *name, sh_t *sh)
{
	char **my_environ;
	char *pair_ptr;
	char *name_cpy;

	for (my_environ = sh->envp; *my_environ != NULL; my_environ++)
	{
		for (pair_ptr = *my_environ, name_cpy = name;
		     *pair_ptr == *name_cpy; pair_ptr++, name_cpy++)
		{
			if (*pair_ptr == '=')
				break;
		}
		if ((*pair_ptr == '=') && (*name_cpy == '\0'))
			return (pair_ptr + 1);
	}
	return (NULL);
}
