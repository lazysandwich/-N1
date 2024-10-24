#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

int matoi(const char *str) {
    int isValid = 1;
    long long num = 0;  
    while (*str != '\0') {
        if (!isdigit(*str)) {
            perror("Было введено не целое число");
            exit(EXIT_FAILURE);
        }
        num = num * 10 + (*str - '0');
        if (num > 2e9) {
            perror("Было введено большое число");
            exit(EXIT_FAILURE);
        }
        str++;
    }
    return (int)num;
}

double matof (char *num) {
    float ten = 0.1;
    float acc = 0;
    int s = sizeof(num), o = 0, minus = 1, f_d = 0;
    for (int i = 0; i < s; i++) {
        if (f_d == 0 && num[i] >= '0' && num[i] <= '9') {
            f_d = 1;
        }
        else if (f_d == 0 && num[i] == '-' && minus == 1) {
            minus = -1;
            continue;
        }
        else if (num[i] == '\0') {
            break;
        }
        else if (o == 0 && f_d == 1 && num[i] == '.') {
            o = 1; // начало дробной части
            continue;
        }
        else if (num[i] < '0' || num[i] > '9') {
            perror("Введено неправильное число\n");
            exit(EXIT_FAILURE);
        }
        if (o == 0) {
            acc *= 10;
            acc += num[i] - '0';
        }
        else {
            acc += ten * (num[i] - '0');
            ten /= 10;
        }
    }
    return minus*acc;
}

void polynomial_reduction(double epsilon, double a, double **result, int degree, char** argv) {
    double *coefficients = (double *)malloc((degree + 1) * sizeof(double));
    if (!coefficients) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= degree; i++) {
        coefficients[i] = matof(argv[i + 4]);
    }
    double *g = (double *)malloc((degree + 1) * sizeof(double));
    if (!g) {
        perror("Ошибка выделения памяти");
        free(coefficients);
        exit(EXIT_FAILURE);
    }
    double coaf_pow[degree + 1][degree + 1];
    for (int i = 0; i <= degree; i++) {
        coaf_pow[i][0] = 1;
    }
    int old_coaf_pow;
    for (int o = 0; o <= degree; o++) {
        for (int i = 1; i <= o; i++) {
            for (int j = 0; j <= (i / 2); j++) {
                if (j == 0) {
                    coaf_pow[o][j] = 1;
                    coaf_pow[o][i - j] = 1;
                    old_coaf_pow = coaf_pow[o][j];
                }
                else {
                    coaf_pow[o][j] = coaf_pow[o][j] + old_coaf_pow;
                    old_coaf_pow = coaf_pow[o][j];
                    coaf_pow[o][i - j] = coaf_pow[o][j];
                }
            }
        }
    }
    int ind[degree + 1];
    for (int o = 0; o <= degree; o++) {
        ind[o] = 1;
    }
    g[degree] = coefficients[degree];
    for (int k = degree - 1; k >= 0; k--) {
        double sum = coefficients[k];
        for (int j = 0; j < degree - k; j++) {
            sum += g[degree - j] * pow(a, degree - k - j) * coaf_pow[degree - j][ind[degree - j]] * pow(-1, ind[degree - j] + 1);
            ind[degree - j]++;
        }
        printf("%f\n", sum);
        g[k] = sum;
    }
    for (int i = 0; i <= degree; i++) {
        if (fabs(g[i]) < epsilon) {
            g[i] = 0.0;
        }
    }
    *result = g;
    free(coefficients);
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        printf("Неверное количество аргументов\n");
        return 1;
    }
    double *g_coefficients = NULL;
    double epsilon = matof(argv[1]);
    double a = matof(argv[2]);
    int degree = matoi(argv[3]);
    if (degree != argc - 5) {
        printf("Неверное количество аргументов\n");
        return 1;
    }
    polynomial_reduction(epsilon, a, &g_coefficients, degree, argv);
    printf("Коэффициенты переразложенного многочлена:\n");
    for (int i = 0; i <= degree; i++) {
        printf("g[%d] = %.6f\n", i, g_coefficients[i]);
    }
    free(g_coefficients);
    return 0;
}
