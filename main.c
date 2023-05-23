#include "shell.h"

ssize_t safePrint(char *str)
{
	return write(STDOUT_FILENO, str, strlen(str));
}

ssize_t safePrintErr(const char *str)
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
	int exit_status = 0;

	initShellData(&shellData);
	if (isatty(STDIN_FILENO))
		shellData.shellName = "hsh";
	else
		shellData.shellName = (const char *)argv[0];
	/*
	TODO:
	1. check if the file path going to execve exist or not

	*/
	signal(SIGINT, skip);

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
		if (shellData.args[0] == NULL)
		{
			freeShellData(&shellData);
			continue;
		}

		char *cmd = _which(shellData.args[0]);
		if (cmd == NULL)
		{
			SAFE_PRINT_ERR(shellData.shellName);
			SAFE_PRINT_ERR(": 1: ");
			SAFE_PRINT_ERR(shellData.args[0]);
			SAFE_PRINT_ERR(": not found\n");
			freeShellData(&shellData);
			if (isatty(STDIN_FILENO))
				continue;
			exit_status = 127;
		}

		pid = fork();
		if (pid == 0 && cmd != NULL)
		{
			signal(SIGINT, SIG_DFL);
			int ret = execve(cmd, shellData.args, envp);
			if (ret == -1)
			{
				safePrintErr(shellData.shellName);
				safePrintErr(": 1: ");
				safePrintErr(shellData.args[0]);
				safePrintErr(": not found\n");
				exit_status = 127;
			}
		}
		else if (pid > 0)
		{
			// Parent process
			waitpid(pid, &status, 0);

			if (WIFEXITED(status))
			{
				exit_status = WEXITSTATUS(status);
			}
			// else if (WIFSIGNALED(status))
			// {
			// 	int signal_num = WTERMSIG(status);
			// 	printf("Child process terminated by signal: %d\n", signal_num);
			// }
		}
		// free_data(&shellData);
	}
	return exit_status;
}