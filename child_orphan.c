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

        // Sleep for 10 seconds to simulate work
        sleep(10);  
        printf("Child process (PID: %d) is terminating...\n", getpid());
        exit(0); // Child terminates
    } else {
        // This is the parent process
        printf("Parent process (PID: %d) is terminating...\n", getpid());
        exit(0); // Parent terminates immediately
    }

    return 0;
}
