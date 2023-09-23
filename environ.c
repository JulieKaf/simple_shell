#include "main.h"

/**
 * _realloc - change buffer size and copy the content of the buffer.
 * @pointer: old buffer.
 * @older_size: the buffer old size.
 * @newest_size: the buffer new size.
 * Return: the new buffer.
*/

void *_reallocs(void *pointer, unsigned int older_size,
		unsigned int newest_size)
{
	char *buffer_s;
	unsigned int i;

	if (newest_size == older_size)
		return (pointer);
	if (newest_size == 0 && pointer != NULL)
	{
		free(pointer);
		return (NULL);
	}
	buffer_s = malloc(newest_size);
	if (buffer_s == NULL)
	{
		if (pointer)
			free(pointer);
		return (NULL);
	}
	if (pointer == NULL)
		return (buffer_s);
	for (i = 0; i < older_size && i < newest_size; i++)
	{
		buffer_s[i] = ((char *) pointer)[i];
	}

	free(pointer);
	return (buffer_s);
}

/**
 * _atoi - convert a string to an int.
 * @string: string.
 * Return: the numbers in string
 */

int _atoi(char *string)
{
	int i = (_strlen(string) - 1), j, num = 0, power = 1;

	for (j = 0; j <= i; j++)
	{
		if (string[i - j] > 47 && string[i - j] < 58)
		{
			num += (string[i - j] - 48) * power;
			power *= 10;
		}
		else
			return (-1);
	}
	return (num);
}

/**
 * _get_environ - get specific environmental variable.
 * @enp: array of environmental variable.
 * @envir: the variable to search for.
 * @length: length of the variable to search for.
 * Return: the variable or NULL if not found.
*/

char *_get_environ(char **enp, char *envir, int length)
{
	int i;

	for (i = 0; enp[i] != NULL; i++)
	{
		if (_strncomp(enp[i], envir, length) == 0)
		{
			return (&enp[i][length + 1]);
		}
	}
	return (NULL);
}

/**
 * _env - check if the input is env and provide it if it is.
 * @arg_s: parameter of type args.
 * Return: 1 input = env, 0 input != env.
*/
int _env(p *arg_s)
{
	int i;

	if (rev_comp(arg_s->line, "env"))
	{
		for (i = 0; arg_s->enp[i] != NULL; i++)
		{
			write(1, arg_s->enp[i], _strlen(arg_s->enp[i]));
			write(1, "\n", 1);
		}
		arg_s->status_num = 0;
		return (1);
	}
	return (0);
}

/**
 * handle_realloc - handle realloc and free args in case it fail.
 * @arg_s: parameter of type args.
 * @buffer_s: buffer to be reallocted
 * @buffer_size: the buffer size.
 * @extras: the size to be added.
 * @maximize: the number to comapre the buffer size with
 * Return: the buffer
 */
char *handle_reallocs(p *agr_s, char *buffer_s, int *buffer_size, int extras,
int maximize)
{
	if (*buffer_size <= maximize)
	{
		buffer_s = _reallocs(buffer_s, *buffer_size, *buffer_size + extras);
			if (buffer_s == NULL)
			{
				free_exits(agr_s);
			}
		*buffer_size += extras;
	}
	return (buffer_s);
}
