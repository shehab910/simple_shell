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

#define TOKENSIZE 64
#define DELIMITER " \n\t\r\a\v"

int str_tok_num(const char *str, const char delim);
int alloc_copy_word(char **words, int word_index, const char *str, int word_length);
char **strsplit(const char *str, int *num_words, const char delim);
char **wordsplit(const char *str, int *num_words);
void free_words(char **words, int num_words);
char *_which(const char *command);
int setTokensFromString(char *line, char ***args);
void freeTokensFromString(char **args);

#endif