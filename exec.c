#include "shell.h"

/**
 * execute_command - a function that executes executable commands
 * @command: parameter to store built in commands
 * @parameters: parameter to store executable commands
 * Return: void
 */

void execute_command(char *command, char **parameters)
{
	pid_t pid;
	char **env;
	int i;

	env = environ;
	if (handle_builtins(command, parameters))
		return;
	if (_strcmp(command, "/bin/ls") == 0)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			execve(command, parameters, env);
			perror("error");
			exit(1);
		}
		else
		{
			wait(NULL);
			for (i = 0; parameters[i] != NULL; i++)
			free(parameters[i]);
			return;
		}
	}
	execute_external_command(command, parameters);
}


