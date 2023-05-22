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
	shell_data_dt shellData;
	pid_t pid;
	int status;

	initShellData(&shellData);
	/*
	TODO:
	1. check if the file path going to execve exist or not


	*/
	signal(SIGINT, skip);

	// if (isatty(STDIN_FILENO))
	// 	isPipedin = 1;

	// if (isPipedin)
	// 	safePrint(PROMPT);

	while (1 == 1)
	{
		if (handleInput(&shellData) < 0)
		{
			if (isatty(STDIN_FILENO))
				SAFE_PRINT("\n");
			break;
		}
		if (setTokensFromString(&shellData) < 0)
		{
			freeShellData(&shellData);
			continue;
		}

		char *cmd = _which(shellData.args[0]);

		pid = fork();
		if (pid == 0)
		{
			int ret = execve(cmd, shellData.args, envp);
			if (ret == -1)
			{
				safePrintErr(shellData.args[0]);
				// safePrintErr(": 1: ");
				// safePrintErr(args[1]);
				// safePrintErr(": not found\n");
				// return (127);
			}
		}
		else
		{
			wait(&status);
			// free_words(args, num_words);
			// if (isPipedin)
			// 	safePrint(PROMPT);
		}
		// free_data(&shellData);
	}
}