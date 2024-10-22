#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 100

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

void conv_base(long long value, int base, char *output) {
    char buffer[65];
    int index = 0;
    if (value < 0) {
        value = -value;
        output[index++] = '-';
    }
    do { // Преобразование значения в строку с заданным основанием
        int digit = value % base;
        buffer[index++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
        value /= base;
    } while (value > 0);
    for (int i = index - 1; i >= 0; i--) { // Заполнение выходной строки в обратном порядке
        output[strlen(output)] = buffer[i];
    }
    output[strlen(output)] = '\0'; // Добавляем нуль-терминатор
}

int main(int argv, char* argc[]) {
    char input[MAX_INPUT_LENGTH];
    if (argv < 4) {
        printf("Неправильное количество аргументов\n");
        return 1;
    }
    if (strcmp(argc[argv - 1], "Stop")) {
        printf("Нет слова Stop или Stop не последнее слово\n");
        return 1;
    }
    if (is_i(argc[1])) {
        return 1;
    }
    int base = atoi(argc[1]);
    long long max_val = -0;
    
    char max_str[MAX_INPUT_LENGTH];
    if (base < 2 || base > 36) {
        printf("Некорректное основание.\n");
        return 1;
    }
    int j = 2;
    while (strcmp(argc[j], "Stop")) {
        long long val = 0;
        int length = strlen(argc[j]);
        for (int i = 0; i < length; i++) {
            if (isdigit(argc[j][i])) {
                if ((argc[j][i] - '0') >= base) {
                    printf("Введено неправильное число\n");
                    return 1;
                }
                
                val = val * base + argc[j][i] - '0'; // Для цифр
            }
            else {
                if (argc[j][i] < 'a' || argc[j][i] > 'z') {
                    printf("Введено неправильное число\n");
                    return 1;
                }
                if (argc[j][i] - 'a' + 10 >= base) {
                    printf("Введено неправильное число\n");
                    return 1;
                }
                val = val * base + argc[j][i] - 'a' + 10; // Для букв (a-z)
            }
        }
        if (val > max_val) {
            max_val = val;
            strcpy(max_str, input); // Сохраняем строковое представление
        }
        j++;
    }
    printf("Максимальноe по модулю число: %s\n", max_str);
    printf("Преобразования в основаниях 9, 18, 27, 36:\n");
    char output_str[MAX_INPUT_LENGTH];
    for (int b = 9; b <= 36; b += 9) {
        output_str[0] = '\0';
        conv_base(max_val, b, output_str);
        printf("Основание %d: %s\n", b, output_str);
    }
    return 0;
}
