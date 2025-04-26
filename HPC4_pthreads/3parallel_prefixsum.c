#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000
#define NUM_THREADS 2

int arr[N], prefix_sum[N];
pthread_barrier_t barrier;

typedef struct {
    int start;
    int end;
} ThreadData;

void* partial_prefix_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int start = data->start;
    int end = data->end;
    
    for (int i = start; i < end; i++) {
        prefix_sum[i] = (i == start) ? arr[i] : prefix_sum[i - 1] + arr[i];
    }
    
    pthread_barrier_wait(&barrier);
    
    if (start != 0) {
        int correction = prefix_sum[start - 1];
        for (int i = start; i < end; i++) {
            prefix_sum[i] += correction;
        }
    }
    
    return NULL;
}

int main() {
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }
    
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int segment_size = N / NUM_THREADS;
    
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);
    
    LARGE_INTEGER frequency, start_time, end_time;
    QueryPerformanceFrequency(&frequency); // Get the frequency
    QueryPerformanceCounter(&start_time); // Record start time
    
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start = i * segment_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? N : (i + 1) * segment_size;
        pthread_create(&threads[i], NULL, partial_prefix_sum, &thread_data[i]);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    QueryPerformanceCounter(&end_time); // Record end time
    
    pthread_barrier_destroy(&barrier);
    
    for (int i = 0; i < N; i += N / 10) {
        printf("%d ", prefix_sum[i]);
    }
    printf("\n");
    
    double time_taken = (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart; // Calculate elapsed time
    printf("Time taken for parallel execution: %f seconds\n", time_taken);
    
    return 0;
}
