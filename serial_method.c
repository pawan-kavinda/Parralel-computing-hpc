#include <stdio.h>
#include <time.h>
double f(double x) {
    return x * x;
}

double trapezoidal_serial(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = (f(a) + f(b)) / 2.0;
    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }
    return sum * h;
}

int main() {
    double a = 0.0, b = 1.0;
    int n = 1000000;

    clock_t start = clock();  

    double result = trapezoidal_serial(a, b, n);
    clock_t end = clock();   
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Serial Result = %f\n", result);
    printf("Execution Time = %f seconds\n", time_taken);
    return 0;
}
