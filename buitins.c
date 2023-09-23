#include "main.h"

/**
 * put_char - print char.
 * @ch: the char
 * Return: len.
 */

int put_char(char ch)
{
	return (write(2, &ch, 1));
}

/**
 * put_string - print string.
 * @string: the the string
 * Return: len.
 */

int put_string(char *string)
{
	return (write(2, string, _strlen(string)));
}

/**
 * put_number - print number
 * @numb: number to be printed
 */

void put_number(int numb)
{
	unsigned int n1;

	if (numb < 0)
	{
		n1 = -numb;
		put_char('-');
	}
	else
		n1 = numb;

	if (n1 / 10)
		put_number(n1 / 10);

	put_char((n1 % 10) + '0');
}

/**
 * num_len - return the number len
 * @n: number to be printed
 * Return: len.
 */

int num_length(int numb)
{
	int length = 1;

	put_number(numb);
	if (numb < 0)
		length++;
	while (numb /= 10)
		length++;

	return (length);
}

/**
 * specifiers - print argument
 * @ch: the specifier
 * @arg_s: the arguments
 * Return: len.
 */

int specifiers(char ch, va_list arg_s)
{
	int length = 0;
	char *string;

	if (ch == 'c')
		length += put_char(va_arg(arg_s, int));
	else if (ch == 's')
	{
		string = va_arg(arg_s, char *);
		length += put_string(STRING);
	}
	else if (ch == 'i' || ch == 'd')
		length += num_length(va_arg(arg_s, int));
	else if (ch == '%')
		length += put_char('%');
	else
	{
		length += put_char('%');
		length += put_char(ch);
	}
	return (length);
}
