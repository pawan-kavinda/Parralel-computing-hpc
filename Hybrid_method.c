#include <stdio.h>
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
    int rank, size, n = 1000000;
    double a = 0.0, b = 1.0;
    double h = (b - a) / n;
    double local_a, local_b;
    int local_n;
    double local_result, total_result;
    double start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_n = n / size;
    local_a = a + rank * local_n * h;
    local_b = local_a + local_n * h;

    if (rank == 0) start = MPI_Wtime();

    local_result = local_trapezoidal_openMP(local_a, local_b, local_n, h);

    MPI_Reduce(&local_result, &total_result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        end = MPI_Wtime();
        printf("Hybrid MPI+OpenMP Result = %f\n", total_result);
        printf("Execution Time = %f seconds\n", end - start);
    }

    MPI_Finalize();
    return 0;
}
