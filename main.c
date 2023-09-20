#include "shell.h"

/**
 * main - function that executes a simple shell
 * Return: 0 a success
 */
int main(void)
{
	char command[1024], *parameters[64];

	while (1)
	{
		type_prompt();
		read_command(command, parameters);
		execute_command(command, parameters);
	}
	return (0);
}
