#include "shell.h"

/**
 * _free - frees ptr
 * @ptr: pointer to free
 *
 * Return: None
 */
void _free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}
/**
 * free_mallocs - frees malloced variables
 * @sh: shell parameters structure
 *
 * Return: None
 */
void free_mallocs(sh_t *sh)
{
	unsigned int i;

	if (sh->envp)
	{
		for (i = 0; sh->envp[i]; i++)
			free(sh->envp[i]);
		free(sh->envp);
	}
	if (sh->current_command)
		free(sh->current_command);
	if (sh->line)
		free(sh->line);
	if (sh->commands)
		free(sh->commands);
}
