#include <stdio.h>

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

    double result = trapezoidal_serial(a, b, n);
    printf("Serial Result = %f\n", result);
    return 0;
}
