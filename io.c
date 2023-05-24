#include "shell.h"

/**
 * handleInput - reads input from stdin
 * @shellData: A pointer to a shell_data_dt struct
 * Return: 0 on success, -1 on failure
 */
int handleInput(shell_data_dt *shellData)
{
	char *currentChar, *endOfBuffer, input_char;
	ssize_t size = BUFSIZE, read_st, length, new_size;

	shellData->line = malloc(size * sizeof(char));
	if (shellData->line == NULL)
		return (FAIL);
	if (isatty(STDIN_FILENO))
		SAFE_PRINT(PROMPT);
	/* ! TODO - refactor this for loop */
	for (currentChar = shellData->line, endOfBuffer = shellData->line + size;;)
	{
		read_st = read(STDIN_FILENO, &input_char, 1);
		if (read_st == 0)
			return (FAIL);
		*currentChar++ = input_char;
		if (input_char == '\n')
		{
			*currentChar = '\0';
			return (SUCCESS);
		}
		if (currentChar + 2 >= endOfBuffer)
		{
			new_size = size * 2;
			length = currentChar - shellData->line;
			shellData->line = _realloc(shellData->line, size * sizeof(char),
									   new_size * sizeof(char));
			if (shellData->line == NULL)
				return (FAIL);
			size = new_size;
			endOfBuffer = shellData->line + size;
			currentChar = shellData->line + length;
		}
	}
}

/**
 * safePrint - Prints a string to stdout
 * @str: The string to print
 * Return: The number of bytes printed
 */
ssize_t safePrint(char *str)
{
	return (write(STDOUT_FILENO, str, strlen(str)));
}

/**
 * safePrintErr - Prints a string to stderr
 * @str: The string to print
 * Return: The number of bytes printed
 */
ssize_t safePrintErr(const char *str)
{
	return (write(STDERR_FILENO, str, strlen(str)));
}

/**
 * printNotFoundErr - Prints a not found error message
 * @shellName: The name of the shell
 * @cmd: The command that was not found
 */
void printNotFoundErr(const char *shellName, char *cmd)
{
	SAFE_PRINT_ERR(shellName);
	SAFE_PRINT_ERR(": 1: ");
	SAFE_PRINT_ERR(cmd);
	SAFE_PRINT_ERR(": not found\n");
}
