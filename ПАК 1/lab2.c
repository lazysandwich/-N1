#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int min(int a, int b) {
    if (a > b)
        return b;
    else
        return a;
}

double max_f(double a, double b) {
    if (a < b)
        return b;
    else
        return a;
}

int max(int a, int b) {
    if (a < b)
        return b;
    else
        return a;
}

long int fact(int n) {
    int f = 1;
    for (int i = 2; i <= n; i++) {
        f *= i;
    }
    return f;
}

long double cnk(int n, int k) {
    return fact(n) / fact(k) / fact(n - k);
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

int is_i (char *num) {
    int acc = 0;
    int s = sizeof(num), o = 0, minus = 0, f_d = 0;
    for (int i = 0; i < s; i++) {
        if (f_d == 0 && num[i] >= '0' && num[i] <= '9') {
            f_d = 1;
            acc += num[i] - '0';
        }
        else if (f_d == 0 && num[i] == '-' && minus == 0) {
            minus = 1;
        }
        else if (num[i] == '\0') {
            break;
        }
        else if (num[i] < '0' || num[i] > '9') {
            printf("Введено неправильное число\n");
            return 1;
        }
        else {
            acc *= 10;
            acc += num[i] - '0';
        }
    }
    return 0;
}

int main(int argv, char *argc[]) {
    if (argv != 2) {
        printf("Неправильное количество аргументов\n");
        return 1;
    }
    float acc = matof(argc[1]);
    if (acc < 0) {
        printf("Введено неправильное число\n");
        return 1;
    }
    acc = max_f(acc, 0.01);
    float e_lim = 2, e_row = 0, e_old = 0;
    long double pi_lim = 4, pi_row = 0, pi_old = 0;
    float ln_lim = 1, ln_row = 0, ln_old = 0;
    float root_lim = -0.5 - 0.25 / 2 + 1, root_row = 0, root_old;
    float y_lim = 0, y_row = 0, y_old = 0;
    //y_lim = cnk(2, 1) * pow(-1.0, 1) / 1.0 * log(fact(1)) + cnk(2, 2) * pow(-1.0, 2) / 2.0 * log(fact(2));
    printf("Через предел\n");
    int n = 2;
    while (fabs(log(e_lim) - 1) > acc) {
        e_lim = pow((1.0 + 1.0 / n), n);
        n++;
    }
    printf("%f ", e_lim);
    n = 2;
    while (fabs(cos(pi_lim) + 1) > acc) {
        pi_lim = pow((pow(2.0, n) * fact(n)), 4.0) / (n * pow(fact(2.0 * n), 2.0));
        n++;
    }
    printf("%Lf ", pi_lim);
    n = 2;
    while (fabs(pow(e_lim, ln_lim) - 2) > acc) {
        ln_lim = n * (pow(2.0, (1.0 / n)) - 1.0);
        n++;
    }
    printf("%f ", ln_lim);
    while (fabs(root_lim * root_lim - 2) > acc) {
        root_lim = root_lim - root_lim * root_lim / 2.0 + 1.0;
        n++;
    }
    printf("%f ", root_lim);
    n = 3;
    //while (fabs(y_lim - y_old) > acc) {
    //    y_old = y_lim;
    //    y_lim = 0;
    //    for (int k = 1; k <= n; k++)
    //        y_lim += cnk(n, k) * pow(-1.0, k) / k * log(fact(k));
    //    n++;
    //}
    //printf("%f\n", y_lim);
    printf("\nЧераз ряд / произведение\n");
    e_old = 1.0 / fact(1);
    e_row = 2.0 * e_old;
    pi_old = 4.0 * (pow(-1.0, 0) / (2.0 * 1 - 1));
    pi_row = 4.0 * (pow(-1.0, 2 - 1) / (2.0 * 2 - 1)) + pi_old;
    ln_old = pow(-1.0, 1.0 - 1) / 1;
    ln_row = pow(-1.0, 2 - 1) / 2.0 + ln_old;
    root_old = pow(2.0, pow(2.0, -2));
    root_row = pow(2.0, pow(2.0, -3)) * root_old;
    float pi = 3.14159265358979323846;
    //y_old = -pow(pi, 2.0) / 6.0 + 1 / pow(floor(pow(2.0, 0.5)), 2.0) - 1.0 / 2.0;
    //y_row = 1.0 / pow(floor(pow(3.0, 0.5)), 2.0) - 1.0 / 3.0 + y_old;
    n = 2;
    while (fabs(log(e_row) - 1) > acc) {
        e_old = e_row;
        e_row = 1.0 / fact(n) + e_old;
        n++;
    }
    printf("%f ", e_row);
    n = 3;
    while (fabs(cos(pi_row) + 1) > acc) {
        pi_old = pi_row;
        pi_row = 4.0 * (pow(-1.0, n - 1) / (2.0 * n - 1.0)) + pi_old;
        n++;
    }
    printf("%Lf ", pi_row);
    n = 3;
    while (fabs(pow(e_row, ln_row) - 2) > acc) {
        ln_old = ln_row;
        ln_row = pow(-1.0, n - 1.0) / n + ln_old;
        n++;
    }
    printf("%f ", ln_row);
    n = 4;
    while (fabs(root_row * root_row - 2) > acc) {
        root_old = root_row;
        root_row = pow(2.0, pow(2.0, -n)) * root_old;
        n++;
    }
    printf("%f ", root_row);
    n = 4;
    //while (fabs(y_row - y_old) > acc) {
    //    if (pow(floor(pow(n, 0.5)), 2.0) == n) {
    //        n++;
    //    }
    //    y_old = y_row;
    //    y_row = 1.0 / pow(floor(pow(n, 0.5)), 2.0) - 1.0 / n + y_old;
    //    n++;
    //}
    //printf("%f\n", y_row);
    printf("\nЧерез уравнение\n");
    long double a = 1, b = 4, c;
    c = (a + b) / 2;
    while (fabs(log(c) - 1) > acc) {
        if (log(c) > 1) {
            b = c;
        }
        else {
            a = c;
        }
        c = (a + b) / 2;
    }
    float e = c;
    printf("%Lf ", c);
    a = 1, b = 4;
    c = (a + b) / 2;
    while (fabs(cos(c / 2)) > acc) {
        if (cos(c / 2) < 0) {
            b = c;
        }
        else {
            a = c;
        }
        c = (a + b) / 2;
    }
    printf("%Lf ", c);
    a = 0, b = 10;
    c = (a + b) / 2;
    while (fabs(pow(e, c) - 2) > acc) {
        if (pow(e, c) > 2) {
            b = c;
        }
        else {
            a = c;
        }
        c = (a + b) / 2;
    }
    printf("%Lf ", c);
    a = 1, b = 4;
    c = (a + b) / 2;
    while (fabs(c * c - 2) > acc) {
        if (c * c > 2) {
            b = c;
        }
        else {
            a = c;
        }
        c = (a + b) / 2;
    }
    printf("%Lf \n", c);
    //a = 0, b = 1000;
    //c = (a + b) / 2;
    //float mult = 1;
    //for (int i = 2; i < 20; i++) {
    //    mult *= (i - 1) / i;
    //}
    //mult *= log(20);
    //while (fabs(pow(e, -c) - mult) > acc) {
    //    if (pow(e, -c) < mult) {
    //        b = c;
    //    }
    //    else {
    //        a = c;
    //    }
    //    c = (a + b) / 2;
    //}
    //printf("%Lf\n", c);
}