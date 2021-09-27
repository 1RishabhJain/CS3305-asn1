#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

/*
 * CS3305A - Assignment 1
 * September 27th, 2021
 * Rishabh Jain
 */

int main(int argc, char **argv) {
    // Declaring variables of type pid_t
    pid_t pid1, pid2, pid2_1;

    // Exit boolean
    bool terminate = false;

    // Parent process creates a child process, child 1
    pid1 = fork();

    // Parent process waits for child 1 to complete
    wait(NULL);

    // Check if the fork was unsuccessful
    if (pid1 < 0) {
        printf("fork unsuccessful");
        exit(1);
    }

    // Parent process
    if (pid1 > 0) {
        // Parent process creates child 2
        pid2 = fork();

        // Parent process waits for child 2 to complete
        wait(NULL);

        // Check if the fork was unsuccessful
        if (pid2 < 0) {
            printf("fork unsuccessful");
            exit(1);
        }

        // child 2 process
        if (pid2 > 0) {
            // child 2 creates child 2.1
            pid2_1 = fork();

            // child 2 process waits for child 2.1 to complete
            wait(NULL);

            // Check if the fork was unsuccessful
            if (pid2_1 < 0) {
                printf("fork unsuccessful");
                exit(1);
            }

            // Child2.1 process
            if (pid2_1 > 0) {
                printf("child_2 (PID %d) created child_2.1 (PID %d)\n", pid2, pid2_1);

                // Converting PID to string
                int length = floor(log10(abs(pid2_1))) + 1;
                char PID[length];
                sprintf(PID, "%d", pid2_1);

                printf("child_2.1 (PID %d) is calling an external program external_program.out and leaving child_2\n", pid2_1);

                // Setting boolean terminate to true
                terminate = true;

                // External program
                execl(argv[1], "", strcat(PID, " for child_2.1"), NULL);
            }
        }

        // Print termination statement
        if (terminate) {
            printf("child_1 and child_2 are completed and parent process is terminating...\n");
        }

        // Child 2
        if (pid2 == 0) {
            printf("parent (PID %d) created child_2 (PID %d)\n", getppid(), getpid());
        }
    }

    // Child 1 calls an external program and passes parameters
    if (pid1 == 0) {
        printf("parent (PID %d) created child_1 (PID %d)\n", getppid(), getpid());
        printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", getppid(), getpid());

        // Converting PID to string
        int length = floor(log10(abs(getpid()))) + 1;
        char PID[length];
        sprintf(PID, "%d", getpid());

        printf("child_1 (PID %d) is calling an external program external_program.out and leaving parent\n", getpid());

        // External program
        execl(argv[1], "", strcat(PID, " for child_1"), NULL);
    }
}