#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_data = rank; // Each process sends its rank
    int recv_data;

    int next = (rank + 1) % size;
    int prev = (rank - 1 + size) % size;

    MPI_Sendrecv(&send_data, 1, MPI_INT, next, 0,
                 &recv_data, 1, MPI_INT, prev, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Process %d received data %d from process %d\n", rank, recv_data, prev);

    MPI_Finalize();
    return 0;
}
