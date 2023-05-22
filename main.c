#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

#define PROMPT "$ "

ssize_t safePrint(char *str)
{
	return write(STDOUT_FILENO, str, strlen(str));
}

ssize_t safePrintErr(char *str)
{
	return write(STDERR_FILENO, str, strlen(str));
}

void skip(int sig)
{
	(void)sig;
}

/**
 * main - check the code
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: Always 0.
 */
int main(int argc, char **argv, char **envp)
{
	// !FIXME: remove all fixemes and TODOs
	(void)argc;
	(void)argv;
	char *line = NULL;
	size_t len = 0;
	ssize_t read_size;
	pid_t pid;
	int status;
	int isPipedin = 0;

	/*
	TODO:
	1. check if the file path going to execve exist or not


	*/
	signal(SIGINT, skip);

	if (isatty(STDIN_FILENO))
		isPipedin = 1;

	if (isPipedin)
		safePrint(PROMPT);

	while ((read_size = getline(&line, &len, stdin)) != -1)
	{
		if (strcmp(line, "\n") == 0)
		{
			if (isPipedin)
				safePrint(PROMPT);
			continue;
		}

		line[read_size - 1] = '\0';

		int num_words;
		char **args = wordsplit(line, &num_words);
		if (args == NULL)
		{
			free(line);
			return (0);
		}
		char *cmd = _which(args[0]);

		pid = fork();
		if (pid == 0)
		{
			int ret = execve(cmd, args, envp);
			if (ret == -1)
			{
				safePrintErr(args[0]);
				// safePrintErr(": 1: ");
				// safePrintErr(args[1]);
				// safePrintErr(": not found\n");
				// return (127);
			}
		}
		else
		{
			wait(&status);
			free_words(args, num_words);
			if (isPipedin)
				safePrint(PROMPT);
		}
		free(line);
	}
}