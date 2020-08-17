#include <mpi.h>
#include <stdio.h>

int main (int argc, char **argv) {
	int nprocs;
	int rank;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	printf("I am a process %d. The number of processes is %d.\n", rank, nprocs);

	MPI_Finalize();
	return 0;
}
