#include "shell.h"

/**
 * read_command - a function that reads and tokenizes user input
 * @cmd: an array storing user commands
 * @par: an array of pointers to user parameters
 * Return: void
 */
void read_command(char cmd[], char *par[])
{
	char *pch, *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int i = 0, j;

	signal(SIGINT, SIG_IGN);
	nread = getline(&line, &len, stdin);

	if (nread != -1)
	{
		line[nread - 1] = '\0';
		if (strlen(line) > 0)
		{
			pch = strtok(line, " ");
			while (pch != NULL)
			{
				par[i++] = _strdup(pch);
				pch = strtok(NULL, " ");
			}
			_strcpy(cmd, par[0]);
			par[i] = NULL;
		}
		free(line);
	}
	else
	{
		free(line);
		for (j = 0; j < i; j++)
			free(par[j]);
		exit(EXIT_SUCCESS);
	}
}
