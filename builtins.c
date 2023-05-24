#include "shell.h"

/**
 * executeEnvCommand - Executes the env command
 * @envp: The environment variables
 */
void executeEnvCommand(char **envp)
{
	int i = 0;

	while (envp[i] != NULL)
	{
		SAFE_PRINT(envp[i]);
		SAFE_PRINT("\n");
		i++;
	}
}

/**
 * execExitCommand - Executes the exit command
 * @shellData: The shell data
 * @exit_status: The exit status
 * Return: Does not return
 */

int execExitCommand(shell_data_dt *shellData, int *exit_status)
{
	if (shellData->args[1] != NULL) /* if shell.args has 2 arguments */
	{
		if (charToNumber(shellData->args[1]) <= -1) /* if shell.args[1] is a num */
		{
			SAFE_PRINT_ERR(shellData->shellName);
			SAFE_PRINT_ERR(": 1: exit: Illegal number: ");
			SAFE_PRINT_ERR(shellData->args[1]);
			SAFE_PRINT_ERR("\n");
			*exit_status = 2;
			return (CONTINUE);
		}
		*exit_status = charToNumber(shellData->args[1]);
	}
	__exit(shellData, *exit_status);
	return (0);
}
