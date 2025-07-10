#include <stdio.h>
#include <mpi.h>

double f(double x) {
    return x * x;
}

double local_trapezoidal(double local_a, double local_b, int local_n, double h) {
    double sum = (f(local_a) + f(local_b)) / 2.0;
    for (int i = 1; i < local_n; i++) {
        sum += f(local_a + i * h);
    }
    return sum * h;
}

int main(int argc, char* argv[]) {
    int rank, size, n = 1000000;
    double a = 0.0, b = 1.0;
    double h, local_a, local_b;
    int local_n;
    double local_result, total_result;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    h = (b - a) / n;
    local_n = n / size;
    local_a = a + rank * local_n * h;
    local_b = local_a + local_n * h;

    double start = MPI_Wtime();  
    local_result = local_trapezoidal(local_a, local_b, local_n, h);

    MPI_Reduce(&local_result, &total_result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double end = MPI_Wtime();   

    if (rank == 0) {
        printf("MPI Result = %f\n", total_result);
        printf("Execution Time = %f seconds\n", end - start);
    }

    MPI_Finalize();
    return 0;
}
