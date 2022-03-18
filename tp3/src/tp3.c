/*!
 * @file tp3.c
 * @version 0.1
 * @author Pierre Monchecourt <monchecour@cy-tech.fr>
 * @date 04-03-2022
 * @brief Header file implementation
 */

#include "../lib/tp3.h"

/*!
* @fn exerciseOne()
* @author Pierre Monchecourt <monchecour@cy-tech.fr>
* @brief Exercise One
* @return 0 if all went well
*/
/* ${cursor} */
int exerciseOne() {
    const int BUFF_SIZE = 1000; /* Max size */
    char buff[BUFF_SIZE]; /* Buffer for message writing */

    int p[2]; /* Descriptor, 2-sized array */
    int status;
    int n;

    pipe(p); /* Pipe opening */

    pid_t f = fork();

    switch(f) {
        case -1:
            printf("%s\n", "Fork error.");
            break;
        case 0:
            /*printf("%s\n", "In child process");*/
            n = read(p[0], buff, BUFF_SIZE - 1); /* Son reads in pipe */
            buff[n] = '\0'; /* Closing stream */
            printf("%d%s%s%s%d\n", getpid(), " reading: ", buff,  " sent by ", getppid());

            write(p[1], "Hello father!", strlen("Hello father!"));

            kill(getppid(), SIGCONT); /* Father continues */

            exit(0);
        default:
            /*printf("%s\n", "In father process");*/
            write(p[1], "Hello son!", strlen("Hello son !")); /* Father writes in */

            kill(getpid(), SIGSTOP); /* Father stops */


            n = read(p[0], buff, BUFF_SIZE - 1);
            buff[n] = '\0';

            printf("%d%s%s%s%d\n", getpid(), " reading: ", buff, " sent by ", f);
            break;
    }

    return(0);
}
