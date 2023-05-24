#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "shell.h"

#define PATH_DELIM ':'

/*! TODO: handle errors without using printf & remove sprintf */
char *_which(const char *command)
{
	char *_path;
	char *path;
	int i;
	int num_tokens;
	struct stat st;
	char **tokens;
	char *file_path;

	if (command == NULL)
		return NULL;

	if ((isPath(command) || isRelativePath(command)) && stat(command, &st) == 0)
		return (char *)strdup(command);

	path = getenv("PATH");
	if (path == NULL || _strlen(path) == 0)
	{
		return NULL; /* strdup(command); */
	}

	_path = strdup(path);

	num_tokens = -1;
	tokens = strsplit(_path, &num_tokens, PATH_DELIM);
	if (tokens == NULL || num_tokens == -1)
	{
		free_words(tokens, num_tokens);
		printf("Error: Memory allocation failed.\n");
		free(_path);
		return NULL;
	}

	for (i = 0; i < num_tokens; i++)
	{
		file_path = malloc(strlen(tokens[i]) + strlen(command) + 2);
		if (file_path == NULL)
		{
			free_words(tokens, num_tokens);
			printf("Error: Memory allocation failed.\n");
			free(_path);
			return NULL;
		}
		sprintf(file_path, "%s/%s", tokens[i], command);
		if (stat(file_path, &st) == 0)
		{
			free(_path);
			free_words(tokens, num_tokens);
			return file_path;
		}

		free(file_path);
	}
	free(_path);
	free_words(tokens, num_tokens);
	return NULL;
}
