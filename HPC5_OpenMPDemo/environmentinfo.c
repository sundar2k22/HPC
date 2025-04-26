#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Number of processors available: %d\n", omp_get_num_procs());
    printf("Maximum number of threads: %d\n", omp_get_max_threads());

    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("Number of threads currently in use: %d\n", omp_get_num_threads());
        }
    }

    printf("Dynamic threads enabled: %d\n", omp_get_dynamic());
    printf("Active level of nested parallelism: %d\n", omp_get_active_level());

    return 0;
}
