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
    printf("length: %d \n", length);
    char **final = malloc((length + 1) * sizeof(char *));
    for (int i = 0; i < length; ++i) {
//        printf("array[%d] =  %s\n", i, array[i]);
        final[i] = array[i];
    }

    return (final);
}

char *buildCmdPath(char *cmd) {
    char *final = malloc(BUFF_SIZE * sizeof(char));
    strcat(final, "/bin/");
    strcat(final, cmd);

    return(final);
}