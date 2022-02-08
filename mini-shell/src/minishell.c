/*!
 * \file minishell.c
 * \version 0.1
 * \author Monchecourt Pierre <monchecour@cy-tech.fr>
 * \date 25/01/2022
 * \brief Mini shell
 */

#include "../lib/minishell.h"

void getInput(char **command) {
    fgets(command[0], BUFF_SIZE, stdin);
    command[0][strlen(command[0]) - 1] = '\0';
}

int wordCount(const char *input) {
    int i = 0;
    int wc = 0;

    while (input[i] != '\0') {
        if (input[i] == 32) { ++wc; }

        ++i;
    }

    if (input[i - 1] == 32) { --wc; }

    return wc + 1;
}

char **splitString(char **input, int length) {
    int i = 0;
    char **array = malloc(length * sizeof(char *));
    char *token = strtok(*input, " ");
    while (token != NULL) {
        array[i] = token;
        token = strtok(NULL, " ");
        ++i;
    }

    return (array);
}

char **prepareArgsArray(char **array, int length) {
    char **final = malloc((length + 1) * sizeof(char *));
    for (int i = 0; i < length; ++i) {
        final[i] = array[i];
    }

    return (final);
}

char *buildCmdPath(char *cmd, char* path) {
    char *final = malloc(BUFF_SIZE * sizeof(char));
    strcat(final, path);
    strcat(final, cmd);

    return (final);
}

void execCmd(char *cmd, char** args, int option) {

    char *bin = buildCmdPath(cmd, "/bin/");
    char *usr_bin = buildCmdPath(cmd, "/usr/bin/");

    if (option == 0) {
        if (execl(bin, cmd, NULL) == -1) {
            execl(usr_bin, cmd, NULL);
        }
    } else {
        if (execvp(bin, args) == -1) {
            execvp(usr_bin, args);
        }
    }
}

void prompt(char* option) {
    printf("%s", "\033[1;90m");
    printf("%s%s%s%s", option, " ", PS, " ");
    printf("%s", "\033[0m");
}
