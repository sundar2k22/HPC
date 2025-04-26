#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int data[4];       // Only used by root
    int local_data;    // Each process will get one element

    if (world_rank == 0) {
        // Initialize array at root
        data[0] = 1;
        data[1] = 2;
        data[2] = 3;
        data[3] = 4;
    }

    // Scatter data: each process gets one int
    MPI_Scatter(data, 1, MPI_INT, &local_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process multiplies its chunk by 2
    local_data *= 2;

    // Gather results into result[] at root
    int result[4];  // Only meaningful at root
    MPI_Gather(&local_data, 1, MPI_INT, result, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Root process prints the result
    if (world_rank == 0) {
        printf("Final gathered result:\n");
        for (int i = 0; i < 4; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
