#include "shell.h"

/*FIXME: REMOVE
 void test_str_split()
 {
	const char *str = "This is a test string";
	int num_words;
	char **words = wordsplit(str, &num_words);

	if (words != NULL)
	{
		printf("Number of words: %d\n", num_words);
		for (int i = 0; i < num_words; i++)
		{
			printf("Word %d: %s\n", i + 1, words[i]);
		}

		// Free the allocated memory
		free_words(words, num_words);
	}
}*/

/**
 * setTokensFromString - Splits a string into tokens
 * @line: The string to split
 * @args: A pointer to an array of strings
 * Return: 0 on success, -1 on failure
 */
int setTokensFromString(shell_data_dt *data)
{
	char *token;
	unsigned int size = TOKENSIZE, new_size, i = 0;
	char **temp;

	if (_strcmp(data->line, "\n") == 0)
		return -1;

	data->args = malloc(size * sizeof(char *));
	if (data->args == NULL)
		return -1;

	token = strtok(data->line, WHITESPACE);
	while (token)
	{
		data->args[i] = token;

		if (i + 2 >= size)
		{
			new_size = size * 2;
			temp = _realloc(data->args, size * sizeof(char *),
							new_size * sizeof(char *));
			if (temp == NULL)
			{
				free(data->args);
				return -1;
			}

			data->args = temp;
			size = new_size;
		}

		i++;
		token = strtok(NULL, WHITESPACE);
	}

	data->args[i] = NULL;

	return 0;
}

/**
 * freeTokensFromString - Frees the memory allocated by setTokensFromString
 * @args: The array of strings to free
 */
void freeTokensFromString(char **args)
{
	int i = 0;

	while (args[i])
	{
		free(args[i]);
		i++;
	}

	free(args);
}

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
	return num_words;
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
		return 1;
	}
	strncpy(words[wordIndex], str, wordLength);
	words[wordIndex][wordLength] = '\0';
	return 0;
}

char **strsplit(const char *str, int *num_words, const char delim)
{
	int word_index;
	char **words;
	const char *ptr;
	int in_word;
	int word_length;
	int failed;

	if (str == NULL || num_words == NULL || delim == 0)
	{
		return NULL;
	}

	*num_words = str_tok_num(str, delim);

	/* Allocate memory for the array of strings */
	words = (char **)malloc(((*num_words) + 1) * sizeof(char *));
	if (words == NULL)
	{
		return NULL;
	}

	/* Split the string into words */
	word_index = 0;
	ptr = str;
	in_word = 0;
	while (*ptr != '\0')
	{
		if (*ptr == delim)
		{
			if (in_word)
			{
				word_length = ptr - str;
				failed = copyWordAlloc(words, word_index, str, word_length);
				if (failed)
					return NULL;
				word_index++;
				in_word = 0;
			}
			str = ptr + 1; /* Update the start of the next word */
		}
		else
		{
			if (!in_word)
			{
				/* Start of word */
				in_word = 1;
			}
		}
		ptr++;
	}

	/* Handle the last word */
	if (in_word)
	{
		word_length = ptr - str;
		failed = copyWordAlloc(words, word_index, str, word_length);
		if (failed)
			return NULL;
		word_index++;
	}

	return words;
}

char **wordsplit(const char *str, int *num_words)
{
	return strsplit(str, num_words, ' ');
}

void free_words(char **words, int num_words)
{
	int i;

	if (words != NULL)
	{
		for (i = 0; i < num_words; i++)
		{
			free(words[i]);
		}
		free(words);
	}
}