#include <math.h>
#include <stdlib.h>
#include <stdio.h>

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

int main (int argv, char *argc[]) {
    if (argv != 3) {
        printf("Неправильное количество аргументов\n");
        return 1;
    }
    char * dop_flag = argc[1];
    char flag = dop_flag[1];
    char *endptr;
    if (is_i(argc[2])) {
        return 1;
    }
    int num = atoi(argc[2]);
    if (num < 0) {
        printf("Введено не корректное число\n");
        return 1;
    }
    if (dop_flag[0] != '/' && dop_flag[0] != '-') {
        printf("Веден неправильный флаг\n");
        return 1;
    }
    if (flag == 'h') { // проверка на кратность
        int o = 1;
        for (int i = num; i <= 100; i++) {
            if (i % num == 0 && i / num != 0) {
                o = 0;
                printf("%i ", i);
            }
        }
        if (o) {
            printf("Нет чисел кратных исходнодному числу\n");
        }
        printf("\n");
    }
    else if (flag == 'p') { // простое ли число
        int o = 0;
        for (int i = 2; i < sqrt(num); i++) {
            if (num % i == 0) {
                o = 1;
            }
        }
        if (o)
            printf("Число составное\n");
        else
            printf("Число простое\n");
    }
    else if (flag == 's') { // разбиение числа на цифры 16 системы счисления
        if (num == 0) {
            printf("0\n");
        }
        else {
            char dig[100];
            int ind = 0;
            while (num > 0) {
                int a = num % 16;
                dig[ind++] = (a < 10) ? (a + '0') : (a - 10 + 'A');
                num /= 16;
            }
            for (int i = ind - 1; i > -1; i--) {
                printf("%c ", dig[i]);
            }
            printf("\n");
        }
    }
    else if (flag == 'e') { // степени 
        if (num > 10) {
            printf("Число х должно быть меньше 11\n");
            return 1;
        }
        printf("%d\n", num);
        long long degr = num;
        int* start = (int*)malloc(sizeof(degr));
        long int* div = (long int*)malloc(sizeof(degr));
        for (int i = 0; i < degr; i++) {
            start[i] = i + 1;
            div[i] = i + 1;
            printf("%ld ", div[i]);
        }
        printf("\n");
        for (int i = 1; i < 10; i++) {
            for (int j = 0; j < degr; j++) {
                div[j] *= start[j];
                printf("%ld ", div[j]);
            }
            printf("\n");
        }
    }
    else if (flag == 'a') { // сумма
        int sum = 0;
        for (int i = 1; i <= num; i++) {
            sum += i;
        }
        printf("%i\n", sum);
    }
    else if (flag == 'f') { // факториал
        if (num > 20) {
            printf("МНого Чиферек\n");
            return 1;
        }
        int mult = 1;
        for (int i = 1; i <= num; i++) {
            mult *= i;
        }
        printf("%i\n", mult);
    }
    else {
        printf("Нет такого флага\n");
        return 1;
    }
    return 0;
} 
