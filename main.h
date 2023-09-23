#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define STRING ((string) ? string : "(null)")

/**
 * struct para - structure
 * @enp: array of enviromental variables.
 * @pwd: the working directory
 * @line: input.
 * @path: the path
 * @older_pwd: the old working directory
 * @num_token: the number of token
 * @num_path: the number of token in the path
 * @status_num: the status of the last command
 * @file_name: the type of stream
 * @counter: the count of operation
 * @pi:the shell id
 * @shell_user: the name of the shell
 */
typedef struct p
{
	char **enp;
	char **pwd;
	char *line;
	char *shell_user;
	char *path;
	char *older_pwd;
	int num_token;
	int num_path;
	int status_num;
	int counter;
	int file_name;
	int pi;
} p;

int _strlen(char *string);
void handle_d(char **input_line, p *arg_s);
int _printfs(const char *format, ...);
int put_char(char ch);
int put_string(char *string);
void put_number(int numb);
int num_length(int numb);
int specifiers(char ch, va_list arg_s);
int _strlen(char *string);
char *_strcat(char *destination, char *source);
char *_strdupl(p *arg_s, char *string);
int _strncomp(const char *string1, const char *string2, size_t numb);
char *_strtokenizer(char *string, const char *delimeter);
char *_strchr(char *string, char ch);
char *_strncatenate(char *destination, char *source, int numb);
int _strcomp(char *string1, char *string2);
void tostringify(char *string, int numb);
int _excecute(p *arg_s, char *buffer);
void *_reallocs(void *pointer, unsigned int older_size,
		unsigned int newest_size);
int _atoi(char *string);
int _exit_shell_(p *arg_s);
int _commands_(p *arg_s);
int _inputs(p *arg_s, int arr, int *semi);
int tokens(char *line_s, char *delimeter);
int rev_comp(char *string1, char *string2);
int _env(p *arg_s);
ssize_t _getline(p *arg_s);
void spaces(char **line_s, p *arg_s);
char *_get_environ(char **enp, char *envir, int length);
int handle_inputs(p *arg_s);
void handle_dollar_sign(char *buffer_s, char **dollars, p *arg_s);
char *handle_reallocs(p *agr_s, char *buffer_s, int *buffer_size, int extras,
int maximize);
char **gets_PWD(p *arg_s);
int cd(p *arg_s);
void pwd_changer(p *arg_s);
void free_exits(p *arg_s);
char *_mallocs(p *arg_s, int size_num);
char *mallocs2(char *line_ptr, p *arg_s, int size_);

#endif
