#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>
#include <fcntl.h>

/*constants*/
#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1

#define BUFSIZE 1024

#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 * struct sh - a struct that holds shell parameters
 * @commands: splited commands user entered
 * @line: string from getline function
 * @shell_name: the program name
 * @current_command: the current command
 * @cmd_type: type of the command
 * @envp: an array of pointers to environment variables
 * @filename: file name passed as input
 * @status: the last execution status
 */
typedef struct sh
{
	char **commands;
	char *line;
	char *shell_name;
	char **current_command;
	int cmd_type;
	char **envp;
	char *filename;
	int status;
} sh_t;

/**
 *struct map - a struct that maps a command name to a function
 *@command_name: name of the command
 *@func: the function that executes the command
 */

typedef struct map
{
	char *command_name;
	void (*func)(sh_t *sh);
} function_map;

extern char **environ;
extern char *line;
extern char **commands;
extern char *shell_name;
extern int status;

/*helpers*/
void print(char *, int);
char **tokenizer(char *, char *);
void remove_newline(char *);
int _strlen(char *);
void _strcpy(char *, char *);

/*helpers2*/
int _strcmp(char *, char *);
char *_strcat(char *, char *);
int _strspn(char *, char *);
int _strcspn(char *, char *);
char *_strchr(char *, char);

/*helpers3*/
char *_strtok_r(char *, char *, char **);
int _atoi(char *);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void ctrl_c_handler(int);
void remove_comment(char *);
/*helper4*/
char *assemble_env_var(char *name, char *value);
int _strncmp(char *str1, char *str2, size_t n);
char **__realloc(char **pptr, unsigned int old_sz, unsigned int new_sz);
char *_strdup(char *s);
void _memcpy(void *newptr, const void *ptr, unsigned int size);
/*helper5*/
char *__strcat(char *dest, char *src);
/*utils*/
int parse_command(char *);
void execute_command(sh_t *sh);
char *check_path(char *);
void (*get_func(char *))(sh_t *);
char *_getenv(char *);

/*built_in*/
void env(sh_t *sh);
void quit(sh_t *sh);
void _setenv(sh_t *sh);
void _unsetenv(sh_t *sh);
void free_env(sh_t *sh);
void cd_sh(sh_t *sh);
char *get_env(char *, char **);
void set_env(char *, char *, sh_t *);

/*main*/
extern void non_interactive(sh_t *sh);
extern void initializer(sh_t *sh);
void exec_cmd_from_file(sh_t *sh);
/*chk syntax error*/
int chk_syntax_err(sh_t *sh);
#endif /*SHELL_H*/
