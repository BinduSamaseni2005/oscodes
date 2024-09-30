#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3, pid4;

    printf("Parent process started with PID: %d\n", getpid());

    // Create the third child first
    pid3 = fork();
    if (pid3 == 0) {
        // Third child process
        printf("Third child process started with PID: %d\n", getpid());
        sleep(1); // Simulate some work
        printf("Third child process terminated with PID: %d\n", getpid());
        return 0; // Terminate
    }

    // Create the second child
    pid2 = fork();
    if (pid2 == 0) {
        // Second child process
        printf("Second child process started with PID: %d\n", getpid());
        waitpid(pid3, NULL, 0); // Wait for the third child to finish
        sleep(1); // Simulate some work
        printf("Second child process terminated with PID: %d\n", getpid());
        return 0; // Terminate
    }

    // Create the first child
    pid1 = fork();
    if (pid1 == 0) {
        // First child process
        printf("First child process started with PID: %d\n", getpid());
        pid_t grandchild_pid = fork(); // Create grandchild
        if (grandchild_pid == 0) {
            // Grandchild process
            printf("Grandchild process started with PID: %d\n", getpid());
            sleep(1); // Simulate some work
            printf("Grandchild process terminated with PID: %d\n", getpid());
            return 0; // Terminate
        }
        waitpid(grandchild_pid, NULL, 0); // Wait for grandchild to finish
        printf("First child process terminated with PID: %d\n", getpid());
        return 0; // Terminate
    }

    // Create the fourth child
    pid4 = fork();
    if (pid4 == 0) {
        // Fourth child process
        printf("Fourth child process started with PID: %d\n", getpid());
        sleep(2); // Simulate some work
        printf("Fourth child process terminated with PID: %d\n", getpid());
        return 0; // Terminate
    }

    // Parent process waits for all children in the specified order
    waitpid(pid3, NULL, 0); // Wait for third child
    waitpid(pid2, NULL, 0); // Wait for second child
    waitpid(pid1, NULL, 0); // Wait for first child
    waitpid(pid4, NULL, 0); // Wait for fourth child

    printf("Parent process terminated with PID: %d\n", getpid());
    return 0;
}
