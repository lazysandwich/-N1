#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>

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

double geometric_mean(int argv, char **argc) {
    double result = 1.0, ind = 0;
    for (int i = 1; i < argv; i++) {
        ind = 1;
        result *= matof(argc[i]);
    }
    if (result < 0.0) {
        perror("Среднего геометрического не существует\n");
        exit(EXIT_FAILURE);
    }
    if (ind = 0) {
        return 0;
    }
    return pow(result, 1.0 / (argv - 1));
}

int main(int argv, char* argc[]) {
    printf("%f\n", geometric_mean(argv, argc));
    return 0;
}