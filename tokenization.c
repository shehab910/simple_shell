#include "shell.h"

/**
 * setTokensFromString - Splits a string into tokens
 * @data: The shell data structure
 * Return: 0 on success, -1 on failure
 */
int setTokensFromString(shell_data_dt *data)
{
	char *token;
	unsigned int size = TOKENSIZE, new_size, i = 0;
	char **temp;

	if (_strcmp(data->line, "\n") == 0)
		return (-1);

	data->args = malloc(size * sizeof(char *));
	if (data->args == NULL)
		return (-1);

	token = strtok(data->line, WHITESPACE);
	while (token)
	{
		data->args[i] = strdup(token);

		if (i + 2 >= size)
		{
			new_size = size * 2;
			temp = _realloc(data->args, size * sizeof(char *),
							new_size * sizeof(char *));
			if (temp == NULL)
			{
				return (-1);
			}

			data->args = temp;
			size = new_size;
		}
		i++;
		token = strtok(NULL, WHITESPACE);
	}

	data->args[i] = NULL;

	return (0);
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
