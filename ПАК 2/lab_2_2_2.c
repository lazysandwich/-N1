#include <stdio.h>
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

double power(double base, int exponent) {
    if (exponent < 0) {
        base = 1 / base;
        exponent = -exponent;
    }
    if (exponent == 0) {
        return 1.0;
    }
    if (exponent == 1) {
        return base;
    }
    if (exponent % 2 == 0) {
        double half = power(base, exponent / 2);
        return half * half;
    }
    else {
        return base * power(base, exponent - 1);
    }
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

int main(int argv, char *argc[]) {
    if (argv != 3) {
        printf("Неверное количество аргументов\n");
        return 1;
    }
    double num_f = matof(argc[1]);
    int num_i = matoi(argc[2]);
    printf("%f\n",power(num_f, num_i));
    return 0;
}