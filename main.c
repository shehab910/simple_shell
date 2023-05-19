#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include "strsplit.h"

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
	safePrint("\n");
	safePrint(PROMPT);
}

/**
 * main - check the code
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: Always 0.
 */
int main(int argc, char **argv, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;

	signal(SIGINT, skip);

	safePrint(PROMPT);
	while ((read = getline(&line, &len, stdin)) != -1)
	{
		if (*line == '\n')
		{
			safePrint(PROMPT);
			continue;
		}
		int num_words;
		line[read - 1] = '\0';
		char **args = wordsplit(line, &num_words);

		pid = fork();
		if (pid == 0)
		{
			execve(args[0], args, NULL);
		}
		else
		{
			wait(&status);
		}
		safePrint(PROMPT);
	}
}