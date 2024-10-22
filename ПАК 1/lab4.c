#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

int main(int argv, char* argc[]) {
    if (argv < 3) {
        printf("Неверное количество аргументов\n");
        return 1;
    }
    char* flag = argc[1]; 
    char* in_file = argc[2];
    char out_file[300];
    if (flag[1] == 'n') {
        if (argv != 4) {
            printf("Неверное количество аргументов\n");
            return 1;
        }
        strcpy(out_file, argc[3]);
    }
    else if (argv != 3) {
        printf("Неверное количество аргументов\n");
        return 1;
    }
    else {
        snprintf(out_file, sizeof(out_file), "out_%s", in_file);
    }
    FILE *inp = fopen(in_file, "r");
    if (!inp) {
        perror("Ошбка при открытии input файла");
        return 1;
    }
    FILE *out = fopen(out_file, "w");
    if (!out) {
        perror("Ошбка при открытии output файла");
        return 1;
    }
    struct stat buf1, buf2;
    stat(in_file, &buf1);
    stat(out_file, &buf2);
    if (buf1.st_ino == buf2.st_ino) {
        printf("Выходной файл тот же, что и входной\n");
        return 1;
    }
    if (flag[0] != '-' && flag[0] != '/') {
        fclose(inp);
        fclose(out);
        printf("Неправильно введен флаг\n");
        return 1;
    }
    if (strcmp(flag, "-d") == 0 || strcmp(flag, "/d") == 0 || strcmp(flag, "/nd") == 0 || strcmp(flag, "-nd") == 0) {
        int c = fgetc(inp);
        while (c != EOF) {
            if (!isdigit(c)) {
                fputc(c, out);
            }
            c = fgetc(inp);
        }
    }
    else if (strcmp(flag, "-i") == 0 || strcmp(flag, "/i") == 0 || strcmp(flag, "/ni") == 0 || strcmp(flag, "-ni") == 0) {
        char line[256];
        while (fgets(line, sizeof(line), inp)) {
            int count = 0;
            for (int i = 0; line[i] != '\0'; i++) {
                if (isalpha(line[i]))
                    count++;
            }
            fprintf(out, "%d\n", count);
        }
    }
    else if (strcmp(flag, "-s") == 0 || strcmp(flag, "/s") == 0 || strcmp(flag, "/ns") == 0 || strcmp(flag, "-ns") == 0) {
        char line[256];
        while (fgets(line, sizeof(line), inp)) {
            int count = 0;
            for (int i = 0; line[i] != '\0'; i++) {
                if (!isalpha(line[i]) && !isdigit(line[i]) && !isspace(line[i]))
                    count++;
            }
            fprintf(out, "%d\n", count);
        }
    }
    else if (strcmp(flag, "-a") == 0 || strcmp(flag, "/a") == 0 || strcmp(flag, "/na") == 0 || strcmp(flag, "-na") == 0) {
        char c = fgetc(inp);
        while (c != EOF) {
            if ((!isalnum(c) && !isspace(c)) || isalpha(c)) {
                int ci = c;
                fprintf(out, "%02X", ci);
            }
            else
                fputc(c, out);
            c = fgetc(inp);
        }
    }
    else {
        fclose(inp);
        fclose(out);
        printf("Нет такого флага\n");
        return 1;
    }
    fclose(inp);
    fclose(out);
    return 0;
}
