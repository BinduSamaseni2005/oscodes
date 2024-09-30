#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void parentProcess(int *sharedVar) {
    // Parent increments the shared variable by 5
    *sharedVar += 5;
    printf("Parent process: Value after increment = %d\n", *sharedVar);
}

void childProcess(int *sharedVar) {
    // Child just displays the value of the shared variable
    printf("Child process: Value of shared variable = %d\n", *sharedVar);
}

int main() {
    int sharedVar;  // Variable shared between parent and child

    // Obtain the value of sharedVar from the user
    printf("Enter an integer value for the shared variable: ");
    scanf("%d", &sharedVar);

    pid_t pid = fork();  // Create a new process

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        childProcess(&sharedVar);
    } else {
        // Parent process
        parentProcess(&sharedVar);
    }

    return 0;
}
