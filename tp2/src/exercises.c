/**
 * TP2 Exercises
 */

#include <wait.h>
#include "../lib/exercises.h"

int TRIES;
int HASTOINPUT;

void sigHandler(int signal) {
    printf("%d%s%d\n", getpid(), " received signal: ", signal);
}

void sendSignal(int sig, pid_t p_dest) {
    pid_t cur_pid = getpid();
    if (kill(p_dest, sig) == -1) {
        printf("%s%d\n", "Error when sending signal: ", sig);
    } else {
        if (p_dest == cur_pid) {
            printf("%d%s%d%s\n", cur_pid, " send ", sig, " to itself");
        } else {
            printf("%d%s%d%s%d\n", cur_pid, " send ", sig, " to ", p_dest);
        }
    }
}

void alarmHandler(int sig) {
    printf("%s%d\n", "Wake up! Remaining tries: ", 3 - TRIES);
    HASTOINPUT = 1;
    ++TRIES;
}

/**
 * Exercise one. Creates a child process that try to reroute SIG KILL ANT SIGTERM signals.
 */
void exerciseOne() {
    pid_t f;
    int status;
    struct sigaction action;

    signal(SIGUSR1, &sigHandler);
    signal(SIGUSR2, &sigHandler);

    f = fork();

    switch (f) {
        case -1:
            fprintf(stderr, "%s\n", "Fork error!");
            break;
        case 0:
            printf("%s\n", "\033[1;32mIn child process\033[0m");
            if (kill(getppid(), SIGUSR1) == -1) {
                fprintf(stderr, "%s\n", "Error when sending signal");
            } else {
                printf("%s%d%c\n", "Child sent SIGTERM to father(", getppid(), ')');
                sleep(5);
            }

            if (kill(getppid(), SIGUSR2) == -1) {
                fprintf(stderr, "%s", "Error when sending signal");
            } else {
                printf("%s%d%c\n", "Child sent SIGKILL to father(", getppid(), ')');
                sleep(5);
            }
            break;

        default:
            wait(&status);

            printf("%s\n", "\033[1;34mIn father process\033[0m");

            /* HANDLING SIGTERM */
            if (sigaction(SIGUSR1, &action, NULL) == -1) {
                fprintf(stderr, "%s\n", "Error when handling signal");
            } else {
                printf("%d%s\n", getpid(), " rerouted SIGTERM");
            }

            /* HANDLING SIGKILL */
            if (sigaction(SIGUSR2, &action, NULL) == -1) {
                fprintf(stderr, "%s\n", "Error when handling signal");
            } else {
                printf("%d%s\n", getpid(), " rerouted SIGKILL");
            }
            sleep(50);
            break;
    }
}

void exerciseTwo() {
    pid_t f = fork(); /* Child creation */
    int status;

    switch (f) {
        case -1:
            printf("%s\n", "Fork error");
            break;
        case 0:
            printf("%s%d%c\n", "\033[1;34mIn child\033[0m(", getpid(), ')');

            printf("%s\n", "Task f1");
            sleep(3);

            sendSignal(SIGCONT, getppid());

            sendSignal(SIGSTOP, getpid());

            printf("%s\n", "Task f2");
            sleep(3);

            sendSignal(SIGCONT, getppid());
            break;
        default:
            printf("%s%d%c\n", "\033[1;32mIn father\033[0m(", getpid(), ')');

            sendSignal(SIGSTOP, getpid());

            printf("%s\n", "Task p1");
            sleep(3);

            sendSignal(SIGCONT, f);

            sendSignal(SIGSTOP, getpid());

            printf("%s\n", "Task p2");
            sleep(3);

            break;
    }
}

void exerciseThree() {
    struct sigaction action;
    char question[1024];

    action.sa_handler = alarmHandler;

    if (sigaction(SIGALRM, &action, NULL) == -1) {
        printf("%s\n", "Error when sending signal (SIGALRM)");
    }

    printf("%s\n", "What's your question?");

    TRIES = 0;
    while (HASTOINPUT && TRIES <= 3) {
        HASTOINPUT = 0;
        alarm(5);
        fgets(question, 1024, stdin);
    }

    if (HASTOINPUT == 0) {
        printf("%s%s\n", "Your question is: ", question);
    } else {
        printf("%s\n", "No question, no answer!");
    }

}
