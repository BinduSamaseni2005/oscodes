#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Function that will be executed by the thread
void *threadFunction(void *arg) {
    printf("Hello from the thread! Thread ID: %ld\n", pthread_self());
    return NULL; // Exit the thread
}

int main() {
    pthread_t thread; // Declare a thread variable

    // Create a thread that runs the threadFunction
    if (pthread_create(&thread, NULL, threadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1; // Exit if there's an error
    }

    // Wait for the thread to finish
    pthread_join(thread, NULL);

    printf("Hello from the main thread! Thread ID: %ld\n", pthread_self());
    
    return 0; // Exit the program
}
