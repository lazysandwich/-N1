#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double max_f(double a, double b) {
    if (a < b)
        return b;
    else
        return a;
}

void ans (double a, double b, double dis) {
    if (dis == 0) {
            double root = -b / 2 / a;
            printf("Корни квадратного уравнения: %.5lf\n", root);
        }
        else if(dis > 0){
            double root1 = -b + sqrt(dis) / 2 / a;
            double root2 = -b + sqrt(dis) / 2 / a;
            printf("Корни квадратного уравнения: %.5lf и %.5lf\n", root1, root2);
        }
        else {
        printf("Нет действительных корней\n");
    }
}

double min(double a, double b) {
    if (a < b) {
        return a;
    }
    else 
        return b;
}

double max(double a, double b) {
    if (a > b) {
        return a;
    }
    else 
        return b;
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

int main(int argv, char* argc[]) {
    if (argv < 2) {
        printf("Неверное количество аргументов\n");
        return 1;
    }
    char flag = argc[1][1];
    if (argc[1][0] != '-' && argc[1][0] != '/') {
        printf("Неправильный флаг\n");
        return 1;
    }
    if (flag == 'q') {
        if (argv != 6) {
            printf("Неверное количество аргументов\n");
            return 1;
        }
        double ep = matof(argc[2]), a = matof(argc[3]), b = matof(argc[4]), c = matof(argc[5]);
        if (ep < 0) {
            printf("Введено неправильное число\n");
            return 1;
        }
        ep = max_f(ep, 0.0001);
        if (fabs(a - b) <= ep && fabs(b - c) <= ep) {
            double dis1 = b * b - 4 * a * c;
            printf("%.5fx^2 + %.5fx + %.5f\n", a, b, c);
            ans(a, b, dis1);
            if (a != c) {
                printf("%.5fx^2 + %.5fx + %.5f\n", c, b, a);
                ans(c, b, dis1);
            }
        }
        else if (fabs(a - b) <= ep || fabs(b - c) <= ep || fabs(a - c) <= ep) {
            double mi = min(a, min(b, c));
            double ma = max(a, max(b, c));
            double mid = a + b + c - mi - ma;
            if (mid == mi) {
                double dis1 = ma * ma - 4 * mi * mi, dis2 = mi * mi - 4 * mi * ma;
                printf("%.5fx^2 + %.5fx + %.5f\n", mi, ma, mi);
                ans(mi, ma, dis1);
                printf("%.5fx^2 + %.5fx + %.5f\n", ma, mi, mi);
                ans(ma, mi, dis2);
                printf("%.5fx^2 + %.5fx + %.5f\n", mi, mi, ma);
                ans(mi, mi, dis2);
            }
            else {
                double dis1 = mi * mi - 4 * ma * ma, dis2 = ma * ma - 4 * mi * ma;
                printf("%.5fx^2 + %.5fx + %.5f\n", ma, mi, ma);
                ans(ma, mi, dis1);
                printf("%.5fx^2 + %.5fx + %.5f\n", mi, ma, ma);
                ans(mi, ma, dis2);
                printf("%.5fx^2 + %.5fx + %.5f\n", ma, ma, mi);
                ans(mi, ma, dis2);
            }
        }
        else {
            double dis1 = b * b - 4 * a * c, dis2 = a * a - 4 * b * c, dis3 = c * c - 4 * a * b;
            printf("%.5fx^2 + %.5fx + %.5f\n", a, b, c);
            ans(a, b, dis1);
            printf("%.5fx^2 + %.5fx + %.5f\n", c, b, a);
            ans(c, b, dis1);
            printf("%.5fx^2 + %.5fx + %.5f\n", b, a, c);
            ans(b, a, dis2);
            printf("%.5fx^2 + %.5fx + %.5f\n", c, a, b);
            ans(c, a, dis2);
            printf("%.5fx^2 + %.5fx + %.5f\n", a, c, b);
            ans(a, c, dis3);
            printf("%.5fx^2 + %.5fx + %.5f\n", b, c, a);
            ans(b, c, dis3);
            
        }
    }
    else if (flag == 'm') {
        if (argv != 4) {
            printf("Неправильное количество аргументов\n");
            return 1;
        }
        if (is_i(argc[2])) {
            return 1;
        }
        int a = atoi(argc[2]), b = atoi(argc[3]);
        if (b == 0) {
            printf("Ошибка: Деление на ноль\n");
            return 1;
        }
        if (a % b == 0) {
            printf("%d кратно %d\n", a, b);
        }
        else {
            printf("%d не кратно %d\n", a, b);
        }
    }
    else if (flag == 't') {
        if (argv != 6) {
            printf("Неверное количество аргументов\n");
            return 1;
        }
        double eps = matof(argc[2]);
        double a = matof(argc[3]);
        double b = matof(argc[4]);
        double c = matof(argc[5]);
        if (eps < 0) {
            printf("Введено неправильное число\n");
            return 1;
        }
        eps = max_f(eps, 0.0001);
        if (fabs(a * a + b * b - c * c) < eps || fabs(a * a + c * c - b * b) < eps || fabs(c * c + b * b - a * a) < eps) {
            printf("Числа могут быть сторонами прямоугольного треугольника\n");
        }
        else {
            printf("Числа не могут быть сторонами прямоугольного треугольника\n");
        }
    }
    else {
        printf("Неизвестный флаг\n");
        return 1;
    }
    return 0;
}