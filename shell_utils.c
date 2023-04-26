#include "shell.h"

/**
 * parse_command - determines the type of the command
 * @command: command to be parsed
 *
 * Return: constant representing the type of the command
 * Description -
 *		EXTERNAL_COMMAND (1) represents commands like /bin/ls
 *		INTERNAL_COMMAND (2) represents commands like exit, env
 *		PATH_COMMAND (3) represents commands found in the PATH like ls
 *		INVALID_COMMAND (-1) represents invalid commands
 */

int parse_command(char *command)
{
	int i;
	char *internal_command[] = {"env", "exit", "setenv", "unsetenv", NULL};
	char *path = NULL;

	for (i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == '/')
			return (EXTERNAL_COMMAND);
	}
	for (i = 0; internal_command[i] != NULL; i++)
	{
		if (_strcmp(command, internal_command[i]) == 0)
			return (INTERNAL_COMMAND);
	}
	/* @check_path - checks if a command is found in the PATH */
	path = check_path(command);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
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
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (sh->cmd_type == PATH_COMMAND)
	{
		if (execve(check_path(sh->current_command[0]),
			sh->current_command, environ) == -1)
		{
			perror(_getenv("PWD"));
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
 * @command: command to be used
 *
 * Return: path where the command is found in, NULL if not found
 */
char *check_path(char *command)
{
	char **path_array = NULL;
	char *temp, *temp2, *path_cpy;
	char *path = _getenv("PATH");
	int i;

	if (path == NULL || _strlen(path) == 0)
		return (NULL);
	path_cpy = malloc(sizeof(*path_cpy) * (_strlen(path) + 1));
	_strcpy(path_cpy, path);
	path_array = tokenizer(path_cpy, ":");
	for (i = 0; path_array[i] != NULL; i++)
	{
		temp2 = _strcat(path_array[i], "/");
		temp = _strcat(temp2, command);
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
		{"unsetenv", _unsetenv}
	};

	for (i = 0; i < 4; i++)
	{
		if (_strcmp(command, mapping[i].command_name) == 0)
			return (mapping[i].func);
	}
	return (NULL);
}

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the environment variable
 *
 * Return: the value of the variable as a string
 */
char *_getenv(char *name)
{
	char **my_environ;
	char *pair_ptr;
	char *name_cpy;

	for (my_environ = environ; *my_environ != NULL; my_environ++)
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
