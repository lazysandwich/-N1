
#include <stdio.h>

void to_base(int n, int base, char *result) {
    if (n == 0) {
        *result = '0';
        *(result + 1) = '\0';
        return;
    }

    char *ptr = result;
    while (n > 0) {
        *ptr = (n & (base - 1)) + '0';
        if (*ptr > '9') {
            *ptr += 'A' - '0' - 10;
        }
        ptr++;
        n >>= (base == 2) ? 1 : (base == 4) ? 2 : (base == 8) ? 3 : (base == 16) ? 4 : 5;
    }
    *ptr = '\0';
    char *start = result;
    char *end = ptr - 1;
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int main() {
    int decimal_number = 10;
    int bases[] = {2, 4, 8, 16, 32};
    char result[32];
    for (int i = 0; i < 5; i++) {
        int base = bases[i];
        to_base(decimal_number, base, result);
        printf("Число %d в системе счисления с основанием %d равно %s.\n", decimal_number, base, result);
    }
    return 0;
}
