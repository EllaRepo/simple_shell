#include "shell.h"

/**
 * __get_line - assigns the line var for _get_line
 * @linep: buff that store the input str
 * @buff: str that is been called to line
 * @szp: size of line
 * @bsz: size of buffer
 */
void __get_line(char **linep, size_t *szp, char *buff, size_t bsz)
{

	if (*linep == NULL)
	{
		if  (bsz > BUFSIZE)
			*szp = bsz;

		else
			*szp = BUFSIZE;
		*linep = buff;
	}
	else if (*szp < bsz)
	{
		if (bsz > BUFSIZE)
			*szp = bsz;
		else
			*szp = BUFSIZE;
		*linep = buff;
	}
	else
	{
		_strcpy(*linep, buff);
		free(buff);
	}
}
/**
 * _get_line - Read input from fp
 * @linep: buffer that stores the input
 * @szp: size of linep
 * @fp: fp to read from
 * Return: The number of bytes
 */
ssize_t _get_line(char **linep, size_t *szp, FILE *fp)
{
	int i;
	static ssize_t ip;
	ssize_t retval;
	char *buff;
	char t = 'z';

	if (ip == 0)
		fflush(fp);
	else
		return (-1);
	ip = 0;

	buff = malloc(sizeof(char) * BUFSIZE);
	if (buff == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && ip == 0))
		{
			free(buff);
			return (-1);
		}
		if (i == 0 && ip != 0)
		{
			ip++;
			break;
		}
		if (ip >= BUFSIZE)
			buff = _realloc(buff, ip, ip + 1);
		buff[ip] = t;
		ip++;
	}
	buff[ip] = '\0';
	__get_line(linep, szp, buff, ip);
	retval = ip;
	if (i != 0)
		ip = 0;
	return (retval);
}
