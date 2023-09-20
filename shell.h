#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>

extern char **environ;

void type_prompt(void);
int handle_builtins(char *command, char **parameters);
void read_command(char cmd[], char *par[]);
void execute_command(char *command, char **parameters);
void execute_external_command(char *command, char **parameters);

int _strlen(char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);

int _atoi(char *s);

#endif
