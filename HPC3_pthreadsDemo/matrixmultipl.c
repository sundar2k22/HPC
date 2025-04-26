#include <stdio.h>
#include <stdlib.h>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <time.h>

#define MAX 1000


int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
int N;

void *multiply(void *arg) {
    int row = (int)arg;
    for (int j = 0; j < N; j++) {
        C[row][j] = 0;
        for (int k = 0; k < N; k++) {
            C[row][j] += A[row][k] * B[k][j];
        }
    }
    pthread_exit(0);
}

void sequential_multiply() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    srand(time(NULL));
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    clock_t start, end;
    double sequential_time, parallel_time;

    start = clock();
    sequential_multiply();
    end = clock();
    sequential_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sequential multiplication time: %f seconds\n", sequential_time);

    pthread_t threads[MAX];
    start = clock();
    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, multiply, (void *)i);
    }
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    end = clock();
    parallel_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Parallel multiplication time: %f seconds\n", parallel_time);

    double overhead = parallel_time - sequential_time;
    double speedup = sequential_time / parallel_time;
    printf("Overhead: %f seconds\n", overhead);
    printf("Speedup: %f\n", speedup);

    return 0;
}
