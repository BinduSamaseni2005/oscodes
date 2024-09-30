#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    printf("Parent PID: %d\n", getpid());

    // Create first child
    pid1 = fork();

    if (pid1 == 0) {
        // This is the first child process
        printf("First child PID: %d, Parent PID: %d\n", getpid(), getppid());
        
        // First child creates its own child (grandchild)
        pid_t pid1_child = fork();
        if (pid1_child == 0) {
            // This is the grandchild of parent (child of first child)
            printf("First child -> Grandchild PID: %d, Parent PID: %d\n", getpid(), getppid());
        } else {
            wait(NULL);  // First child waits for its child (grandchild) to finish
        }

    } else {
        // Create second child in the parent process
        pid2 = fork();

        if (pid2 == 0) {
            // This is the second child process
            printf("Second child PID: %d, Parent PID: %d\n", getpid(), getppid());
            
            // Second child creates its own child (grandchild)
            pid_t pid2_child = fork();
            if (pid2_child == 0) {
                // This is the grandchild of parent (child of second child)
                printf("Second child -> Grandchild PID: %d, Parent PID: %d\n", getpid(), getppid());
            } else {
                wait(NULL);  // Second child waits for its child (grandchild) to finish
            }

        } else {
            // Parent waits for both children to finish
            wait(NULL);  // Wait for first child
            wait(NULL);  // Wait for second child
            printf("Parent process completed.\n");
        }
    }

    return 0;
}
