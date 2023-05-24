#include "shell.h"

/**
 * skip - Skips the INT signal
 * @sig: The signal
 */
void skip(int sig)
{
	if (sig == SIGINT)
	{
		SAFE_PRINT("\n");
		SAFE_PRINT(PROMPT);
	}
}

/**
 * __exit - Exits the shell after freeing the shell data
 * @shellData: The shell data
 * @exit_status: The exit status
 */
void __exit(shell_data_dt *shellData, int exit_status)
{
	freeShellData(shellData);
	exit(exit_status);
}

/**
 * handleCommand - Handles the execution of a command
 * @shellData: The shell data
 * @exit_status: The exit status
 * @envp: The environment variables
 */
void handleCommand(shell_data_dt *shellData, int *exit_status, char **envp)
{
	pid_t pid;
	int status, ret = 0;

	pid = fork();
	if (pid == 0 && shellData->cmd != NULL)
	{
		signal(SIGINT, SIG_DFL);
		ret = execve(shellData->cmd, shellData->args, envp);
		if (ret == -1)
		{
			printNotFoundErr(shellData->shellName, shellData->args[0]);
			*exit_status = 127;
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			*exit_status = WEXITSTATUS(status);
		/* else if (WIFSIGNALED(status)) */
		/* { */
		/* int signal_num = WTERMSIG(status); */
		/* printf("Child process terminated by signal: %d\n", signal_num); */
		/* } */
	}
}

/**
 * checkBuiltins - Checks if the command is a builtin
 * @shellData: The shell data
 * @exit_status: The exit status
 * @envp: The environment variables
 * Return: CONTINUE if the command is a builtin, 0 otherwise
 */
int checkBuiltins(shell_data_dt *shellData, int *exit_status, char **envp)
{
	if (_strcmp(shellData->args[0], "exit") == 0)
	{
		return (execExitCommand(shellData, exit_status));
	}
	else if (_strcmp(shellData->args[0], "env") == 0)
	{
		executeEnvCommand(envp);
		return (CONTINUE);
	}
	return (0);
}

/**
 * main - Entry point for the hsh shell
 * @argc: number of arguments
 * @argv: array of arguments
 * @envp: array of environment variables
 * Return: Always 0.
 */
int main(int argc, char **argv, char **envp)
{
	/* !FIXME: remove all fixemes and TODOs */
	shell_data_dt shellData;
	int exit_status = 0, ret;

	(void)argc;
	initShellData(&shellData);
	if (isatty(STDIN_FILENO))
		shellData.shellName = "hsh";
	else
		shellData.shellName = (const char *)argv[0];
	signal(SIGINT, skip);
	while (1 == 1)
	{
		freeShellData(&shellData);
		if (handleInput(&shellData) < 0)
		{
			if (isatty(STDIN_FILENO))
				SAFE_PRINT("\n");
			__exit(&shellData, exit_status);
		}
		if (setTokensFromString(&shellData) < 0)
			continue;
		if (shellData.args[0] == NULL)
			continue;
		ret = checkBuiltins(&shellData, &exit_status, envp);
		if (ret == CONTINUE)
			continue;
		shellData.cmd = _which(shellData.args[0]);
		if (shellData.cmd == NULL)
		{
			printNotFoundErr(shellData.shellName, shellData.args[0]);
			if (isatty(STDIN_FILENO))
				continue;
			exit_status = 127;
		}
		handleCommand(&shellData, &exit_status, envp);
	}
	return (exit_status);
}
