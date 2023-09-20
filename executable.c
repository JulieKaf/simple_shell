#include "shell.h"
/**
 * execute_external_command - a function that executes external commands
 * @command: parameter to store external command
 * @parameters: paramter to store parameters for external command
 * Return: void
 */
void execute_external_command(char *command, char **parameters)
{
	char cmd[100];
	char **env;
	pid_t pid;
	int i;

	env = environ;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		_strcpy(cmd, "/bin/");
		_strcat(cmd, command);
		execve(cmd, parameters, env);

		perror("error");
		exit(1);
	}
	else
	{
		wait(NULL);
		for (i = 0; parameters[i] != NULL; i++)
			free(parameters[i]);
	}
}
