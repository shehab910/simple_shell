#include "shell.h"

/**
 * isPath - Checks if a string is a path
 * @str: The string to check
 * Return: 1 if true, 0 if false
 */
int isPath(const char *str)
{
	if (_strlen(str) >= 1 && str[0] == '/')
		return (1);
	return (0);
}

/**
 * isRelativePath - Checks if a string is a relative path
 * @str: The string to check
 * Return: 1 if true, 0 if false
 */
int isRelativePath(const char *str)
{
	int isDotSlash = (_strlen(str) >= 2 && str[0] == '.' && str[1] == '/');
	int isDotDotSlash = (_strlen(str) >= 3 && str[0] == '.' && str[1] == '.' &&
						 str[2] == '/');
	if (isDotSlash || isDotDotSlash)
		return (1);
	return (0);
}

/**
 * isDigit - Checks if a character is a digit
 * @c: The character to check
 * Return: 1 if true, 0 if false
 */
int isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

/**
 * charToNumber - Converts a string to a number
 * @c: The string to convert
 * Return: The number, -1 on failure
 */
int charToNumber(char *c)
{
	unsigned int value = 0;
	int numberSign = 1;

	if (c == NULL)
		return (0);
	while (*c)
	{
		if (!isDigit(*c))
			return (-1);
		if (*c == '-')
			numberSign *= -1;
		else
			value = (value * 10) + (*c - '0');
		c++;
	}
	return (numberSign * value);
}
