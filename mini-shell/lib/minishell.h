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
#include <sys/utsname.h>

#define BUFF_SIZE 1024
#define PS "->"

/**
 * Gets input form command-line
 * @param input A string, as an pointer of pointer of char to be able to use its reference
 */
void getInput(char **input);

/**
 * Counts number of words in an input
 * @param input A string
 * @return An int, as the number if words in an input
 */
int wordCount(const char *input);

/**
 * Split a string with multiple words into an array
 * @param input A string
 * @param length The number of words in the string
 * @return An array of string, as the input split
 */
char **splitString(char **input, int length);

/**
 * Adds NULL to split input to be able to use it with execvp
 * @param array The split input array
 * @param length The length of the split input array
 * @return An array of string as the split inout array with NULL added at the end
 */
char **prepareArgsArray(char **array, int length);

/**
 * Builds the command executable path
 * @param cmd The command
 * @param path The specified path
 * @return A string, as the command executable path which is path and cmd concatenated
 */
char *buildCmdPath(char *cmd, char *path);

/**
 * Executes a command : if executable file is not in /bin/, tries in /usr/bin/
 * @param cmd The command
 * @param args The arguments array, default NULL
 * @param option An integer, 0 if there are no arguments, 1 otherwise
 */
void execCmd(char *cmd, char **args, int option);

/**
 * Prints a prompt
 * @param hostname A string, as hostname
 * @param hostname A string, as current working directory
 */
void prompt(char* hostname, char* cwd);