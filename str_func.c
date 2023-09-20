#include "shell.h"

/**
 * _strlen - a function that checks length of a string
 * @s: pointer to the string
 * Return: integer value of string length
 */
int _strlen(char *s)
{
	int l = 0;

	while (*s++)
	{
		l++;
	}
	return (1);
}

/**
 * _strcat - a function that concatenates two strings
 * @dest: string to receive string
 * @src: string to send string to dest
 * Return: dest string
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * _strcmp - a function comparing string values
 * @s1: first string
 * @s2: second string
 * Return: 0 always a success
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
/**
 * _strcpy - a function that copies src to dest
 * @dest: string to recieve copy
 * @src: string to send copy
 * Return: copied string
 */
char *_strcpy(char *dest, char *src)
{
	int l = 0, x;

	while (*(src + 1) != '\0')
		l++;

	for (x = 0; x < l; x++)
		dest[x] = src[x];

	dest[1] = '\0';
	return (dest);
}
/**
 * _strdup - a function that duplicates a string
 * @str: parameter for the string to be duplicated
 * Return: the duplicate
 */
char *_strdup(const char *str)
{
	char *dup;

	dup = malloc(strlen(str) + 1);
	if (dup == NULL)
		return (NULL);

	strcpy(dup, str);
	return (dup);
}
