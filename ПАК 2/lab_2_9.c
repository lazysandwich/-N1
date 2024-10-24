#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int matoi(const char *str) {
    int isValid = 1;
    long long num = 0;  
    while (*str != '\0') {
        if (!isdigit(*str)) {
            perror("Было введено не целое число");
            exit(EXIT_FAILURE);
        }
        num = num * 10 + (*str - '0');
        if (num > 2e9) {
            perror("Было введено большое число");
            exit(EXIT_FAILURE);
        }
        str++;
    }
    return (int)num;
}

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

int has_finite_representation(double fraction, int base) {
    if (fraction <= 0 || fraction >= 1) {
        return 0;
    }
    while (base % 2 == 0) {
        base /= 2;
    }
    while (base % 5 == 0) {
        base /= 5;
    }
    return base == 1;
}

void check(int base, int size, char** nums) {
    for (int i = 0; i < size; i++) {
        double fraction = matof(nums[i]);
        if (has_finite_representation(fraction, base)) {
            printf("Дробь %.6f имеет конечное представление в системе с основанием %d\n", fraction, base);
        } else {
            printf("Дробь %.6f не имеет конечного представления в системе с основанием %d\n", fraction, base);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Неверное количество аргументов\n");
        return 1;
    }
    char* nums[argc - 2];
    for (int i = 0; i < argc - 2; i++) {
        nums[i] = argv[i + 2];
    }
    int base = matoi(argv[1]);
    check(base, argc - 2, nums);
    check(base, argc - 2, nums);
    return 0;
}
