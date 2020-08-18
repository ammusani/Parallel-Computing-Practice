#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int matrix_vector_mult(int *A, int *x, int rank, int n) {

	//Sequential vector multiplication:
	int bi = 0;
	for (int j = 0; j < n; j++) {
		bi += A [j] * x [j];
	}
	return bi;
	
}

int main(int argc, char **argv) {
	int n;
	int rank;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &n);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int x[n];

	if (rank == 0) {

		int A0 [n];
		int Ap [n];
	
		// Use current time as seed for random number generator.
		srand (time(0));
		printf ("%s", "Random values for the square matrix are:\n");

		for(int j = 0; j < n; j++) {
			A0 [j] = rand() % 193;
			printf("%d ", A0[j]);
		}
		puts(" ");

		// Generating random values less than the 45th prime number and assigning to the matrix A.
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < n; j++) {
				Ap [j] = rand () % 193;
				printf ("%d ", Ap [j]);
			}
			puts ("");
			MPI_Send(&Ap, n, MPI_INT, i, i, MPI_COMM_WORLD);
		}
		puts("");

		// Generating random value for the vector x
		printf ("%s", "Random values for the Vector are:\n");
		for (int i = 0; i < n; i++) {
			x [i] = rand () % 193;
			printf("%d\n", x [i]);
		}
		puts("");

		// Declairing the output pointer
		int *b;
		b = (int *) malloc (n * sizeof (int));

		
		MPI_Bcast(&x, n, MPI_INT, 0, MPI_COMM_WORLD);
		
		b[rank] = matrix_vector_mult(A0, x, rank, n);
		
		for(int i = 1; i < n; i++) MPI_Recv(&b[i], 1, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		printf("%s", "Output vector b, for the Ax = b:\n");
		for (int i = 0; i < n; i++) printf ("%d\n", b [i]);

		free (b);
	}
	else {
		int A[n];
		int b;
		
		MPI_Recv(&A, n, MPI_INT, 0, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Bcast(&x, n, MPI_INT, 0, MPI_COMM_WORLD);

		b = matrix_vector_mult(A, x, rank, n);

		MPI_Send(&b, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);
		
	}

	MPI_Finalize();

	return 0;
}

	
