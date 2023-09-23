#include "main.h"

#define D(i) (*dollars)[i]
/**
* _inputs - determine if we start new line in the shell with an arrow.
* @arg_s: parameter of type para
* @arr: 1 if stdin
* @semi:  0 or 1
* Return: 0, 1
*/
int _inputs(p *arg_s, int arr, int *semi)
{
	ssize_t read;

	read = _getline(arg_s);
	if (read == -1)
	{
		if (isatty(STDIN_FILENO) && arr && !arg_s->file_name)
			write(1, "\n", 1);
		close(arg_s->file_name);
		if (arg_s->line)
			free(arg_s->line);
		if (arg_s->path)
			free(arg_s->path);
		if (arg_s->pwd)
			free(*(arg_s->pwd));
		if (arg_s->older_pwd)
			free(arg_s->older_pwd);
		exit(arg_s->status_num);
	}
	if (*semi)
		arg_s->counter--;
	if (arg_s->line[read - 1] == '\n')
	{
		arg_s->line[read - 1] = '\0';
	}
	if (arg_s->line[read - 1] == ';')
	{
		arg_s->line[read - 1] = '\0';
		*semi = 1;
		return (0);
	}
	*semi = 0;
	return (1);
}

/**
 * _getline - read an entire line from a stream.
 * @arg_s: parameter of type para.
 * Return: no of chars read from the stream.
*/
ssize_t _getline(p *arg_s)
{
	size_t i = 0;
	ssize_t read_line;
	char *buffer;
	int buffer_size = 10240;

	if (&(arg_s->line) == NULL)
		return (-1);
	buffer = _mallocs(arg_s, buffer_size + 1);
	if (arg_s->line)
	{
		free(arg_s->line);
		arg_s->line = NULL;
	}
	while ((read_line = read(arg_s->file_name, buffer + i, 1)) > 0)
	{
		i++;
		buffer = handle_reallocs(arg_s, buffer, &buffer_size, 2048, i);
		if (buffer[i - 1] == '\n' || buffer[i - 1] == ';')
			break;
	}
	if (read_line < 0 || (!read_line && !i))
	{
		free(buffer);
		return (-1);
	}
	if (read_line != 8)
		buffer[i] = '\0';
	arg_s->line = buffer;
	return (i);
}

/**
 * handle_inputs - determine if line contain $ or # and act accordingly.
 * @arg_s: parameter of type para..
 *
 * Return: 1 if the string is empty
*/
int handle_inputs(p *arg_s)
{
char *_buffer, *dollar, *start, *hash = _strchr(arg_s->line, '#');
int buffer_size = 10240;

if (hash && ((hash != arg_s->line && *(hash - 1) == ' ')
			|| hash == arg_s->line))
	*hash = '\0';
_buffer = _mallocs(arg_s, buffer_size);
dollar = _strchr(arg_s->line, '$');
start = arg_s->line;
_buffer[0] = '\0';
while (dollar)
{
	_buffer = handle_reallocs(arg_s, _buffer, &buffer_size,
	1024, _strlen(_buffer) + dollar - start);
	_strncatenate(_buffer, start, dollar - start);
	handle_dollar_sign(_buffer, &dollar, arg_s);
	start = dollar;
	dollar = _strchr(start, '$');
}
_buffer = handle_reallocs(arg_s, _buffer, &buffer_size,
128, _strlen(_buffer) + _strlen(start));
_strcat(_buffer, start);
spaces(&_buffer, arg_s);
handle_d(&_buffer, arg_s);
free(arg_s->line);
arg_s->line = _buffer;
return (_buffer[0] == '\0');
}

/**
 * handle_dollar_sign - handle input containing $ sign.
 * @buffer_s: input containing $.
 * @d: input starting from $ sign.
 * @args: parameter of type para.
*/
void handle_dollar_sign(char *buffer_s, char **dollars, p *arg_s)
{
	char num[10], *env;
	int i = 0;

	(*dollars)++;
	if (D(0) == '$' || D(0) == '?')
	{
		if (D(0) == '$')
			tostringify(num, arg_s->pi);
		else
			tostringify(num, arg_s->status_num);
		_strcat(buffer_s, num);
		(*dollars)++;
	}
	else
	{
		while (D(i) && D(i) != ' ' && D(i) != '#' && D(i) != '$' && D(i) != '/')
			i++;
		if (!i)
			_strcat(buffer_s, "$");
		else
		{
			env = _get_environ(arg_s->enp, *dollars, i);
			if (env)
				_strcat(buffer_s, env);
			*dollars += i;
		}
	}
}

/**
 * spaces - handle extra spaces in the input.
 * @line_s: input
 * @arg_s: parameter of type para.
*/
void spaces(char **line_s, p *arg_s)
{
	int i = 0, j = 0;
	char *buffer = malloc(_strlen(*line_s) + 1);

	if (buffer == NULL)
	{
		free(*line_s);
		free_exits(arg_s);
	}
	while ((*line_s)[i] && (*line_s)[i] == ' ')
		i++;
	while ((*line_s)[i])
	{
		if ((*line_s)[i] == ' ')
		{
			buffer[j] = ' ';
			j++;
			while ((*line_s)[i] == ' ')
				i++;
		}
		else
		{
			buffer[j] = (*line_s)[i];
			i++;
			j++;
		}
	}
	if (j && buffer[j - 1] == ' ')
		j--;
	buffer[j] = '\0';
	free(*line_s);
	*line_s = buffer;
}
