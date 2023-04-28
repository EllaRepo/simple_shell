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

/**
 * cd_home - changes current diretory to home directory
 * @sh: shell parameters structure
 *
 * Return: None
*/
void cd_home(sh_t *sh)
{
	char *home, *cwd;
	char buff[BUFSIZE];

	cwd = getcwd(buff, sizeof(buff));
	home = get_env("HOME", sh->envp);

	if (home == NULL)
	{
		set_env("OLDPWD", cwd, sh);
	}
	else if (chdir(home) == 0)
	{
		set_env("PWD", cwd, sh);
		set_env("OLDPWD", cwd, sh);
		sh->status = 0;
	}
}
/**
 * cd_prev - changes current diretory to previous directory
 * @sh: shell parameters structure
 *
 * Return: None
*/
void cd_prev(sh_t *sh)
{
	char *owd, *cwd;
	char buff[BUFSIZE];

	cwd = getcwd(buff, sizeof(buff));
	owd = get_env("OLDPWD", sh->envp);

	if (owd == NULL)
	{
		owd = cwd;
	}
	if (chdir(owd) == 0)
		set_env("PWD", owd, sh);
	else
		set_env("PWD", cwd, sh);
	set_env("OLDPWD", cwd, sh);
	cwd = get_env("PWD", sh->envp);
	write(STDOUT_FILENO, cwd, strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	sh->status = 0;

	chdir(cwd);
}
/**
 * cd_dir - changes the current diretory to a dir set in by the user
 * @sh: shell parameters structure
 *
 * Return: None
 */
void cd_dir(sh_t *sh)
{
	char buff[BUFSIZE];
	char *dir, *cwd;

	cwd = getcwd(buff, sizeof(buff));
	dir = sh->current_command[1];
	if (chdir(dir) == -1)
	{
		print(sh->shell_name, STDERR_FILENO);
		print(": 1: cd: can't cd to ", STDERR_FILENO);
		print(dir, STDERR_FILENO);
		print("\n", STDERR_FILENO);
		return;
	}
	set_env("OLDPWD", cwd, sh);
	set_env("PWD", dir, sh);
	sh->status = 0;
	chdir(dir);
}
/**
 * cd_sh - changes thecurrent directory
 * @sh: shell parameters struture
 *
 * Return: None
 */
void cd_sh(sh_t *sh)
{
	char *cd;

	cd = sh->current_command[1];

	if (cd == NULL)
	{
		cd_home(sh);
		return;
	}
	if (_strcmp("-", cd) == 0)
	{
		cd_prev(sh);
		return;
	}
	cd_dir(sh);
}
