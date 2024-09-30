#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {
    pid_t pid;

    // Create a child process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // This is the child process
        printf("Child process (PID: %d) is executing...\n", getpid());
        sleep(3); // Simulating some work
        printf("Child process (PID: %d) is terminating...\n", getpid());
        exit(0); // Child terminates
    } else {
        // This is the parent process
        printf("Parent process (PID: %d) is waiting for the child to terminate...\n", getpid());
        
        // Wait for the child to terminate
        wait(NULL);
        
        // Child has terminated, parent can now safely proceed
        printf("Parent process (PID: %d) has reaped the child process. Exiting now...\n", getpid());
    }

    return 0;
}
