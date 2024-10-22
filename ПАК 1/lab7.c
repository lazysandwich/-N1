#include <stdio.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

void read_tokens(FILE *file, char *tokens[], int *count) {
    char buffer[MAX_LINE_LENGTH];
    *count = 0;

    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        char *token = strtok(buffer, " \t\n");
        while (token != NULL) {
            tokens[(*count)++] = strdup(token); // Сохранение лексемы
            token = strtok(NULL, " \t\n");
        }
    }
}

void write_tokens_to_file(char *output_path, char *file1_tokens[], int count1, char *file2_tokens[], int count2) {
    FILE *output_file = fopen(output_path, "w");
    if (!output_file) {
        perror("Ошибка открытия выходного файла");
        return;
    }

    int i = 0, j = 0;
    int max_count = count1 > count2 ? count1 : count2;

    for (int k = 0; k < max_count; k++) {
        if (k % 2 == 0 && i < count1) { // Четные индексы из file1
            fprintf(output_file, "%s ", file1_tokens[i++]);
        } else if (j < count2) { // Нечетные индексы из file2
            fprintf(output_file, "%s ", file2_tokens[j++]);
        }
    }

    fclose(output_file);
}

void free_tokens(char *tokens[], int count) {
    for (int i = 0; i < count; i++) {
        free(tokens[i]);
    }
}

int conv4(int i) {
    int o = 0, t = 1;
    while (i != 0) {
        if (o != 0) {
            t *= 10;
        }
        o *= 10;
        o += i % 4;
        i /= 4;
    }
    int rev = 0;
    while (o != 0) {
        rev *= 10;
        rev += o / t;
        o %= t;
        t /= 10;
    }
    return rev;
}

int conv8(int i) {
    int o = 0, t = 1;
    while (i != 0) {
        if (o != 0) {
            t *= 10;
        }
        o *= 10;
        o += i % 8;
        i /= 8;
    }
    int rev = 0;
    while (o != 0) {
        rev *= 10;
        rev += o / t;
        o %= t;
        t /= 10;
    }
    return rev;
}

int main(int argv, char *argc[]) {
    if (argv < 4) {
        printf("Неверное количество аргументов\n");
        return 1;
    }
    char *flag = argc[1];
    if (strcmp(flag, "-r") == 0) {
        if (argv != 5) {
            printf("Неверное количество аргументов\n");
            return 1;
        }
        char *file1_path = argc[2];
        char *file2_path = argc[3];
        char *output_file_path = argc[4];

        FILE *file1 = fopen(file1_path, "r");
        FILE *file2 = fopen(file2_path, "r");

        struct stat buf1, buf2, buf3;
        stat(file1_path, &buf1);
        stat(file2_path, &buf2);
        stat(output_file_path, &buf3);

        if (buf1.st_ino == buf3.st_ino || buf3.st_ino == buf2.st_ino) {
            printf("Выходной файл тот же, что и входной\n");
            return 1;
        }

        if (!file1 || !file2) {
            perror("Ошибка открытия одного из входных файлов");
            if (file1) fclose(file1);
            if (file2) fclose(file2);
            return EXIT_FAILURE;
        }

        char *file1_tokens[MAX_LINE_LENGTH];
        char *file2_tokens[MAX_LINE_LENGTH];
        int count1, count2;

        read_tokens(file1, file1_tokens, &count1);
        read_tokens(file2, file2_tokens, &count2);

        write_tokens_to_file(output_file_path, file1_tokens, count1, file2_tokens, count2);
        fclose(file1);
        fclose(file2);
    }
    else if (strcmp(flag, "-a") == 0) {
        if (argv != 4) {
            printf("Неверное количество аргументов\n");
            return 1;
        }
        FILE *input = fopen(argc[2], "r");
        FILE *output = fopen(argc[3], "w");
        struct stat buf1, buf2;
        stat(argc[2], &buf1);
        stat(argc[3], &buf2);
        if (buf1.st_ino == buf2.st_ino) {
            printf("Выходной файл тот же, что и входной\n");
            return 1;
        }
        if (!input || !output) {
            perror("Ошибка открытия файла");
            exit(EXIT_FAILURE);
        }
        char line[MAX_LINE_LENGTH];
        int lexeme_count = 0;
        while (fgets(line, sizeof(line), input)) {
            char *token = strtok(line, " \t\n");
            while (token) {
                lexeme_count++;
                int len = strlen(token);
                char processed[MAX_LINE_LENGTH] = {0};
                if (lexeme_count % 10 == 0) {
                    for (int i = 0; i < len; i++) {
                        fprintf(output, "%d", conv4((int)tolower(token[i])));
                    }
                    fprintf(output, " ");
                }
                else if (lexeme_count % 5 == 0) {
                    for (int i = 0; i < len; i++) {
                        fprintf(output, "%d", conv8((int)tolower(token[i])));
                    }
                    fprintf(output, " ");
                }
                else if (lexeme_count % 2 == 0) {
                    for (int i = 0; i < len; i++) {
                        processed[i] = tolower(token[i]);
                    }
                    fprintf(output, "%s ", processed);
                }
                else {
                    fprintf(output, "%s ", token);
                }
                token = strtok(NULL, " \t\n");
            }
        }
        fclose(input);
        fclose(output);
    }
    else {
        printf("Неверно введен флаг\n");
        return 1;
    }
    return 0;
}
