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

        clock_t start = clock();
        double result = trapezoidal_serial(a, b, n);
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

        printf("Test %d: a=%.2f, b=%.2f, n=%d\n", t + 1, a, b, n);
        printf("Serial Result = %.10f\n", result);
        printf("Execution Time = %f seconds\n\n", time_taken);
    }

    return 0;
}
