#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long double fact(int n) {
    double f = 1.0;
    for (int i = 2; i <= n; i++) {
        f *= i;
    }
    return f;
}

long double factc(int n) {
    double f = 1.0;
    for (int i = 2; i <= n; i+= 2) {
        f *= i;
    }
    return f;
}

long double factn(int n) {
    double f = 1.0;
    for (int i = 3; i <= n; i+=2) {
        f *= i;
    }
    return f;
}

double max_f(double a, double b) {
    if (a < b)
        return b;
    else
        return a;
}

double matof(char* num) {
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
    return minus * acc;
}

int main(int argv, char* argc[]) {
    if (argv != 2) {
        printf("Неверное количество аргументов\n");
        return 1;
    }
    float e = matof(argc[1]);
    if (e < 0) {
        printf("Введено неправильное число\n");
        return 1;
    }
    e = max_f(e, 0.0001);
    double sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
    int x = 5, ind = 2;
    sum1 = pow(x, 0) / 1;
    double dop = pow(x, 1) / 1;
    while (fabs(dop) > e) {
        sum1 += dop;
        dop = pow(x, ind) / fact(ind);
        ind++;
    }
    printf("первая сумма: %f\n", sum1);
    sum2 = pow(-1, 0) * pow(x, 0) / 1;
    dop = pow(-1, 1) * pow(x, 2) / fact(2);
    ind = 2;
    while (fabs(dop) > e) {
        sum2 += dop;
        dop = pow(-1, ind) * pow(x, 2 * ind) / fact(2 * ind);
        ind++;
    }
    printf("вторая сумма: %f\n", sum2);
    sum3 = pow(3, 0) * pow(1, 3) * pow(x, 0) / 1;
    dop = pow(3, 3) * pow(1, 3) * pow(x, 2) / fact(3);
    ind = 2;
    while (fabs(dop) > e) {
        sum3 += dop;
        dop = pow(fact(ind), 3) * pow(x, 2 * ind) / fact(3 * ind) * pow(3, 3 * ind);
        ind++;
    }
    printf("Третья сумма: %f\n", sum3);
    sum4 = pow(-1, 1) * 1 * pow(x, 2) / fact(fact(2));
    dop = pow(-1, 2) * fact(fact(3)) * pow(x, 4) / fact(fact(4));
    ind = 3;
    while (fabs(dop) > e) {
        sum4 += dop;
        dop = pow(-1, ind) * factn(2 * ind - 1) * pow(x, 2 * ind) / factc(2 * ind);
        ind++;
    }
    printf("Четвертая сумма: %f\n", sum4);
    return 0;
}