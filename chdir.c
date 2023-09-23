#include "main.h"
/**
 * cd - change directory.
 * @arg_s: parameter of type para
 * Return: 0, 1
 */
int cd(p *arg_s)
{
	char *desti, *line = arg_s->line;

	if (!_strcomp(line, "cd"))
	{
		if (arg_s->num_token == 1)
			desti = _get_environ(arg_s->enp, "HOME", 4);
		else
		{
			line += 3;
			if (!_strcomp(line, "-"))
			{
				desti = arg_s->older_pwd;
				write(1, desti, _strlen(desti));
				write(1, "\n", 1);
			}
			else
				desti = line;
		}
		if (chdir(desti) == -1)
		{
		_printfs("%s: %i: cd: can't cd to %s\n", arg_s->shell_user,
				arg_s->counter, desti);
		arg_s->status_num = 2;
		}
		else
		{
			free(arg_s->older_pwd);
			arg_s->older_pwd = _strdupl(arg_s, &((*(arg_s->pwd))[4]));
			if (!arg_s->older_pwd)
				free_exits(arg_s);
			pwd_changer(arg_s);
			arg_s->status_num = 0;
		}
		return (1);
	}
	return (0);
}

/**
 * pwd_changer - change the pwd
 * @arg_s: parameter of type para.
 */
void pwd_changer(p *arg_s)
{
	char buffer[250];
	char *pwd = _mallocs(arg_s, 256);

	getcwd(buffer, 250);
	pwd[0] = '\0';
	_strcat(pwd, "PWD=");
	_strcat(pwd, buffer);
	free(*(arg_s->pwd));
	*(arg_s->pwd) = pwd;
}
/**
 * gets_PWD - get the pwd from the env
 * @arg_s: parameter of type para.
 * Return: pointer to the pwd
 */
char **gets_PWD(p *arg_s)
{
	int i;
	char *pwd = NULL;

	for (i = 0; arg_s->enp[i] != NULL; i++)
	{
		if (_strncomp(arg_s->enp[i], "PWD", 3) == 0)
		{
			pwd = _strdupl(arg_s, arg_s->enp[i]);
			arg_s->enp[i] = pwd;
			return (&(arg_s->enp[i]));
		}
	}
	return (NULL);
}

/**
 * free_exit - free arguments before exit
 * @args: parameter of type para
 */
void free_exits(p *arg_s)
{
	if (arg_s->line)
	{
		free(arg_s->line);
	}
	if (arg_s->path)
	{
		free(arg_s->path);
	}
	if (arg_s->pwd)
	{
		free(*(arg_s->pwd));
	}
	if (arg_s->older_pwd)
	{
		free(arg_s->older_pwd);
	}
	exit(2);
}
/**
 * _mallocs - handling malloc and freeing exit if malloc failed.
 * @arg_s: parameter of type para
 * @size_num: the size to be maloced
 * Return: the buffer.
 */
char *_mallocs(p *arg_s, int size_num)
{
	char *buff = malloc(size_num);

	if (!buff)
		free_exits(arg_s);
	return (buff);
}
