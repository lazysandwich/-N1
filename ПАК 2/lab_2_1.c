#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void count_length(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    printf("Длина строки - %d\n", length);
}

void reverse(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    char *reversed = malloc(length + 1);
    for (unsigned int i = 0; i < length; i++) {
        reversed[i] = str[length - 1 - i];
    }
    reversed[length] = '\0';
    printf("%s\n", reversed);
    free(reversed);
}

void u_pos(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    char *result = malloc(sizeof(char) * (length));
    unsigned int i = 0;
    while (str[i] != '\0') {
        result[i] = (i % 2 == 1) ? toupper(str[i]) : str[i];
        i++;
    }
    printf("%s\n", result);
    free(result);
}

void func(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    char *numbers = malloc(sizeof(char) * (length));
    char *letters = malloc(sizeof(char) * (length));
    char *others = malloc(sizeof(char) * (length));
    unsigned int num_idx = 0, letter_idx = 0, other_idx = 0;
    for (unsigned int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i])) {
            numbers[num_idx++] = str[i];
        }
        else if (isalpha(str[i])) {
            letters[letter_idx++] = str[i];
        }
        else {
            others[other_idx++] = str[i];
        }
    }
    printf("%s%s%s\n", numbers, letters, others);
    free(numbers);
    free(letters);
    free(others);
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

void concat_strings(unsigned int seed, int argv, char **argc) {
    srand(seed);
    char result[1000];
    int ind = 0, o = argv - 4;
    int positions[argv - 4];
    for (int i = 0; i < argv - 4; i++) {
        positions[i] = 0;
    }
    while (o != 0) {
        int place = rand() % (argv - 4);
        if (positions[place] == 0) {
            int j = 0;
            o--;
            positions[place] = 1;
            while (argc[place + 4][j] != '\0') {
                result[ind] = argc[place + 4][j];
                ind++;
                j++;
            }
        }
    }
    for (int i = 0; i < ind; i++) {
        printf("%c", result[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Неверное количество аргументов\n");
        return 1;
    }
    if (argv[1][0] != '-') {
        printf("Неверно введен флaг\n");
        return 1;
    }
    char flag = argv[1][1];
    char *input_string = argv[2];
    switch (flag) {
        case 'l':
            count_length(input_string);
            break;
        case 'r':
            reverse(input_string);
            break;
        case 'u':
            u_pos(input_string);
            break;
        case 'n':
            func(input_string);
            break;
        case 'c':
            if (argc < 4) {
                printf("Неверное количество аргументов\n");
                return 1;
            }
            unsigned int seed = (unsigned int)matoi(argv[3]);
            concat_strings(seed, argc, argv);
            break;
        default:
            printf("Неизвестный флаг\n");
            return 1;
    }
    return 0;
}