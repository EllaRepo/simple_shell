#include "shell.h"

/**
 * initializer - starts executing everything
 * @sh: shell parameters struture
 *
 * Return: void function
 */

void initializer(sh_t *sh)
{
	pid_t PID;

	if (sh->cmd_type == EXTERNAL_COMMAND || sh->cmd_type == PATH_COMMAND)
	{
		if (sh->cmd_type == EXTERNAL_COMMAND)
		{
			if (access(sh->current_command[0], F_OK) != 0)
			{
				print(sh->shell_name, STDERR_FILENO);
				print(": ", STDERR_FILENO);
				print(sh->current_command[0], STDERR_FILENO);
				print(": No such file or directory\n", STDERR_FILENO);
				sh->status = 127;
				return;
			}
		}
		PID = fork();
		if (PID == 0)
			execute_command(sh);
		else
		{
			waitpid(PID, &sh->status, 0);
			sh->status >>= 8;
		}
	}
	else
		execute_command(sh);
}
