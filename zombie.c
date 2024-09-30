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
        // Child process
        printf("Child process (PID: %d) is executing...\n", getpid());
        sleep(5); // Simulate some work
        printf("Child process (PID: %d) is terminating...\n", getpid());
        exit(0); // Child terminates
    } else {
        // Parent process
        printf("Parent process (PID: %d) is sleeping for 10 seconds...\n", getpid());
        sleep(10); // Sleep for a while to allow child to terminate

        // Here, the child process is likely a zombie since the parent has not yet waited for it
        printf("Parent process (PID: %d) waking up...\n", getpid());
        
        // Uncomment the following line to see the cleanup of the child process
        // wait(NULL); 

        // To keep the program running and observe the zombie state,
        // you can add an infinite loop or a pause here
        printf("Parent process (PID: %d) will now terminate...\n", getpid());
    }

    return 0;
}
