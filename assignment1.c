#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/*
 * CS3305A - Assignment 1
 * September 27th, 2021
 * Rishabh Jain
 */

int main(int argc, char **argv) {
    // Declaring variables of type pid_t
    pid_t pid;

    // Character array for sprintf statements
    char output[200];

    // Parent process creates a child process, child 1
    pid = fork();

    // Check if the fork was unsuccessful
    if (pid < 0) {
        puts("fork unsuccessful");
        exit(1);
    }

    // Parent process
    if (pid > 0) {
        // Parent process waits for child 1 to complete
        wait(NULL);
    }

    // Child 1 calls an external program and passes parameters
    if (pid == 0) {
        sprintf(output, "parent (PID %d) created child_1 (PID %d)", getppid(), getpid());
        puts(output);
        sprintf(output, "parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2", getppid(),
               getpid());
        puts(output);

        // Converting PID to string
        char PID[30];
        sprintf(PID, "%d", getpid());

        sprintf(output, "child_1 (PID %d) is calling an external program external_program.out and leaving parent", getpid());
        puts(output);

        // External program
        execl(argv[1], "", strcat(PID, " for child_1"), NULL);
    }

    // Parent process creates child 2
    pid = fork();

    // Check if the fork was unsuccessful
    if (pid < 0) {
        puts("fork unsuccessful");
        exit(1);
    }

    // Parent process
    if (pid > 0) {
        // Parent process waits for child 2 to complete
        wait(NULL);

        // Print termination statement
        puts("child_1 and child_2 are completed and parent process is terminating...");
    }

    // child 2 process
    if (pid == 0) {
        sprintf(output, "parent (PID %d) created child_2 (PID %d)", getppid(), getpid());
        puts(output);

        // child 2 creates child 2.1
        pid = fork();

        // Check if the fork was unsuccessful
        if (pid < 0) {
            puts("fork unsuccessful");
            exit(1);
        }

        // child 2 process waits for child 2.1 to complete
        if (pid > 0) {
            wait(NULL);
        }

        // Child2.1 process
        if (pid == 0) {
            sprintf(output, "child_2 (PID %d) created child_2.1 (PID %d)", getppid(), getpid());
            puts(output);

            // Converting PID to string
            char PID[30];
            sprintf(PID, "%d", getpid());

            sprintf(output, "child_2.1 (PID %d) is calling an external program external_program.out and leaving child_2", getpid());
            puts(output);

            // External program
            execl(argv[1], "", strcat(PID, " for child_2.1"), NULL);
        }
    }
}