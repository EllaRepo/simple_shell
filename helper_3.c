#include "shell.h"

/**
 * assemble_env_var - builds environment variable
 * @name: name of the environment
 * @value: value of the environment
 *
 * Return: new env
 */
char *assemble_env_var(char *name, char *value)
{
	char *new_env_var;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new_env_var = malloc(sizeof(char) * (len));
	_strcpy(new_env_var, name);
	__strcat(new_env_var, "=");
	__strcat(new_env_var, value);
	__strcat(new_env_var, "\0");
	return (new_env_var);
}
/**
 * _strncmp - Compares two strings until n bytes
 * @str1: String
 * @str2: String
 * @n: Number of bytes to compare
 *
 * Return: 0 if strings are equal
 *        >0 if the first non-matching character in s1 is greater (in ASCII)
 *           than that of s2
 *        <0 if the first non-matching character in s1 is less (in ASCII)
 *           than that of s2
 */
int _strncmp(char *str1, char *str2, size_t n)
{
	char *s1, *s2;

	s1 = str1;
	s2 = str2;
	if (n == 0)
		return (0);
	do {
		if (*s1 != *s2++)
			return (*(unsigned char *)s1 -
				*(unsigned char *)(--s2));
		if (*s1++ == 0)
			break;
	} while (--n != 0);
	return (0);
}
/**
 * __realloc - reallocates a memory block of a double pointer
 * @pptr: double pointer to the memory previously allocated.
 * @old_sz: size, in bytes, of the allocated space of pptr.
 * @new_sz: new size, in bytes, of the new memory block.
 *
 * Return: newly created pptr.
 *         pptr without changes if new_sz == old_sz,
 *         NULL if malloc fails,
 */
char **__realloc(char **pptr, unsigned int old_sz, unsigned int new_sz)
{
	char **new_ptr;
	unsigned int i;

	if (pptr == NULL)
		return (malloc(sizeof(char *) * new_sz));

	if (new_sz == old_sz)
		return (pptr);

	new_ptr = malloc(sizeof(char *) * new_sz);
	if (new_ptr == NULL)
		return (NULL);
	for (i = 0; i < old_sz; i++)
		new_ptr[i] = pptr[i];
	free(pptr);
	return (new_ptr);
}
/**
 * _strdup - duplicates a str in the heap memory.
 * @s: string
 * Return: duplicated str
 */
char *_strdup(char *s)
{
	char *new;
	size_t len;

	len = _strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, len + 1);
	return (new);
}
/**
 * _memcpy - copies information between void pointers.
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}
