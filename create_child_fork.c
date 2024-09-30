#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("regno\n");
    } else {
        // Parent process
        printf("name\n");
    }

    // Both processes continue executing after this point
    return 0;
}
