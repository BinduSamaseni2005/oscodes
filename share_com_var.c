#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

void childProcess(int *common){
    printf("Child Process\n");
    printf("Common Variable Value from Child Process: %d\n", *common);
}

void parentProcess(int *common){
    *common += 5;
    printf("Parent Process\n");
    printf("Common Variable Value from Parent Process: %d\n", *common);      
}

int main() {
    // Create shared memory segment
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    // Attach the shared memory to the parent process
    int *common = (int *)shmat(shmid, NULL, 0);
    if (common == (int *) -1) {
        perror("shmat failed");
        exit(1);
    }

    *common = 2;  // Initialize the shared variable

    pid_t child_pid = fork();
    if (child_pid == 0) {
        // Child process
        childProcess(common);
    } else if (child_pid > 0) {
        // Parent process
        parentProcess(common);

        // Wait for the child process to complete
        wait(NULL);

        // Detach and remove shared memory
        shmdt(common);
        shmctl(shmid, IPC_RMID, NULL);
    } else {
        perror("Fork failed");
    }

    return 0;
}
