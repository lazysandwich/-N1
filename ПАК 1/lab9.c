#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
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
    if (argv != 3) {
        printf("Неправильное количество аргументов\n");
        return 1;
    }
    printf("Часть один\n");
    if (is_i(argc[1])) {
        return 1;
    }
    if (if_i(argc[2])) {
        return 1;
    }
    int a = atoi(argc[1]), b = atoi(argc[2]), size1 = 10;
    int size2 = 10 + rand() % 10000;
    int * mass1 = (int*)malloc(sizeof(size1));
    int * mass_A = (int*)malloc(sizeof(size2));
    int * mass_B = (int*)malloc(sizeof(size2));
    int * mass_C = (int*)malloc(sizeof(size2));
    printf("Исходный массив:\n");
    for (int i = 0; i < size1; i++) {
        mass1[i] = a + rand() % b;
        printf("%i ", mass1[i]);
    }
    printf("\n");
    int min = mass1[0], max = mass1[0], ind_min = 0, ind_max = 0;
    for (int i = 1; i < size1; i++) {
        if (min > mass1[i]) {
            min = mass1[i];
            ind_min = i;
        }
        if (max < mass1[i]) {
            max = mass1[i];
            ind_max = i;
        }
    }
    printf("Измененный массив:\n");
    int dop = mass1[ind_max];
    mass1[ind_max] = mass1[ind_min];
    mass1[ind_min] = dop;
    for (int i = 0; i < size1; i++) {
        printf("%i ", mass1[i]);
    }
    printf("\n");
    printf("Максимальное число: %i\n", max);
    printf("Минимальное число: %i\n", min);
    printf("Вторая часть задания\n");
    printf("Исходный массив А:\n");
    for (int i = 0; i < size2; i++) {
        mass_A[i] = -1000 + rand() % 1000;
        //printf("%i ", mass_A[i]);
    }
    printf("\n");
    printf("Исходный массив B:\n");
    for (int i = 0; i < size2; i++) {
        mass_B[i] = -1000 + rand() % 1000;
        //printf("%i ", mass_B[i]);
    }
    printf("\n");
    int dist, val;
    for (int i = 0; i < size2; i++) {
        dist = abs(mass_A[i] - mass_B[0]);
        val = mass_B[0];
        for (int j = 1; j < size2; j++) {
            if (dist > abs(mass_A[i] - mass_B[j])) {
                dist = abs(mass_A[i] - mass_B[j]);
                val = mass_B[j];
            }
        }
        mass_C[i] = mass_A[i] + val;
    }
    printf("Полученный массив C:\n");
    //for (int i = 0; i < size2; i++) {
    //    printf("%i ", mass_C[i]);
    //}
    free(mass1);
    return 0;
}
