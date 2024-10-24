#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>



void search(const char *substring, int size, char **argc) {
    for (int i = 0; i < size; i++) {
        const char *filename = argc[i + 2];
        FILE *file = fopen(filename, "r");
        if (!file) {
            perror("Ошибка открытия файла\n");
            exit(EXIT_FAILURE);
        }
        char *line = NULL;
        size_t len = 0;
        int line_num = 0;
        while (getline(&line, &len, file) != -1) {
            line_num++;
            char *pos = line;
            int char_index;
            while (*pos != '\0') {
                char_index = pos - line + 1;
                int j;
                for (j = 0; substring[j] != '\0' && pos[j] == substring[j]; j++);
                if (substring[j] == '\0') {
                    printf("Найден подстрака в файле: %s, в строке: %d, на: %d месте\n", filename, line_num, char_index);
                }
                pos++;
            }
        }
        free(line);
        fclose(file);
    }
}

int main(int argv, char *argc[]) {
    if (argv < 3) {
        printf("Неверное количество аргументов\n");
        return 1;
    }
    search(argc[1], argv - 2, argc);
    return 0;
}