#include "main.h"

/**
* _strtokenizer - split the string into tokens.
* @string: string to be divided.
* @delimeter: delimiter to split the string by.
* Return: token.
*/
char *_strtokenizer(char *string, const char *delimeter)
{
	static char *last;
	char *token;

	if (string != NULL)
	{
		last = string;
	}
	else if (last == NULL)
	{
		return (NULL);
	}
	token = last;
	while (*last != '\0')
	{
		if (*delimeter == *last)
		{
			*last = '\0';
			last++;
			return (token);
		}
		last++;
	}
	last = NULL;
	return (token);
}

/**
* _strdupl - return a pointer to space contain a copy of the string given
 * @string: string given.
 * @arg_s: parameter of type para.
 * Return: a pointer to a duplicate string.
*/
char *_strdupl(p *arg_s, char *string)
{
	char *copy;
	int i, length;

	if (!string)
		return (NULL);
	length = _strlen(string);
	copy = _mallocs(arg_s, length + 1);
	for (i = 0; i <= length; i++)
	{
		copy[i] = string[i];
	}
	return (copy);
}

/**
* _strncomp - compare the first n bytes of str1 and str2.
 * @string1: the first string to be compared.
 * @string2: the second string to be compared.
 * @n: the number of bytes to be compared.
 * Return: 0 if the strings are equal.
*/
int _strncomp(const char *string1, const char *string2, size_t numb)
{
	while (numb-- && (*string1 != '\0' || *string2 != '\0'))
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	return (0);
}

/**
* _strchr - locate a character in a string.
 * @string: string.
 * @ch: character to be located.
 * Return: a pointer to the first occurrence of c. or null if not found.
 */
char *_strchr(char *string, char ch)
{
	int i = 0;

	while (i < _strlen(string))
	{
		if (string[i] == ch)
		{
			return (string + i);
		}
		i++;
	}
	return (NULL);
}
/**
* _strncat - concatenate one sting to another.
 *@destination: the string to be added to.
 *@source: the string to be added.
 *@numb: number of bytes from src.
*Return: the resulting concatenated string.
*/
char *_strncatenate(char *destination, char *source, int numb)
{
	int dest_len = _strlen(destination), i = 0;

	while (i < numb && source[i] != '\0')
	{
		destination[dest_len + i] = source[i];
		i++;
	}
	destination[dest_len + i] = '\0';
	return (destination);
}
