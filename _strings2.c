#include "main.h"

/**
 * _strlen - determine the length of a string.
 * @string: a string of char.
 * Return: the length of a string.
 */

int _strlen(char *string)
{
	int i = 0;

	while (string[i] != 0)
	{
		i++;
	}

	return (i);
}

/**
 * _strcat - function to concatenates two strings.
 * @destination: string to be concatenated.
 * @source: string to be concatenated to.
 * Return: a pointer to the resulting string.
 */

char *_strcat(char *destination, char *source)
{
	int dest_len = _strlen(destination), i = 0;

	while (source[i] != '\0')
	{
		destination[dest_len + i] = source[i];
		i++;
	}
	destination[dest_len + i] = '\0';
	return (destination);
}

/**
 *_strcomp - compares two strings.
 *@string1: string to be compared with.
 *@string2: string to be compared.
 * Return: 0 if str1, str2 equals.
 */

int _strcomp(char *string1, char *string2)
{
	int i = 0;

	while (string1[i] != 0 || string2[i] != 0)
	{
		if (string1[i] != string2[i])
			return (string1[i] - string2[i]);
		i++;
	}
	return (0);
}

/**
 * tostringify - change a number into a string.
 * @string: empty buffer.
 * @numb: int to be changed into a string.
*/

void tostringify(char *string, int numb)
{
	int i, length = 0, num = numb;

	if (!num)
	{
		string[0] = '0';
		string[1] = '\0';
		return;
	}
	while (num)
	{
		length++;
		num /= 10;
	}
	for (i = 0; i < length; i++)
	{
		string[length - (i + 1)] = num % 10 + '0';
		num /= 10;
	}
	string[length] = '\0';
}

/**
 * rev_comp - compare two strings backward
 * @string1: first string.
 * @string2: second string
 * Return: 1 success, 0 failure
*/
int rev_comp(char *string1, char *string2)
{
	int length1 = (_strlen(string1) - 1), length2 = (_strlen(string2) - 1), i;

	if (length2 > length1)
		return (0);
	for (i = length2; i >= 0; i--)
	{
		if (string1[length1] != string2[i])
			return (0);
		length1--;
	}
	return (1);
}
