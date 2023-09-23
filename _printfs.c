#include "main.h"

/**
 * _printfs - print.
 * @format: the format
 *
 * Return: the number of chars
 */

int _printfs(const char *format, ...)
{
	unsigned int i, length = 0;
	va_list arg_s;

	if (format == NULL)
		return (-1);
	va_start(arg_s, format);
	for (i = 0; format[i]; i++)
	{
		if (format[i] != '%')
		{
			length += put_char(format[i]);
			continue;
		}
		if ((int)i++ == _strlen((char *)format) - 1)
			return (-1);
		length += specifiers(format[i], arg_s);
	}
	va_end(arg_s);
	return (length);
}

/**
 * handle_d - handle the dots
 * @input_line: input
 * @arg_s: parameter of type para
 */

void handle_d(char **input_line, p *arg_s)
{
	int i = 0, length;
	char *line_c = *input_line, *buffer;

	if (line_c[0] == '.')
	{
		buffer = mallocs2(*input_line, arg_s, 512);
		buffer[0] = '\0';
		_strcat(buffer, &((*(arg_s->pwd))[4]));
		length = _strlen(buffer);
		while (line_c[i] && line_c[i] != ' ')
		{
			if (line_c[i] == '.' && line_c[i + 1] == '.')
			{
				while (buffer[length - 1] != '/')
					buffer[(length--) - 1] = '\0';
				buffer[(length--) - 1] = '\0';
				i++;
			}
			else if (line_c[i] != '/' && line_c[i] != '.')
			{
				buffer[length++] = '/';
				while (line_c[i] && line_c[i] != '/' && line_c[i] != ' ')
					buffer[length++] = line_c[i++];
				i--;
			}
			i++;
		}
		buffer[length] = '\0';
		if (access(buffer, X_OK) == 0)
		{
			_strcat(buffer, &line_c[i]);
			free(*input_line);
			*input_line = buffer;
		}
		else
		{
			free(buffer);
		}
	}
}

/**
 * mallocs2 - handle malloc2
 * @line_ptr: input
 * @arg_s: parameter of type para
 * @size_: the size
 *
 * Return: the buffer
 */

char *mallocs2(char *line_ptr, p *arg_s, int size_)
{
	char *buffer = malloc(size_);

	if (!buffer)
	{
		free(line_ptr);
		free_exits(arg_s);
	}
	return (buffer);
}

/**
* tokens - function to return the splitted number of token
* @line_: the string to be splitted
* @delimeter: the delim used to split the string
* Return:number of token splitted
*/
int tokens(char *line_s, char *delimeter)
{
	int n_token = 0;
	char *str_token = _strtokenizer(line_s, delimeter);

	while (str_token)
	{
		str_token = _strtokenizer(NULL, delimeter);
		n_token++;
	}
	return (n_token);
}
