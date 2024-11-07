#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *chars;
    int length;
} String;

String createString(const char *value) {
    String str;
    str.length = strlen(value);
    str.chars = (char *)malloc((str.length + 1) * sizeof(char));
    if (str.chars) {
        strcpy(str.chars, value);
    }
    return str;
}

void deleteString(String *str) {
    if (str->chars) {
        free(str->chars);
        str->chars = NULL;
        str->length = 0;
    }
}

int compareStrings(const String *a, const String *b) {
    if (a->length != b->length) {
        return a->length - b->length;
    }
    return strcmp(a->chars, b->chars);
}

int areStringsEqual(const String *a, const String *b) {
    return (a->length == b->length) && (strcmp(a->chars, b->chars) == 0);
}

void copyString(String *dest, const String *src) {
    deleteString(dest);
    dest->length = src->length;
    dest->chars = (char *)malloc((dest->length + 1) * sizeof(char));
    if (dest->chars) {
        strcpy(dest->chars, src->chars);
    }
}

String copyStringToNew(const String *src) {
    return createString(src->chars);
}

String concatenateStrings(const String *a, const String *b) {
    String result;
    result.length = a->length + b->length;
    result.chars = (char *)malloc((result.length + 1) * sizeof(char));
    if (result.chars) {
        strcpy(result.chars, a->chars);
        strcat(result.chars, b->chars);
    }
    return result;
}

int main() {
    String str1 = createString("Hello");
    String str2 = createString("World");
    int cmp = compareStrings(&str1, &str2);
    printf("результат композиции: %d\n", cmp);
    printf("равны ли строки %d\n", areStringsEqual(&str1, &str2));
    String str3;
    copyString(&str3, &str1);
    printf("копирование строки: %s\n", str3.chars);
    String str4 = copyStringToNew(&str2);
    printf("новая скопированная строка: %s\n", str4.chars);
    String concatenated = concatenateStrings(&str1, &str2);
    printf("конканированиая строка: %s\n", concatenated.chars);
    deleteString(&str1);
    deleteString(&str2);
    deleteString(&str3);
    deleteString(&str4);
    deleteString(&concatenated);
    return 0;
}