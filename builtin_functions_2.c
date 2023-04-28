#include "shell.h"

/**
 * get_env - returns environment variable of name
 * @name: env variable
 * @_environ: environ
 *
 * Return: the value of the variable if found
 *         NULL if not found
 */
char *get_env(char *name, char **_environ)
{
	char **env;
	int len, bool;

	if (name)
	{
		len = _strlen(name);
		env = _environ;
		while (*env)
		{
			bool = _strncmp(*env, name, len);
			if (bool == 0 && (*env)[len] == '=')
			{
				return (&(*env)[len + 1]);
			}
			env++;
		}
	}
	return (NULL);
}
