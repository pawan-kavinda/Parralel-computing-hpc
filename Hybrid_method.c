#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

double f(double x) {
    return x * x;
}

double local_trapezoidal_openMP(double local_a, double local_b, int local_n, double h) {
    double sum = (f(local_a) + f(local_b)) / 2.0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i < local_n; i++) {
        sum += f(local_a + i * h);
    }

    return sum * h;
}

int main(int argc, char* argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
 
    double test_cases[][3] = {
        {0.0, 1.0, 1000000},
        {0.0, 5.0, 2000000},
        {1.0, 3.0, 500000},
        {0.0, 10.0, 10000000},
        {2.0, 4.0, 100000},
        {0.0, 1000.0, 1000000000}
    };
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int t = 0; t < num_tests; t++) {
        double a = test_cases[t][0];
        double b = test_cases[t][1];
        int n = (int)test_cases[t][2];

        double h = (b - a) / n;
        int local_n = n / size;
        double local_a = a + rank * local_n * h;
        double local_b = local_a + local_n * h;

        double start, end;
        if (rank == 0) start = MPI_Wtime();

        double local_result = local_trapezoidal_openMP(local_a, local_b, local_n, h);

        double total_result;
        MPI_Reduce(&local_result, &total_result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            end = MPI_Wtime();
            printf("Test %d: a=%.2f, b=%.2f, n=%d\n", t + 1, a, b, n);
            printf("Hybrid MPI+OpenMP Result = %.10f\n", total_result);
            printf("Execution Time = %f seconds\n\n", end - start);
        }

        MPI_Barrier(MPI_COMM_WORLD);  
    }

    MPI_Finalize();
    return 0;
}
