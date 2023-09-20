#include "shell.h"

/**
 * type_prompt - a function that prints the shell prompt
 * Return: void
 */
void type_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		const char *prompt;

		prompt = "$";
		write(STDOUT_FILENO, prompt, 2);
		fflush(stdout);
	}
}
