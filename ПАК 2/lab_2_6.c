#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

int fscan_roman(const char *s) {
    int total = 0;
    int prev_value = 0;

    while (*s) {
        int value = 0;
        switch (*s) {
            case 'I': value = 1; break;
            case 'V': value = 5; break;
            case 'X': value = 10; break;
            case 'L': value = 50; break;
            case 'C': value = 100; break;
            case 'D': value = 500; break;
            case 'M': value = 1000; break;
            default: return -1; // Некорректный ввод
        }

        if (value > prev_value) {
            total += value - 2 * prev_value; // Вычитаем предыдущее
        }
        else {
            total += value;
        }
        prev_value = value;
        s++;
    }
    return total;
}

unsigned int fscan_zeckendorf(const char *s) {
    int fibs[] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};
    unsigned int result = 0;
    int idx = 0;
    while (*s) {
        if (*s == '1') {
            result += fibs[idx];
        }
        idx++;
        s++;
    }
    return result;
}

int read_decimal(const char *s, int *value, int base) {
    if (base < 2 || base > 36) {
        base = 10;
    }
    *value = (int)strtol(s, NULL, base);
    return 1;
}

int oversscanf(const char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    const char *p = format;
    char buf[100]; // Буфер для считывания строк
    int count = 0;
    while (*p) {
        if (*p == '%') {
            p++;
            char first = *p;
            p++;
            char second = *p;
            if (first == 'R' && second == 'o') {
                int *int_ptr = va_arg(args, int *);
                sscanf(str, "%s", buf);
                *int_ptr = fscan_roman(buf);
                count++;
            }
            else if (first == 'Z' && second == 'r') {
                unsigned int *uint_ptr = va_arg(args, unsigned int *);
                sscanf(str, "%s", buf);
                *uint_ptr = fscan_zeckendorf(buf);
                count++;
            }
            else if (first == 'C' && second == 'v') {
                int *int_ptr = va_arg(args, int *);
                int base = va_arg(args, int);
                sscanf(str, "%s", buf);
                read_decimal(buf, int_ptr, base);
                count++;
            }
            else if (first == 'C' && second == 'V') {
                int *int_ptr = va_arg(args, int *);
                int base = va_arg(args, int);
                sscanf(str, "%s", buf);
                for (int i = 0; buf[i]; i++) buf[i] = toupper((unsigned char)buf[i]);
                read_decimal(buf, int_ptr, base);
                count++;
            }
            else if (first == 'd') {
                *p--;
                int *int_ptr = va_arg(args, int *);
                sscanf(str, "%i", int_ptr);
                count++;
            }
            else if (first == 'l' && second == 'd') {
                long int *int_ptr = va_arg(args, long int *);
                sscanf(str, "%ld", int_ptr);
                count++;
            }
            else if (first == 'u') {
                *p--;
                unsigned int *uint_ptr = va_arg(args, unsigned int *);
                sscanf(str, "%u", uint_ptr);
                count++;
            } 
            else if (first == 'f') {
                *p--;
                *p--;
                double *double_ptr = va_arg(args, double *);
                sscanf(str, "%lf", double_ptr);
                count++;
            } 
            else if (first == 's') {
                *p--;
                char *str_ptr = va_arg(args, char*);
                sscanf(str, "%s", str_ptr);
                count++;
            } 
            else if (first == 'c') {
                *p--;
                char *char_ptr = va_arg(args, char*);
                sscanf(str, "%c", char_ptr);
                count++;
            }
            else {
                perror("Введен не существующий флаг");
                exit(EXIT_FAILURE);
            }
        }
        else {
            str++;
        }
        p++;
    }
    va_end(args);
    return count;
}


int overfscanf(FILE *file, const char *format, ...) {
    char str[100];
    if (!fgets(str, sizeof(str), file)) {
        perror("Не удалось считать строку или конец файла");
        exit(EXIT_FAILURE);
    }
    va_list args;
    va_start(args, format);
    const char *p = format;
    char buf[100]; // Буфер для считывания строк
    int count = 0;
    while (*p != '\0') {
        if (*p == '%') {
            p++;
            char first = *p;
            p++;
            char second = *p;
            if (first == 'R' && second == 'o') {
                int *int_ptr = va_arg(args, int *);
                sscanf(str, "%s", buf);
                *int_ptr = fscan_roman(buf);
                count++;
            }
            else if (first == 'Z' && second == 'r') {
                unsigned int *uint_ptr = va_arg(args, unsigned int *);
                sscanf(str, "%s", buf);
                *uint_ptr = fscan_zeckendorf(buf);
                count++;
            }
            else if (first == 'C' && second == 'v') {
                int *int_ptr = va_arg(args, int *);
                int base = va_arg(args, int);
                sscanf(str, "%s", buf);
                read_decimal(buf, int_ptr, base);
                count++;
            }
            else if (first == 'C' && second == 'V') {
                int *int_ptr = va_arg(args, int *);
                int base = va_arg(args, int);
                sscanf(str, "%s", buf);
                for (int i = 0; buf[i]; i++) buf[i] = toupper((unsigned char)buf[i]);
                read_decimal(buf, int_ptr, base);
                count++;
            }
            else if (first == 'd') {
                *p--;
                int *int_ptr = va_arg(args, int *);
                sscanf(str, "%i", int_ptr);
                count++;
            }
            else if (first == 'l' && second == 'd') {
                long int *int_ptr = va_arg(args, long int *);
                sscanf(str, "%ld", int_ptr);
                count++;
            }
            else if (first == 'u') {
                *p--;
                unsigned int *uint_ptr = va_arg(args, unsigned int *);
                sscanf(str, "%u", uint_ptr);
                count++;
            } 
            else if (first == 'f') {
                *p--;
                *p--;
                double *double_ptr = va_arg(args, double *);
                sscanf(str, "%lf", double_ptr);
                count++;
            } 
            else if (first == 's') {
                *p--;
                char *str_ptr = va_arg(args, char*);
                sscanf(str, "%s", str_ptr);
                count++;
            } 
            else if (first == 'c') {
                *p--;
                char *char_ptr = va_arg(args, char*);
                sscanf(str, "%c", char_ptr);
                count++;
            }
            else {
                perror("Введен не существующий флаг");
                exit(EXIT_FAILURE);
            }
        }
        p++;
    }
    va_end(args);
    return count;
}

int main() {
    int roman_result;
    unsigned int zeckendorf_result;
    int decimal_result;
    const char *roman_input = "XVIII"; // 18
    oversscanf(roman_input, "%Ro", &roman_result);
    printf("Десятичное значение римских цифр: %d\n", roman_result);
    const char *zeckendorf_input = "01001"; // 10
    oversscanf(zeckendorf_input, "%Zr", &zeckendorf_result);
    printf("Десятичное значение цекендорфового числа: %u\n", zeckendorf_result);
    const char *num1 = "1a"; // 1A в шестнадцатеричной = 26 в десятичной
    oversscanf(num1, "%Cv", &decimal_result, 16);
    printf("Десятичное значение числа в системе счисления с основанием 16: %d\n", decimal_result);
    const char *num2 = "2B"; // 1A в шестнадцатеричной = 43 в десятичной
    oversscanf(num2, "%CV", &decimal_result, 16);
    printf("Десятичное значение числа в системе счисления с основанием 16: %d\n", decimal_result);
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    overfscanf(file, "%Ro", &roman_result);
    printf("Десятичное значение римских цифр: %d\n", roman_result);
    overfscanf(file, "%Zr", &zeckendorf_result);
    printf("Десятичное значение цекендорфового числа: %u\n", zeckendorf_result);
    overfscanf(file, "%Cv", &decimal_result, 16);
    printf("Десятичное значение числа в системе счисления с основанием 16: %d\n", decimal_result);
    overfscanf(file, "%CV", &decimal_result, 16);
    printf("Десятичное значение числа в системе счисления с основанием 16: %d\n", decimal_result);
    return 0;
}