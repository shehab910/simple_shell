#include "shell.h"

/**
 * arrayFill - Fills an array with a given element, length
 * @array: A pointer to array to be filled
 * @element: The element to fill the array with
 * @length: The length of the array
 * Return: A pointer to the filled array
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

/*! TODO: CHANGE */

/**
 * _memcpy - Copies memory area
 * @dest: A pointer to the destination memory area
 * @src: A pointer to the source memory area
 * @n: The number of bytes to copy
 * Return: A pointer to the copied memory area @dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

/*! TODO: CHANGE */

/**
 * _realloc - Reallocates a memory block using malloc and free
 * @ptr: A pointer to the memory previously allocated
 * @old_size: The size of the allocated space for ptr
 * @new_size: The size of the new memory block
 * Return: A pointer to the new memory block, NULL on failure
 */
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
	{
		free(ptr);
		return (NULL);
	}
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
 * copyWordAlloc - Copies a word into a newly allocated string
 * @words: The array of strings to copy the word into
 * @wordIndex: The index of the word to copy
 * @str: The string to copy from
 * @wordLength: The length of the word to copy
 * Return: 0 on success, 1 on failure
 */
int copyWordAlloc(char **words, int wordIndex, const char *str, int wordLength)
{
	int i;

	words[wordIndex] = malloc((wordLength + 1) * sizeof(char));
	if (words[wordIndex] == NULL)
	{
		for (i = 0; i < wordIndex; i++)
			free(words[i]);
		free(words);
		return (1);
	}
	strncpy(words[wordIndex], str, wordLength);
	words[wordIndex][wordLength] = '\0';
	return (0);
}
