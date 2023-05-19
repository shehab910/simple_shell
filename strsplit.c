#include <stdlib.h>
#include <string.h>

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

int str_tok_num(const char *str, const char delim)
{
	// Count the number of words in the string
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

int alloc_copy_word(char **words, int word_index, const char *str, int word_length)
{
	words[word_index] = (char *)malloc((word_length + 1) * sizeof(char));
	if (words[word_index] == NULL)
	{
		// Memory allocation failed, free previously allocated memory
		for (int i = 0; i < word_index; i++)
		{
			free(words[i]);
		}
		free(words);
		return 1;
	}
	strncpy(words[word_index], str, word_length);
	words[word_index][word_length] = '\0';
	return 0;
}

char **strsplit(const char *str, int *num_words, const char delim)
{
	if (str == NULL || num_words == NULL || delim == 0)
	{
		return NULL;
	}

	*num_words = str_tok_num(str, delim);

	// Allocate memory for the array of strings
	char **words = (char **)malloc(((*num_words) + 1) * sizeof(char *));
	if (words == NULL)
	{
		return NULL;
	}

	// Split the string into words
	int word_index = 0;
	const char *ptr = str;
	int in_word = 0;
	while (*ptr != '\0')
	{
		if (*ptr == delim)
		{
			if (in_word)
			{
				int word_length = ptr - str;
				int failed = alloc_copy_word(words, word_index, str, word_length);
				if (failed)
					return NULL;
				word_index++;
				in_word = 0;
			}
			str = ptr + 1; // Update the start of the next word
		}
		else
		{
			if (!in_word)
			{
				// Start of word
				in_word = 1;
			}
		}
		ptr++;
	}

	// Handle the last word
	if (in_word)
	{
		int word_length = ptr - str;
		int failed = alloc_copy_word(words, word_index, str, word_length);
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
	if (words != NULL)
	{
		for (int i = 0; i < num_words; i++)
		{
			free(words[i]);
		}
		free(words);
	}
}