#include <stdio.h>
#include <omp.h>

double f(double x) {
    return x * x;  
}
// This function integrates f(x) from a to b using the trapezoidal rule
double trapezoidal_openMP(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = (f(a) + f(b)) / 2.0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }

    return sum * h;
}

int main() {
    double a = 0.0, b = 1.0;
    int n = 1000000;

    double start = omp_get_wtime();  

    double result = trapezoidal_openMP(a, b, n);

    double end = omp_get_wtime();  
    
    printf("OpenMP Result = %f\n", result);
    printf("Execution Time = %f seconds\n", end - start);
    return 0;
}
