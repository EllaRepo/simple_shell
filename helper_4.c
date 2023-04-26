#include "shell.h"

/**
 * __strcat - Concatenates two strings
 * @dest: A char pointer pointing to the destination string
 * @src: A char pointer pointing to the source string
 *
 * Return: A pointer to the resulting string 'dest'
 */
char *__strcat(char *dest, char *src)
{
	char *d, *s;

	d = dest;
	s = src;
	while (*d)
		d++;
	while ((*d++ = *s++) != '\0')
		;

	return (dest);
}

/**
 * _rev_string - reverses a string
 * @s: string
 *
 * Return: None
 */
void _rev_string(char *s)
{
	int count = 0, i, j;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}

/**
 * cmp_chars - compare chars of strings
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}
/**
 * check_delim - compare chars of strings
 * @str: string
 * @delim: delimiter
 *
 * Return: 1 if delim found
 *         0 if not
 */
int check_delim(char *str, char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - splits a string by delimiter.
 * @str: string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *_strtok(char *str, char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, j;

	if (str)
	{
		if (check_delim(str, delim))
			return (NULL);
		splitted = str;
		i = _strlen(str);
		str_end = &str[i];
	}
	str_start = splitted;
	if (str_start == str_end)
		return (NULL);

	for (j = 0; *splitted; splitted++)
	{
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (j == 0 && *splitted)
			j = 1;
	}
	if (j == 0)
		return (NULL);
	return (str_start);
}
