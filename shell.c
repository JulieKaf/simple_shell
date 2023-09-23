#include "main.h"

/**
 * _commands_ - handle the path of the command passed.
 * @arg_s: parameter of type para
 * Return: 0 or 127
 */
int _commands_(p *arg_s)
{
	int i;
	char *path = arg_s->path;

	if (_exit_shell_(arg_s) || cd(arg_s))
		return (arg_s->status_num);
	if (arg_s->line[0] == '/')
	{
		if (access(arg_s->line, X_OK) == 0)
		{
			if (!_env(arg_s))
				return (_excecute(arg_s, arg_s->line));
			return (0);
		}
	_printfs("%s: %i: %s: not found\n", arg_s->shell_user, arg_s->counter,
			arg_s->line);
	}
	else
	{
		if (!_strcomp(arg_s->line, "env") && _env(arg_s))
			return (0);
		for (i = 0; i < arg_s->num_path; i++)
		{
			char buffer[500] = "";

			_strcat(buffer, path);
			_strcat(buffer, "/");
			_strcat(buffer, arg_s->line);
			if (access(buffer, X_OK) == 0)
				return (_excecute(arg_s, buffer));
			path += _strlen(path) + 1;
		}
	_printfs("%s: %i: %s: not found\n", arg_s->shell_user,
			arg_s->counter, arg_s->line);
	}
	arg_s->status_num = 127;
	return (127);
}

/**
* _excecute - function executing the command
* @arg_s: parameter of type para
* @buffer: input buffer
* Return: the exit status.
*/
int _excecute(p *arg_s, char *buffer)
{
	int i;
	char **arg_v, *line = arg_s->line;
	pid_t id_num = fork();

	if (!id_num)
	{
		if (rev_comp(arg_s->line, "pwd"))
		{
			arg_v = malloc(16);
			if (arg_v == NULL)
				exit(255);
			arg_v[0] = arg_s->line;
			arg_v[1] = NULL;
		}
		else
		{
			arg_v = malloc(8 * (arg_s->num_token + 1));
			if (arg_v == NULL)
				exit(255);
			for (i = 0; i < arg_s->num_token; i++)
			{
				arg_v[i] = line;
				line += _strlen(line) + 1;
			}
			arg_v[i] = NULL;
		}
		execve(buffer, arg_v, NULL);
		free(arg_v);
		exit(arg_s->status_num);
	}
	wait(&(arg_s->status_num));
	arg_s->status_num = WEXITSTATUS(arg_s->status_num);
	return (arg_s->status_num);
}

/**
 * _exit_shell_ - handle if exit the shell and the exit status.
 * @arg_s: parameter of type para
 * Return: 0 success, 1 failure
*/
int _exit_shell_(p *arg_s)
{
int length;

if (!_strcomp(arg_s->line, "exit"))
{
	if (arg_s->num_token > 1)
	{
	length = _strlen(arg_s->line) + 1;
	arg_s->status_num = _atoi(arg_s->line + length);
	}
	if (arg_s->status_num != -1)
	{
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
	_printfs("%s: %i: exit: Illegal number: %s\n",
	arg_s->shell_user, arg_s->counter, arg_s->line + length);
	arg_s->status_num = 2;
	return (1);
}
	return (0);
}

/**
* ctrl_c - handle signal
* @signal: the singal
*/
void ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n=> ", 4);
	}
}

/**
* main - The entry point of the program
* @argc: number of argument to the program
* @argv: array of argument to the program
* @envp: array of environmental variable
* Return: 0;
*/
int main(int argc, char **argv, char **envp)
{
	p arg_s;
	int  arrow = 1, semi_numb = 0;

	arg_s.line = NULL, arg_s.path = NULL;
	arg_s.enp = envp, arg_s.pwd = NULL;
	arg_s.older_pwd = NULL;
	arg_s.path = _strdupl(&arg_s, _get_environ(envp, "PATH", 4));
	arg_s.pwd = gets_PWD(&arg_s);
	if (arg_s.pwd)
		arg_s.older_pwd = _strdupl(&arg_s, &((*arg_s.pwd)[4]));
	arg_s.shell_user = argv[0];
	arg_s.counter = 0, arg_s.status_num = 0, arg_s.file_name = 0;
	arg_s.pi = (int)getpid();
	arg_s.num_path = tokens(arg_s.path, ":");
	if (argc > 1)
	{
		arg_s.file_name = open(argv[1], O_RDONLY);
		if (arg_s.file_name == -1)
		{
			_printfs("%s: 0: cannot open %s: No such file\n", argv[0], argv[1]);
			free_exits(&arg_s);
			exit(2);
		}
	}
while (1)
{
	if (isatty(STDIN_FILENO) && arrow && !arg_s.file_name)
		write(1, "=> ", 3);
	signal(SIGINT, ctrl_c);
	arg_s.counter++;
	arrow = _inputs(&arg_s, arrow, &semi_numb);
	if (handle_inputs(&arg_s))
		continue;
	arg_s.num_token = tokens(arg_s.line, " ");
	if (_commands_(&arg_s) == 255)
		free_exits(&arg_s);
}
if (argc > 1)
	close(arg_s.file_name);
return (0);
}
