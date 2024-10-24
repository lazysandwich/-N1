
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_NUM_LENGTH 1024

char value_to_char(int value) {
    if (value < 10) {
        return '0' + value;
    }
    return 'a' + (value - 10);
}

char* add(const char* num1, const char* num2, int base) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int carry = 0;
    int max_len = len1 > len2 ? len1 : len2;
    char* result = (char*)malloc(max_len + 2);
    if (!result) 
        return NULL;
    result[max_len + 1] = '\0';
    
    int i = 0;
    while (i < max_len || carry) {
        int digit1 = (i < len1) ? (isdigit(num1[len1 - 1 - i]) ? num1[len1 - 1 - i] - '0' : tolower(num1[len1 - 1 - i]) - 'a' + 10) : 0;
        int digit2 = (i < len2) ? (isdigit(num2[len2 - 1 - i]) ? num2[len2 - 1 - i] - '0' : tolower(num2[len2 - 1 - i]) - 'a' + 10) : 0;
        
        int sum = digit1 + digit2 + carry;
        carry = sum / base;
        sum %= base;
        
        result[max_len - i] = value_to_char(sum);
        i++;
    }
    
    if (carry) {
        result[max_len - i] = value_to_char(carry);
        return strdup(result + max_len - i); // Возвращаем результат без ведущих нулей
    }
    
    return strdup(result + max_len - i + 1);
}

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

char* sum_base(int base, int size, char** nums) {
    char* total = strdup("0");
    for (int i = 0; i < size; i++) {
        char* num = nums[i];
        char* new_total = add(total, num, base);
        free(total);
        total = new_total;
    }
    return total;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Неверное количество аргументов\n");
        return 1;
    }
    int base = matoi(argv[1]);
    if (base < 2 || base > 36) {
        printf("Неверная база\n");
        return 1;
    }
    char* nums[argc - 2];
    for (int i = 0; i < argc - 2; i++) {
        nums[i] = argv[i + 2];
    }
    char *sum = sum_base(base, argc - 2, nums);
    printf("Сумма в системе счисления с основанием %d: %s\n", base, sum);
    free(sum);
    return 0;
}