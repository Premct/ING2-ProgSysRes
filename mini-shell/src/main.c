/*!
 * \file main.c
 * \version 0.1
 * \author Monchecourt Pierre <monchecour@cy-tech.fr>
 * \date 25/01/2022
 * \brief Main file
 */

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
    char *input = malloc(BUFF_SIZE * sizeof(char));
    char **array = NULL;
    char **final = NULL;

    do {
        getInput(&input);
        int wc = wordCount(input);

        printf("wordCount: %d\n", wc);
        if (wc > 1) {
            array = splitString(&input, wc);
            final = prepareArgsArray(array, wc);
            execvp(buildCmdPath(final[0]), final);
        } else {
            execl(buildCmdPath(input),input, NULL);
        }
    } while(strcmp(input, "exit") != 0);


    free(input);
}