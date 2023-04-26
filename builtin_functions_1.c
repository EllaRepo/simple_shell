#include "shell.h"

/**
 * free_env - frees env variables
 * @sh: shell parameters structure
 *
 * Return: None
 */
void free_env(sh_t *sh)
{
	unsigned int i;

	for (i = 0; sh->envp[i]; i++)
	{
		free(sh->envp[i]);
	}

	free(sh->envp);
}
