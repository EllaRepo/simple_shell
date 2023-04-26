#include "shell.h"

/**
 * cd_home - changes current diretory to home directory
 * @sh: shell parameters structure
 *
 * Return: 0
*/
void cd_home(sh_t *sh)
{
	char *home, *cwd;
	char buff[PATH_MAX];

	cwd = getcwd(buff, sizeof(buff));
	home = _getenv("HOME", sh);

	if (home == NULL)
	{
		set_env("OLDPWD", cwd, sh);
		return;
	}
	if (chdir(home) == 0)
	{
		set_env("PWD", cwd, sh);
		set_env("OLDPWD", cwd, sh);
		sh->status = 0;
		return;
	}
	cd_error(sh);
}
/**
 * cd_prev - changes current diretory to previous directory
 * @sh: shell parameters structure
 *
 * Return: 0
*/
void cd_prev(sh_t *sh)
{
	char *owd, *cwd;
	char buff[PATH_MAX];

	cwd = getcwd(buff, sizeof(buff));
	owd = _getenv("OLDPWD", sh);

	if (owd == NULL)
	{
		owd = cwd;
	}
	if (chdir(owd) == 0)
		set_env("PWD", owd, sh);
	else
		set_env("PWD", cwd, sh);
	set_env("OLDPWD", cwd, sh);
	cwd = _getenv("PWD", sh);
	write(STDOUT_FILENO, cwd, strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	sh->status = 0;

	chdir(cwd);
}
/**
 * cd_dot - changes to the parent directory
 * @sh: shell parameters structure
 *
 * Return: no return
 */
void cd_dot(sh_t *sh)
{
	char buff[PATH_MAX];
	char *dir, *cwd, *pwd;

	cwd = getcwd(buff, sizeof(buff));
	set_env("OLDPWD", cwd, sh);
	dir = sh->current_command[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cwd, sh);
		return;
	}
	if (_strcmp("/", cwd) == 0)
		return;
	pwd = cwd;
	_rev_string(pwd);
	pwd = _strtok(pwd, "/");
	if (pwd != NULL)
	{
		pwd = _strtok(NULL, "\0");

		if (pwd != NULL)
			_rev_string(pwd);
	}
	if (pwd != NULL)
	{
		chdir(pwd);
		set_env("PWD", pwd, sh);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", sh);
	}
	sh->status = 0;
}
/**
 * cd_dir - changes the current diretory to a dir set in by the user
 * @sh: shell parameters structure
 *
 * Return: None
 */
void cd_dir(sh_t *sh)
{
	char buff[PATH_MAX];
	char *dir, *cwd;

	cwd = getcwd(buff, sizeof(buff));

	dir = sh->current_command[1];
	if (chdir(dir) == -1)
	{
		cd_error(sh);
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
	int home1, home2, ddash;

	cd = sh->current_command[1];
	if (cd != NULL)
	{
		home1 = strcmp("$HOME", cd);
		home2 = strcmp("~", cd);
		ddash = strcmp("--", cd);
	}
	if (cd == NULL || !home1 || !home2 || !ddash)
	{
		cd_home(sh);
		return;
	}
	if (_strcmp("-", cd) == 0)
	{
		cd_prev(sh);
		return;
	}
	if (_strcmp(".", cd) == 0 || _strcmp("..", cd) == 0
		|| _strcmp("../", cd) == 0)
	{
		cd_dot(sh);
		return;
	}
	cd_dir(sh);
}
