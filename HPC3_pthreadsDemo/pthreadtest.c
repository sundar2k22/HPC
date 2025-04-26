#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void *printHello(void *threadid) {
    long tid;
    tid = (long)threadid;
    printf("Hello from Thread %ld\n", tid);
    pthread_exit(NULL); // Although not strictly necessary here, it's good practice
                       // to explicitly exit the thread.
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_create(&threads[t], NULL, printHello, (void *)t);
        if (rc) {
            fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", rc); // Use stderr for errors
            perror("pthread_create"); // Print a more descriptive error message
            exit(-1);
        }
    }

    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL); // Wait for each thread to complete.
    }

    printf("All threads have finished.\n"); // Indicate that all threads completed.
    return 0; // Indicate successful program termination.  pthread_exit in main is usually not recommended.
}