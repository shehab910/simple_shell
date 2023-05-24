#include "shell.h"

/**
 * str_tok_num - Counts the number of words in a string
 * @str: The string to count the words in
 * @delim: The delimiter to use
 * Return: The number of words in the string
 */
int str_tok_num(const char *str, const char delim)
{
	/* Count the number of words in the string */
	int num_words = 0;
	const char *ptr = str;
	int in_word = 0;

	while (*ptr != '\0')
	{
		if (*ptr == delim)
		{
			in_word = 0;
		}
		else if (!in_word)
		{
			in_word = 1;
			num_words++;
		}
		ptr++;
	}
	return (num_words);
}

int __handleInWord(int *in_word_ref, int *word_index_ref, int *word_length_ref,
				   const char *ptr, const char *str, char **words)
{
	int failed, in_word = *in_word_ref, word_index = *word_index_ref,
				word_length = *word_length_ref;

	if (in_word)
	{
		word_length = ptr - str;
		failed = copyWordAlloc(words, word_index, str, word_length);
		if (failed)
			return (-1);
		word_index++;
		in_word = 0;
	}
	*in_word_ref = in_word;
	*word_index_ref = word_index;
	*word_length_ref = word_length;
	return (0);
}

/**
 * strsplit - Split a string into words
 * @str: The string to split
 * @num_words: The number of words in the string
 * @delim: The delimiter to use
 * Return: An array of strings, NULL if an error occurred
 */
char **strsplit(const char *str, int *num_words, const char delim)
{
	int in_word = 0, word_length, word_index = 0, ret = 0;
	char **words;
	const char *ptr;

	if (str == NULL || num_words == NULL || delim == 0)
		return (NULL);
	*num_words = str_tok_num(str, delim);
	/* Allocate memory for the array of strings */
	words = (char **)malloc(((*num_words) + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	ptr = str;
	while (*ptr != '\0') /* Split the string into words */
	{
		if (*ptr == delim)
		{
			ret = __handleInWord(&in_word, &word_index, &word_length, ptr, str, words);
			if (ret == -1)
				return (NULL);
			str = ptr + 1; /* Update the start of the next word */
		}
		else if (!in_word) /* Start of word */
		{
			str = ptr;
			in_word = 1;
		}
		ptr++;
	}
	/* for the last word */
	ret = __handleInWord(&in_word, &word_index, &word_length, ptr, str, words);
	if (ret == -1)
		return (NULL);
	return (words);
}

/**
 * wordsplit - Split a string into words
 * @str: The string to split
 * @num_words: The number of words in the string
 * Return: An array of strings, NULL if an error occurred
 */
char **wordsplit(const char *str, int *num_words)
{
	return (strsplit(str, num_words, ' '));
}

/**
 * free_words - Free the memory allocated for an array of words
 * @words: The array of words
 * @num_words: The number of words in the array
 */
void free_words(char **words, int num_words)
{
	int i;

	if (words != NULL)
	{
		for (i = 0; i < num_words; i++)
			free(words[i]);
		free(words);
	}
}
