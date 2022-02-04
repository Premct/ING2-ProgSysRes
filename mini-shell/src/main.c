/*!
 * \file main.c
 * \version 0.1
 * \author Monchecourt Pierre <monchecour@cy-tech.fr>
 * \date 25/01/2022
 * \brief Main file
 */

#include <wait.h>
#include "../lib/minishell.h"

/*!
 * \fn main
 * \param argc Arguments count
 * \param argv Arguments array
 * \version 0.1
 * \author Monchecourt Pierre <monchecour@cy-tech.fr>
 * \date 25/01/2022
 * \brief Main function
 */
int main(int argc, char* argv[]) {
    int status;
    char *input = malloc(BUFF_SIZE * sizeof(char));
    char **array = NULL;
    char **final = NULL;

    do {
        printf("%s%s", PS, " ");
        getInput(&input);
        int wc = wordCount(input);
        int hasArgs = wc > 1;

        if (hasArgs) {
            array = splitString(&input, wc);
            final = prepareArgsArray(array, wc);

            if (strcmp(final[0], "cd") == 0) {
                chdir(final[1]);
            }
        }

        pid_t f = fork();

        switch (f) {
            case -1:
                printf("%s", "Fork error.");
                break;
            case 0:
                if (hasArgs) {
                    execvp(buildCmdPath(final[0]), final);
                } else {
                    printf("input: %s\n", input);
                    execl(buildCmdPath(input),input, NULL);
                }
                exit(1);
            default:
                wait(&status);
                break;
        }

    } while(strcmp(input, "exit") != 0);

    free(input);
}