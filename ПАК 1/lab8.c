#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

int min(const char *number) { // Функция для определения минимального основания системы счисления
    int min_base = 2;
    for (int i = 0; number[i] != '\0'; i++) {
        char digit = tolower(number[i]);
        int value;
        if (isdigit(digit)) {
            value = digit - '0';
        }
        else if (isalpha(digit)) {
            value = digit - 'a' + 10;
        }
        else {
            return -1;
        }
        if (value + 1 > min_base) {
            min_base = value + 1;
        }
    }

    return min_base > 36 ? -1 : min_base;
}

long long back_ten(const char *number, int base) { // Функция для преобразования числа из заданной системы счисления в десятичную
    long long result = 0;

    for (int i = 0; number[i] != '\0'; i++) {
        char digit = tolower(number[i]);
        int value;
        if (isdigit(digit)) {
            value = digit - '0';
        } else {
            value = digit - 'a' + 10;
        }
        result = result * base + value;
    }
    return result;
}

int main(int argv, char *argc[]) {
    if (argv != 3) {
        printf("Неправильое колтчество аргументов\n");
        return 1;
    }
    FILE *input = fopen(argc[1], "r");
    FILE *output = fopen(argc[2], "w");
    struct stat buf1, buf2;
        stat(argc[2], &buf1);
        stat(argc[3], &buf2);
        if (buf1.st_ino == buf2.st_ino) {
            printf("Выходной файл тот же, что и входной\n");
            return 1;
        }
    if (!input || !output) {
        printf("Оштбка открытия файла\n");
        exit(EXIT_FAILURE);
    }
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), input)) {
        char *token = strtok(line, " \t\n");
        while (token != NULL) { // Удаление ведущих нулей
            char *trimmed = token;
            while (*trimmed == '0') {
                trimmed++;
            }
            if (*trimmed == '\0') {
                token = strtok(NULL, " \t\n");
                continue;
            }
            int min_base = min(trimmed);
            if (min_base >= 2 && min_base <= 36) {
                long long decimal_value = back_ten(trimmed, min_base);
                fprintf(output, "%s %d %lld\n", trimmed, min_base, decimal_value);
            } else {
                fprintf(output, "Неправильное число\n");
            }
            token = strtok(NULL, " \t\n");
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}