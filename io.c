#include "shell.h"

/**
 * handleInput - Reads a line from stdin
 * @line: A pointer to a string
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
