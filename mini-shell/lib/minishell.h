/*!
 * \file minishell.h
 * \version 0.1
 * \author Monchecourt Pierre <monchecour@cy-tech.fr>
 * \date 25/01/2022
 * \brief Header file minishell
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 1024
#define PS "-> "

void getInput(char **input);

int wordCount(const char *input);

char **splitString(char **input, int length);

char **prepareArgsArray(char **array, int length);

char *buildCmdPath(char *cmd);