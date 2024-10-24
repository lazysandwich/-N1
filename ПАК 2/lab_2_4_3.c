#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
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

int right_base (int base, char* num) {
    while (*num != '\0') {
        if (isdigit(*num) && *num - '0' >= base) {
            return 0;
        }
        else if (isalpha(*num) && *num - 'a' + 10 >= base) {
            return 0;
        }
        else {
            return 0;
        }
    }
    return 1;
}

void find_kaprekar_numbers(int argv, char** argc) {
    int base = matoi(argc[1]);
    for (int i = 2; i < argv; i++) {
        if (!right_base(base, argc[i]));
    }
    for (int i = 2; i < argv; i++) {
        int num = (int) strtol(argc[i], NULL, base);
        if (num == 0) {
            printf("0\n");
            continue;
        }
        int squared = num * num;
        for (int j = 1; j < num; j++) {
            int left = j;
            int right = num - j;
            double ten_pow = (squared - left) / right;
            if (log10(ten_pow) == (int)log10(ten_pow)) {
                printf("%s\n", argc[i]);
                break;
            }
        }
    }
}

int main(int argv, char* argc[]) {
    if (argv < 3) {
        printf("Неверное количество аргументов\n");
        return 0;
    }
    find_kaprekar_numbers(argv, argc);
    return 0;
}