#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "shell.h"
// bash command to rename a file removing .passed
//
#define PATH_DELIM ':'
//! TODO: handle errors without using printf & remove sprintf
char *_which(const char *command)
{
	struct stat st;

	if (command == NULL)
	{
		return NULL;
	}
	char *path = getenv("PATH");
	if (path == NULL)
	{
		printf("Error: PATH environment variable not found.\n");
		return NULL;
	}
	if (stat(command, &st) == 0)
		return (char *)(command);

	char *_path = strdup(path);

	int num_tokens = -1;
	char **tokens = strsplit(_path, &num_tokens, PATH_DELIM);
	if (tokens == NULL || num_tokens == -1)
	{
		free_words(tokens, num_tokens);
		printf("Error: Memory allocation failed.\n");
		return NULL;
	}

	for (int i = 0; i < num_tokens; i++)
	{
		char *file_path = malloc(strlen(tokens[i]) + strlen(command) + 2);
		if (file_path == NULL)
		{
			free_words(tokens, num_tokens);
			printf("Error: Memory allocation failed.\n");
			return NULL;
		}
		sprintf(file_path, "%s/%s", tokens[i], command);
		if (stat(file_path, &st) == 0)
		{
			free_words(tokens, num_tokens);
			return file_path;
		}

		free(file_path);
	}
	free_words(tokens, num_tokens);
	return NULL;
}
