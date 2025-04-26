#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    omp_set_num_threads(5);
    #pragma omp parallel for
    for(int i=0;i<10;i++){
        printf("Hello HPC class %d... from thread = %d\n", i, omp_get_thread_num());
    }
    return 0;
}