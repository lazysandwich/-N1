#include <stdio.h>
#include <math.h>

typedef double (*Function)(double);

double bisection(double a, double b, double epsilon, Function f) {
    if (f(a) * f(b) >= 0) {
        printf("Функция должна иметь разные знаки на концах интервала.\n");
        return NAN;
    }
    double midpoint;
    while ((b - a) >= epsilon) {
        midpoint = (a + b) / 2.0;
        if (f(midpoint) == 0.0) {
            return midpoint;
        }
        else if (f(midpoint) * f(a) < 0) {
            b = midpoint;
        }
        else {
            a = midpoint;
        }
    }
    return (a + b) / 2.0;
}

double equation1(double x) { // Пример уравнения f(x) = x^2 - 2 (корень 1.4142135...)
    return x * x - 2;
}

double equation2(double x) { // Пример уравнения f(x) = x^3 - x - 2 (корень 1.521...)
    return x * x * x - x - 2;
}

double equation3(double x) { // Пример уравнения f(x) = sin(x) (корень 0)
    return sin(x);
}

void demo_bisection() { // Функция для демонстрации работы метода дихотомии
    double a, b, epsilon, root;
    // Пример 1
    a = 0;
    b = 2;
    epsilon = 0.0001;
    root = bisection(a, b, epsilon, equation1);
    printf("Корень уравнения x^2 - 2 на интервале [%.2f, %.2f]: %.8f\n", a, b, root);
    // Пример 2
    a = 1;
    b = 2;
    epsilon = 0.001;
    root = bisection(a, b, epsilon, equation2);
    printf("Корень уравнения x^3 - x - 2 на интервале [%.2f, %.2f]: %.8f\n", a, b, root);
    // Пример 3
    a = 3;
    b = 4;
    epsilon = 0.0001;
    root = bisection(a, b, epsilon, equation3);
    printf("Корень уравнения sin(x) на интервале [%.2f, %.2f]: %.8f\n", a, b, root);
}

int main() {
    demo_bisection();
    return 0;
}