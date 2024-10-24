#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

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

int matoi(const char *str) {
    int isValid = 1;
    int sign = 1;
    long long num = 0;  
    while (*str != '\0') {
        num = num * 10 + (*str - '0');
        if (num * sign > 1e9 || num * sign < -1e9) {
            perror("Было введено большое число");
            exit(EXIT_FAILURE);
        }
        if (!isdigit(*str)) {
            perror("Было введено не целое число");
            exit(EXIT_FAILURE);
        }
        str++;
    }
    return sign * (int)num;
}

double evaluate_polynomial(int argv, char **argc) {
    double x = matof(argc[1]);
    double koaf[argv - 2];
    for (int i = 0; i < argv - 2; i++) {
        koaf[i] = matof(argc[i + 2]);
    }
    double result = 0.0;
    for (int i = 0; i < argv - 2; i++) {
        result += pow(x, argv - 2 - i - 1) * koaf[i];
    }
    return result;
}

int main(int argv, char *argc[]) {
    if (argv < 2) {
        printf("Неверное количество аргументов\n");
        return 1;
    }
    printf("%f\n", evaluate_polynomial(argv, argc));
    return 0;
}