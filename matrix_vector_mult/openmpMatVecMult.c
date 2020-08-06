#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void matrix_vector_mult(int *A, int *x, int *b, int n) {

	//OpenMP parallel matrix-vector multiplication:
	#pragma omp parallel
	{
		// Have a doubt whether copies of A, x, b and n will be created or they would be shared?
		#pragma omp for
		for (int i = 0; i < n; i++) {
			b [i] = 0;
			// Will using omp for reduction work here?
			for (int j = 0; j < n; j++) {
				b [i] += A [i * n + j] * x [j];
			}
		}
	}

}

int main() {
	int n;
	printf ("%s", "Enter the dimension of the square matrix.\n");
	scanf ("%d", &n);


	int A [n * n];
	int x [n];
	
	// Use current time as seed for random number generator.
	srand (time(0));
	printf ("%s", "Random values for the square matrix are:\n");

	// Generating random values less than the 45th prime number and assigning to the matrix A.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A [i * n + j] = rand () % 193;
			printf ("%d ", A [i * n + j]);
		}
		puts ("");
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

	// Calling the function to generate the output
	matrix_vector_mult (A, x, b, n);

	printf ("%s", "Output vector b, for the Ax = b:\n");
	for (int i = 0; i < n; i++) printf ("%d\n", b [i]);

	free (b);

	return 0;
}

	



