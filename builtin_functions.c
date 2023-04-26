#include "shell.h"

/**
 * env - prints the current_environnement
 * @sh: shell parameters structure
 *
 *Return: void
 */

void env(sh_t *sh)
{
	int i;

	for (i = 0; sh->envp[i] != NULL; i++)
	{
		print(sh->envp[i], STDOUT_FILENO);
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
		free_mallocs(sh);
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
			free_mallocs(sh);
			exit(arg);
		}
	}
	else
		print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}
/**
 * set_env - change or add an environment variable
 * @name: name of the environment
 * @value: value of the environment
 * @sh: shell parameter structure
 *
 * Return: None.
 */
void set_env(char *name, char *value, sh_t *sh)
{
	int len, i, j;
	char **ev, *err;

	len = _strlen(name);
	for (i = 0; sh->envp[i]; i++)
	{
		j = _strncmp(sh->envp[i], name, len);
		if (j == 0 && sh->envp[i][len] == '=')
		{
			free(sh->envp[i]);
			sh->envp[i] = assemble_env_var(name, value);
			return;
		}
	}
	ev  = __realloc(sh->envp, i, sizeof(char *) * (i + 2));
	if (!ev)
	{
		err = "Unable to unset env variable\n";
		write(STDERR_FILENO, err, _strlen(err));
		return;
	}
	sh->envp = ev;
	sh->envp[i] = assemble_env_var(name, value);
	sh->envp[i + 1] = NULL;
}
/**
 * _setenv - change or add an environment variable
 * @sh: shell parameters structure
 *
 * Return: None
 */
void _setenv(sh_t *sh)
{
	char *err;

	if (sh->current_command[1] == NULL || sh->current_command[2] == NULL)
	{
		err = "Unable to set env variable\n";
		write(STDERR_FILENO, err, _strlen(err));
		return;
	}
	set_env(sh->current_command[1], sh->current_command[2], sh);

}
/**
 * _unsetenv - deletes the variable name from the environment
 * @sh: shell parameters structure
 *
 * Return: None
 */
void _unsetenv(sh_t *sh)
{
	char **env, *err;
	int len, bool, i, j, k;

	if (sh->current_command[1] == NULL)
	{
		err = "No env variable is entered\n";
		write(STDERR_FILENO, err, _strlen(err));
		return;
	}
	len = _strlen(sh->current_command[1]);
	k = -1;
	for (i = 0; sh->envp[i]; i++)
	{
		bool = _strncmp(sh->current_command[1], sh->envp[i], len);
		if (bool == 0 && sh->envp[i][len] == '=')
			k = i;
	}
	if (k == -1)
	{
		err = "Unable to unset env variable\n";
		write(STDERR_FILENO, err, _strlen(err));
		return;
	}
	env = malloc(sizeof(char *) * (i));
	for (i = j = 0; sh->envp[i]; i++)
	{
		if (i != k)
		{
			env[j] = sh->envp[i];
			j++;
		}
	}
	env[j] = NULL;
	free(sh->envp[k]);
	free(sh->envp);
	sh->envp = env;
}
