#include "../lib/exercises.h"

void ex1() {
    printf("%s%i\n", "Process number (PID): ", getpid());
    printf("%s%i\n", "Father process number (PPID): ", getppid());
    printf("%s%i\n", "Real Process number (UID): ", getuid());
    printf("%s%i\n", "Effective process number (EUID): ", geteuid());
    printf("%s%i\n", "GID number: ", getgid());
    printf("%s%i\n", "Effective GID number (EGID): ", getegid());
}

void ex2() {
    pid_t process;

    process = fork();

    printf("%s%i\n", "FORK value: ", process);

    switch (process) {
        case -1:
            fprintf(stderr, "%s%s%s\n", RED, "FORK FAILURE", RESET);
            break;
        case 0:
            printf("%s%s%s%i\n", BLUE, "In child process: ", RESET, getpid());
            break;
        default:
            printf("%s%s%s%i\n", RED, "In father process: ", RESET, getpid());


    }
}

void ex3() {
    pid_t process;
    char path[MAX_BUF];

    process = fork();

    printf("%s%i\n", "FORK value: ", process);

    switch (process) {
        case -1:
            fprintf(stderr, "%s%s%s\n", RED, "FORK FAILURE", RESET);
            break;
        case 0:
            printf("%s%s%s%i\n", GREEN, "Child Process: ", RESET, getpid());
            break;
        default:
            printf("%s%s%s%i\n", RED, "Father Process: ", RESET, getpid());
    }
    ex1();
    printf("%s%s%s%s\n", "Work directory: ", BLUE, getcwd(path, MAX_BUF), RESET);
}

void ex4() {
    pid_t p;
    p = fork();
    int x = 2;

    switch (p) {
        case 0:
            //sleep(15);
            printf("%s%i%s%i%s%i\n", "Child PID is ", getpid(), " and Father PID is ", getppid(), ". x = ", x + 3);

            break;
        case -1:
            //sleep(15);
            printf("%s%s%s\n", RED, "Fork error", RESET);
            break;
        default:
            sleep(2);
            printf("%s%i%s%i%s%i\n", "Father PID is ", getpid(), " and Father PID is ", getppid(), ". x = ", x * 5);
            break;
    }
    printf("%s%i\n", "Real Process number (UID): ", getuid());
    printf("%s%i\n", "GID number: ", getgid());

    printf("%s%d\n", "End of process: ", getpid());
}

void ex5() {
    int matrix[4] = {1, 2, 3, 4};

    long unsigned int mat_len = ((sizeof matrix) / sizeof matrix[0]);

    for (int i = 0; i < mat_len; ++i) {
        pid_t process = fork();
        int exit_status;

        switch (process) {
            case -1:
                printf("%s%s%s\n", RED, "Fork error", RESET);
                break;
            case 0:
                printf("%s%s%s%i%s\n", GREEN, "Child process ", BLUE, getpid(), RESET);
                exit(matrix[i] * matrix[i]);
            default:
                waitpid(process, &exit_status, WUNTRACED);
                printf("%s%s%s%i%s\n", RED, "Parent process ", BLUE, getpid(), RESET);
                printf("%s%i\n", "Child exited with status code: ", WEXITSTATUS(exit_status));
                break;
        }
    }


}
