#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "shell.h"

#define PATH_DELIM ':'

/*! TODO: handle errors without using printf & remove sprintf */

/**
 * _whichFreeHandler - free memory allocated by _which
 * @_path: The path to free
 * @tokens: The tokens to free
 * @num_tokens: The number of tokens to free
 */
void _whichFreeHandler(char *_path, char **tokens, int num_tokens)
{
	free(_path);
	free_words(tokens, num_tokens);
}

/**
 * _which - locate a command & handle 3 cases
 * 1. command is a path
 * 2. command is a short hand
 * 3. command is a builtin
 * @command: The command to locate
 * Return: The path to the command, NULL if not found
 */
char *_which(const char *command)
{
	char *_path, *path, *file_path;
	char **tokens;
	int i, num_tokens;
	struct stat st;

	if (command == NULL)
		return (NULL);
	if ((isPath(command) || isRelativePath(command)) && stat(command, &st) == 0)
		return ((char *)strdup(command));
	path = getenv("PATH");
	if (path == NULL || _strlen(path) == 0)
	{
		return (NULL); /* strdup(command); */
	}
	_path = strdup(path);
	num_tokens = -1;
	tokens = strsplit(_path, &num_tokens, PATH_DELIM);
	if (tokens == NULL || num_tokens == -1)
	{
		_whichFreeHandler(_path, tokens, num_tokens);
		return (NULL);
	}
	for (i = 0; i < num_tokens; i++)
	{
		file_path = malloc(strlen(tokens[i]) + strlen(command) + 2);
		if (file_path == NULL)
		{
			_whichFreeHandler(_path, tokens, num_tokens);
			return (NULL);
		}
		sprintf(file_path, "%s/%s", tokens[i], command);
		if (stat(file_path, &st) == 0)
		{
			_whichFreeHandler(_path, tokens, num_tokens);
			return (file_path);
		}
		free(file_path);
	}
	_whichFreeHandler(_path, tokens, num_tokens);
	return (NULL);
}
