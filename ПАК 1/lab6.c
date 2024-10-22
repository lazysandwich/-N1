#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double func1 (double a) {
    if (a == 0) {
        return 0;
    }
    else
        return log(1 + a) / a;
}

double func2 (double a) {
    return pow(2.71828, (-1 * a * a / 2));
}

double func3 (double a) {
    return log(1.0 / (1.0 - a));
}

double func4 (double a) {
    if (a == 0) {
        return 1;
    }
    else
        return pow(a, a);
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
        printf("Неправильное количество аргументов\n");
        return 1;
    }
    double eps = matof(argc[1]), step;
    if (eps < 0) {
        printf("Введено неправильное число\n");
        return 1;
    }
    eps = max_f(eps, 0.0001);
    double result1 = 0, result2 = 0, result3 = 0, result4 = 0;
    double old_result1 = 0, old_result2 = 0, old_result3 = 0, old_result4 = 0;
    old_result1 = (func1(1) + func1(0)) / 2 * 1;
    int n = 1, o = 0;
    do {
        if (o == 0) {
            o = 1;
        }
        else {
            old_result1 = result1;
        }
        result1 = 0;
        n++;
        step = 1.0 / n;
        for (double i = 0; i < 1; i += step) {
            result1 += (func1(i) + func1(i + step)) / 2 * step;
        }
    } while (fabs(result1 - old_result1) >= eps);
    printf("%.10f\n", result1);
    old_result2 = (func2(1) + func2(0)) / 2 * 1;
    n = 1, o = 0;
    do {
        if (o == 0) {
            o = 1;
        }
        else {
            old_result2 = result2;
        }
        result2 = 0;
        n++;
        step = 1.0 / n;
        for (double i = 0; i < 1; i += step) {
            result2 += (func2(i) + func2(i + step)) / 2 * step;
        }
    } while (fabs(result2 - old_result2) >= eps);
    printf("%.10f\n", result2);
    old_result3 = (func3(0.999) + func3(0)) / 2 * 1;
    n = 10, o = 0;
    do {
        if (o == 0) {
            o = 1;
        }
        else {
            old_result3 = result3;
        }
        result3 = 0;
        n++;
        step = 1.0 / n;
        for (double i = 0; i + step < 1; i += step) {
            result3 += (func3(i) + func3(i + step)) / 2 * step;
        }
    } while (fabs(result3 - old_result3) >= eps);
    printf("%.10f\n", result3);
    old_result4 = (func4(1) + func4(0)) / 2 * 1;
    n = 1, o = 0;
    do {
        if (o == 0) {
            o = 1;
        }
        else {
            old_result4 = result4;
        }
        result4 = 0;
        n++;
        step = 1.0 / n;
        for (double i = 0; i < 1; i += step) {
            result4 += (func4(i) + func4(i + step)) / 2 * step;
        }
    } while (fabs(result4 - old_result4) >= eps);
    printf("%.10f\n", result4);
    return 0;
}