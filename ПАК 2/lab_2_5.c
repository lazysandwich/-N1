#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

void print_roman(int num) { // Функция для преобразования числа в римские цифры
    const char *roman_numerals[][2] = {
        {"M", "1000"},
        {"CM", "900"},
        {"D", "500"},
        {"CD", "400"},
        {"C", "100"},
        {"XC", "90"},
        {"L", "50"},
        {"XL", "40"},
        {"X", "10"},
        {"IX", "9"},
        {"V", "5"},
        {"IV", "4"},
        {"I", "1"},
    };

    if (num < 1 || num > 3999) {
        printf("Invalid Roman numeral range\n");
        return;
    }

    for (int i = 0; i < 13; i++) {
        while (num >= atoi(roman_numerals[i][1])) {
            printf("%s", roman_numerals[i][0]);
            num -= atoi(roman_numerals[i][1]);
        }
    }
}

void print_cekendorf(unsigned int num) { // Функция для преобразования числа в цекендорфово представление
    int fib[32] = {1, 2}; // первые два числа Фибоначчи
    for (int i = 2; i < 32; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    unsigned int representation[32] = {0};
    int index = 0;
    for (int i = 31; i >= 0; i--) {
        if (fib[i] <= num) {
            representation[index++] = 1;
            num -= fib[i];
        } else if (index > 0) {
            representation[index++] = 0;
        }
    }
    for (int i = index - 1; i >= 0; i--) { // Вывод
        printf("%u", representation[i]);
    }
    printf("1"); // завершающая единица
}

void print_number_base(int base, int number, int uppercase) { // Функция для преобразования числа в систему счисления
    char buffer[36];
    char *chars = uppercase ? "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" : "0123456789abcdefghijklmnopqrstuvwxyz";
    int i = 0, sign = (number < 0) ? -1 : 1;
    number = abs(number); // Обработка отрицательных чисел
    while (number > 0) {
        
        buffer[i++] = chars[number % base];
        number /= base;
    }
    if (sign < 0) {
        buffer[i++] = '-';
    }
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", buffer[j]);
    }
}

void to_lowercase(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}

void to_uppercase(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

long long str_to_int(const char *str, int base) {
    return strtoll(str, NULL, base);
}

void print_memory_dump(const void *ptr, size_t size) {
    const unsigned char *byte_ptr = (const unsigned char *)ptr;
    for (size_t i = 0; i < size; i++) {
        printf("%02x", byte_ptr[i]);
        if (i < size - 1) {
            printf(" ");
        }
    }
}

void overprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    for (const char *p = format; *p != '\0'; p++) {
        if (*p == '%') {
            p++;
            char first = *p;
            p++;
            char second = *p;
            if(first == 'R' && second == 'o') {
                print_roman(va_arg(args, int));
            }
            else if (first == 'Z' && second == 'r') {
                print_cekendorf(va_arg(args, unsigned int));
            }
            else if (first == 'C' && second == 'v') {
                print_number_base(va_arg(args, int), va_arg(args, int), 0); // Низкий регистр
            }
            else if (first == 'C' && second == 'V') {
                print_number_base(va_arg(args, int), va_arg(args, int), 1); // Высокий регистр
            }
            else if (first == 'T' && second == 'O') {
                char *str = va_arg(args, char *);
                int base = va_arg(args, int);
                if (base < 2 || base >= 36) base = 10;
                to_uppercase(str);
                long long value = str_to_int(str, base);
                printf("%lld", value);
            }
            else if (first == 't' && second == 'o') {
                char *str = va_arg(args, char *);
                int base = va_arg(args, int);
                if (base < 2 || base >= 36) base = 10;
                to_lowercase(str);
                long long value = str_to_int(str, base);
                printf("%lld", value);
            }
            else if (first == 'm' && second == 'i') {
                int num = va_arg(args, int);
                print_memory_dump(&num, sizeof(int));
            }
            else if (first == 'm' && second == 'u') {
                unsigned int numu = va_arg(args, unsigned int); // Получаем unsigned int
                print_memory_dump(&numu, sizeof(unsigned int)); // Передаем адрес
            }
            else if (first == 'm' && second == 'd') {
                double numd = va_arg(args, double); // Получаем double
                print_memory_dump(&numd, sizeof(double)); // Передаем адрес
            }
            else if (first == 'm' && second == 'f') {
                float numf = va_arg(args, double); // Примечание: float передается как double
                print_memory_dump(&numf, sizeof(float)); // Передаем адрес
            }
            else if (first == 'd') {
                *p--;
                printf("%d", va_arg(args, int));
            }
            else if (first == 'i') {
                *p--;
                printf("%i", va_arg(args, int));
            }
            else if (first == 'l' && second == 'i') {
                printf("%ld", va_arg(args, long int));
            }
            else if (first == 'l' && second == 'd') {
                printf("%ld", va_arg(args, long int));
            }
            else if (first == 'u' && second == 'd') {
                printf("%ud", va_arg(args, unsigned int));
            }
            else if (first == 'f') {
                *p--;
                printf("%f", va_arg(args, double));
            }
            else if (first == 's') {
                *p--;
                printf("%s", va_arg(args, char*));
            }
            else if (first == 'c') {
                *p--;
                printf("%c", (char)va_arg(args, int));
            }
            else {
                perror("Введен не существующий флаг");
                exit(EXIT_FAILURE);
            }
        }
        else {
            putchar(*p);
        }
    }

    va_end(args);
}

void oversprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(str, 1024, format, args); // Ограничение по размеру строки
    va_end(args);
}

void fprint_roman(int num, FILE *output) {
    const char *roman_numerals[][2] = {
        {"M", "1000"},
        {"CM", "900"},
        {"D", "500"},
        {"CD", "400"},
        {"C", "100"},
        {"XC", "90"},
        {"L", "50"},
        {"XL", "40"},
        {"X", "10"},
        {"IX", "9"},
        {"V", "5"},
        {"IV", "4"},
        {"I", "1"},
    };

    if (num < 1 || num > 3999) {
        fprintf(output, "Invalid Roman numeral range\n");
        return;
    }

    for (int i = 0; i < 13; i++) {
        while (num >= atoi(roman_numerals[i][1])) {
            fprintf(output, "%s", roman_numerals[i][0]);
            num -= atoi(roman_numerals[i][1]);
        }
    }
}

void fprint_cekendorf(unsigned int num, FILE *output) {
    int fib[32] = {1, 2};
    for (int i = 2; i < 32; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    unsigned int representation[32] = {0};
    int index = 0;
    for (int i = 31; i >= 0; i--) {
        if (fib[i] <= num) {
            representation[index++] = 1;
            num -= fib[i];
        } else if (index > 0) {
            representation[index++] = 0;
        }
    }
    for (int i = index - 1; i >= 0; i--) {
        fprintf(output, "%u", representation[i]);
    }
    fprintf(output, "1"); // завершающая единица
}

void fprint_number_base(int base, int number, int uppercase, FILE *output) {
    char buffer[36];
    char *chars = uppercase ? "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" : "0123456789abcdefghijklmnopqrstuvwxyz";
    int i = 0, sign = (number < 0) ? -1 : 1;
    number = abs(number);
    while (number > 0) {
        buffer[i++] = chars[number % base];
        number /= base;
    }
    if (sign < 0) {
        buffer[i++] = '-';
    }
    for (int j = i - 1; j >= 0; j--) {
        fprintf(output, "%c", buffer[j]);
    }
}

void fprint_memory_dump(FILE *output, const void *ptr, size_t size) {
    const unsigned char *byte_ptr = (const unsigned char *)ptr;
    for (size_t i = 0; i < size; i++) {
        fprintf(output, "%02x", byte_ptr[i]);
        if (i < size - 1) {
            fprintf(output, " ");
        }
    }
}

void overfprintf(FILE *output, const char *format, ...) {
    va_list args;
    va_start(args, format);
    for (const char *p = format; *p != '\0'; p++) {
        if (*p == '%') {
            p++;
            char first = *p;
            p++;
            char second = *p;
            if (first == 'R' && second == 'o') {
                fprint_roman(va_arg(args, int), output);
            }
            else if (first == 'Z' && second == 'r') {
                fprint_cekendorf(va_arg(args, unsigned int), output);
            }
            else if (first == 'C' && second == 'v') {
                fprint_number_base(va_arg(args, int), va_arg(args, int), 0, output);
            }
            else if (first == 'C' && second == 'V') {
                fprint_number_base(va_arg(args, int), va_arg(args, int), 1, output);
            }
            else if (first == 'T' && second == 'O') {
                char *str = va_arg(args, char *);
                int base = va_arg(args, int);
                if (base < 2 || base >= 36)
                    base = 10;
                to_uppercase(str);
                long long value = str_to_int(str, base);
                fprintf(output, "%lld", value);
            }
            else if (first == 't' && second == 'o') {
                char *str = va_arg(args, char *);
                int base = va_arg(args, int);
                if (base < 2 || base >= 36) 
                    base = 10;
                to_lowercase(str);
                long long value = str_to_int(str, base);
                fprintf(output, "%lld", value);
            }
            else if (first == 'm' && second == 'i') {
                int num = va_arg(args, int);
                fprint_memory_dump(output, &num, sizeof(int));
            }
            else if (first == 'm' && second == 'u') {
                unsigned int numu = va_arg(args, unsigned int);
                fprint_memory_dump(output, &numu, sizeof(unsigned int));
            }
            else if (first == 'm' && second == 'd') {
                double numd = va_arg(args, double);
                fprint_memory_dump(output, &numd, sizeof(double));
            }
            else if (first == 'm' && second == 'f') {
                float numf = va_arg(args, double); // float передается как double
                fprint_memory_dump(output, &numf, sizeof(float));
            }
            else if (first == 'd') {
                *p--;
                fprintf(output, "%d", va_arg(args, int));
            }
            else if (first == 'i') {
                *p--;
                fprintf(output, "%i", va_arg(args, int));
            }
            else if (first == 'l' && second == 'i') {
                fprintf(output, "%ld", va_arg(args, long int));
            }
            else if (first == 'l' && second == 'd') {
                fprintf(output, "%ld", va_arg(args, long int));
            }
            else if (first == 'u') {
                *p--;
                fprintf(output, "%u", va_arg(args, unsigned int));
            }
            else if (first == 'u' && second == 'd') {
                fprintf(output, "%ui", va_arg(args, unsigned int));
            }
            else if (first == 'f') {
                *p--;
                fprintf(output, "%f", va_arg(args, double));
            }
            else if (first == 's') {
                *p--;
                fprintf(output, "%s", va_arg(args, char*));
            }
            else if (first == 'c') {
                *p--;
                fprintf(output, "%c", (char)va_arg(args, int));
            }
            else {
                perror("Введен не существующий флаг");
                exit(EXIT_FAILURE);
            }
        }
        else {
            fputc(*p, output);
        }
    }

    va_end(args);
}

int main() {
    overprintf("Римское число 36: %Ro\n", 36);
    overprintf("Цекендорфово представление 10: %Zr\n", 10);
    overprintf("10 в двоичной: %Cv\n", 10, 2);
    overprintf("10 в шестнадцатеричной: %CV\n", 10, 16);
    char num1[] = "1a";
    overprintf("num1 в десятичной: %to\n", num1, 16);
    char num2[] = "2B";
    overprintf("num2 в десятичной: %TO\n", num2, 16);
    int num = -12345;
    overprintf("Дамп памяти int -12345: %mi\n", num);
    unsigned int numu = 12345;
    overprintf("Дамп памяти unsigned int 12345: %mu\n", numu);
    double numd = 12.34;
    overprintf("Дамп памяти double 12.34: %md\n", numd);
    float numf = 12.34f;
    overprintf("Дамп памяти float 12.34: %mf\n", numf);
    overprintf("%i\n", 1);
    FILE *file = fopen("output.txt", "w");
    if (!file) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }
    overfprintf(file, "Римское число 36: %Ro\n", 36);
    overfprintf(file, "Цекендорфово представление 10: %Zr\n", 10);
    overfprintf(file, "10 в двоичной: %Cv\n", 10, 2);
    overfprintf(file, "10 в шестнадцатеричной: %CV\n", 10, 16);
    overfprintf(file, "num1 в десятичной: %to\n", num1, 16);
    overfprintf(file, "num2 в десятичной: %TO\n", num2, 16);
    overfprintf(file, "Дамп памяти int -12345: %mi\n", num);
    overfprintf(file, "Дамп памяти unsigned int 12345: %mu\n", numu);
    overfprintf(file, "Дамп памяти double 12.34: %md\n", numd);
    overfprintf(file, "Дамп памяти float 12.34: %mf\n", numf);
    fclose(file);
    return 0;
}