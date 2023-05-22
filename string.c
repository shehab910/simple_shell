#include "shell.h"
/**
 * _strlen - returns the length of a string.
 * @s: string to be measured
 * Return: length of a string
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

/**
 * _strcmp -  compares two strings.
 * @s1: pointer to the first string
 * @s2: pointer to the second string
 * Return: 0 if the strings can be considered identical,
 * otherwise return difference between
 * first two differing bytes
 */
int _strcmp(const char *s1, const char *s2)
{
	if (s1 == NULL || s2 == NULL)
	{
		if (s1 == s2)
			return 0;
		else if (s1 == NULL)
			return -1;
		else
			return 1;
	}

	int i;
	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}

	if (s1[i] == '\0' && s2[i] != '\0')
		return -1;
	else if (s1[i] != '\0' && s2[i] == '\0')
		return 1;
	else
		return 0;
}
