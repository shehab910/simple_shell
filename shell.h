#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 512
#define TOKENSIZE 64
#define SAFE_PRINT(c) (write(STDOUT_FILENO, c, _strlen(c)))
#define SAFE_PRINT_ERR(c) (write(STDERR_FILENO, c, _strlen(c)))
#define PROMPT "$ "
#define SUCCESS (1)
#define FAIL (-1)
#define CONTINUE (255)
#define WHITESPACE " \n\t\r\a\v"

/**
 * struct shell_data - Struct for shell data
 * @shellName: The name of the shell
 * @line: The line of input from the user
 * @args: The arguments from the line of input
 * @cmd: The command from the line of input
 */
typedef struct shell_data
{
	const char *shellName;
	char *line;
	char **args;
	char *cmd;
	/* char *error_msg; */
	/* char *oldpwd; */
	/* unsigned long int index; */
	/* char *env; */
} shell_data_dt;

int str_tok_num(const char *str, const char delim);
int copyWordAlloc(char **words, int word_index, const char *str, int word_len);
char **strsplit(const char *str, int *num_words, const char delim);
char **wordsplit(const char *str, int *num_words);
void free_words(char **words, int num_words);
char *_which(const char *command);
void freeTokensFromString(char **args);
int setTokensFromString(shell_data_dt *data);
int handleInput(shell_data_dt *data);
void initShellData(shell_data_dt *data);
int freeShellData(shell_data_dt *data);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memcpy(char *dest, char *src, unsigned int n);
int _strlen(const char *s);
void *arrayFill(void *array, int element, unsigned int length);
int _strcmp(const char *s1, const char *s2);
int isPath(const char *str);
int isRelativePath(const char *str);
int charToNumber(char *c);
void printNotFoundErr(const char *shellName, char *cmd);
int execExitCommand(shell_data_dt *shellData, int *exit_status);
void executeEnvCommand(char **envp);
int checkBuiltins(shell_data_dt *shellData, int *exit_status, char **envp);
void handleCommand(shell_data_dt *shellData, int *exit_status, char **envp);
void __exit(shell_data_dt *shellData, int exit_status);
void skip(int sig);

#endif
