#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    double x, y;
} Point;

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

double cross_product(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int is_convex(int n, char **argc) {
    n--;
    if (n < 3)
        return 0;
    Point points[n / 2];
    int ind = 0;
    for (int i = 1; i < n; i += 2) {
        points[ind].x = matof(argc[i]);
        points[ind].y = matof(argc[i + 1]);
        ind++;
    }
    int sign = 0;
    for (int i = 0; i < ind; i++) {
        double cp = cross_product(points[i], points[(i + 1) % ind], points[(i + 2) % ind]);
        if (cp != 0) {
            if (sign == 0 && cp > 0) {
                sign = 1;
            }
            else if (sign == 0 && cp < 0) {
                sign = -1;
            }
            else if ((cp > 0 && sign < 0) || (cp < 0 && sign > 0)) {
                return 0; // Многоугольник не выпуклый
            }
        }
    }
    return 1; // Многоугольник выпуклый
}

int main(int argv, char *argc[]) {
    if (argv % 2 == 0) {
        printf("Неверное количество аргументов\n");
        return 1;
    }
    if(is_convex(argv, argc)) {
        printf("Многоугольник выпуклый\n");
    }
    else {
        printf("Многоугольник не выпуклый\n");
    }
    return 0;
}