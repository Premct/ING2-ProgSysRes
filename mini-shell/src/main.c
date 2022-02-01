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

    getInput(&input);
    int wc = wordCount(input);

//    while(strcmp(input, "exit") != 0) {
        pid_t f = fork();

        switch (f) {
            case -1:
                printf("%s", "Fork error.");
                break;
            case 0:
                printf("Input: %s\n", input);
                printf("wordCount: %d\n", wc);

                if (wc > 1) {
                    array = splitString(&input, wc);
                    final = prepareArgsArray(array, wc);
                    execvp(buildCmdPath(final[0]), final);
                } else {
                    execl(buildCmdPath(input),input, NULL);
                }

                getInput(&input);
                wc = wordCount(input);
                exit(1);
            default:
                wait(&status);
                break;
        }

        getInput(&input);
        wc = wordCount(input);
//    }





    free(input);
}