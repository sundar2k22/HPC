#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int arr[50];
    for(int i = 0; i < 50; i++) {
        arr[i] = i;
    }

    int sum = 0;
    omp_set_num_threads(5);
    double start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < 50; i++) {
        int thread_id = omp_get_thread_num();
        double thread_start_time = omp_get_wtime();
        printf("Thread %d is processing index %d\n", thread_id, i);
        sum += arr[i];
        double thread_end_time = omp_get_wtime();
        printf("Thread %d finished processing index %d in %f seconds\n", thread_id, i, thread_end_time - thread_start_time);
    }

    double end_time = omp_get_wtime();
    printf("Average is %d\n", sum / 50);
    printf("Total time taken: %f seconds\n", end_time - start_time);

    return 0;
}
