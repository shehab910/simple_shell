#include "shell.h"

/**
 * arrayFill - Fills an array with a given element, length
 * @array: A pointer to array to be filled
 * @element: The element to fill the array with
 * @length: The length of the array
 */
void *arrayFill(void *array, int element, unsigned int length)
{
	char *tmpPtr = array;
	unsigned int i = 0;

	while (i < length)
	{
		*tmpPtr = element;
		tmpPtr++;
		i++;
	}
	return (array);
}

//! TODO: CHANGE
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

//! TODO: CHANGE
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *result;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	result = malloc(new_size);
	if (result == NULL)
		return (NULL);
	if (ptr == NULL)
	{
		arrayFill(result, '\0', new_size);
		free(ptr);
	}
	else
	{
		_memcpy(result, ptr, old_size);
		free(ptr);
	}
	return (result);
}

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
