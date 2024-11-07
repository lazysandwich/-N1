#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_GROUP_LEN 50
#define MAX_GRADES 5

typedef struct {
    unsigned int id;
    char name[MAX_NAME_LEN];
    char last_name[MAX_NAME_LEN];
    char group[MAX_GROUP_LEN];
    unsigned char* grades;
} Student;

Student* read_students_from_file(const char* file_path, size_t* count) {
    FILE* file = fopen(file_path, "r");
    if (!file) {
        perror("файл не открыл");
        exit(EXIT_FAILURE);
    }
    fscanf(file, "%zu", count);
    Student* students = malloc(*count * sizeof(Student));
    if (!students) {
        perror("ошибка с паматью");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < *count; i++) {
        students[i].grades = malloc(MAX_GRADES * sizeof(unsigned char));
        fscanf(file, "%u %s %s %s", &students[i].id, students[i].name, students[i].last_name, students[i].group);
        for (int j = 0; j < MAX_GRADES; j++) {
            fscanf(file, "%hhu", &students[i].grades[j]);
        }
    }
    fclose(file);
    return students;
}

void free_students(Student* students, size_t count) {
    for (size_t i = 0; i < count; i++) {
        free(students[i].grades);
    }
    free(students);
}

int compare_by_id(const void* a, const void* b) {
    return ((Student*)a)->id - ((Student*)b)->id;
}

int compare_by_last_name(const void* a, const void* b) {
    return strcmp(((Student*)a)->last_name, ((Student*)b)->last_name);
}

int compare_by_first_name(const void* a, const void* b) {
    return strcmp(((Student*)a)->name, ((Student*)b)->name);
}

int compare_by_group(const void* a, const void* b) {
    return strcmp(((Student*)a)->group, ((Student*)b)->group);
}

void search_student_by_id(Student* students, size_t count, unsigned int id, FILE* trace_file) {
    for (size_t i = 0; i < count; i++) {
        if (students[i].id == id) {
            double avg_grade = calculate_average_grade(&students[i]);
            fprintf(trace_file, "найден студент по ID %u: %s %s, группа: %s, средняя оценка: %.2f\n", 
                    id, students[i].name, students[i].last_name, students[i].group, avg_grade);
            printf("найден студент по ID %u: %s %s, группа: %s, средняя оценка: %.2f\n", 
                   students[i].name, students[i].last_name, students[i].group, avg_grade);
            return;
        }
    }
    printf("нет таких студента %u.\n", id);
}

void search_students_by_name(Student* students, size_t count, const char* name, FILE* trace_file) {
    int found = 0;
    for (size_t i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            found = 1;
            fprintf(trace_file, "найден студент: %s %s, группа: %s\n", 
                    students[i].name, students[i].last_name, students[i].group);
            printf("найден студент: %s %s, группа: %s\n", 
                   students[i].name, students[i].last_name, students[i].group);
        }
    }
    if (!found) {
        printf("нет таого студента.\n");
    }
}

void search_students_by_last_name(Student* students, size_t count, const char* last_name, FILE* trace_file) {
    int found = 0;
    for (size_t i = 0; i < count; i++) {
        if (strcmp(students[i].last_name, last_name) == 0) {
            found = 1;
            fprintf(trace_file, "найден студент: %s %s, группа: %s\n", 
                    students[i].name, students[i].last_name, students[i].group);
            printf("найден студент: %s %s, группа: %s\n", 
                   students[i].name, students[i].last_name, students[i].group);
        }
    }
    if (!found) {
        printf("нет таких студентов.\n");
    }
}

void search_students_by_group(Student* students, size_t count, const char* group, FILE* trace_file) {
    int found = 0;
    for (size_t i = 0; i < count; i++) {
        if (strcmp(students[i].group, group) == 0) {
            found = 1;
            fprintf(trace_file, "найден студента: %s %s, группы: %s\n", students[i].name, students[i].last_name, students[i].group);
            printf("найден студент: %s %s, группа: %s\n", students[i].name, students[i].last_name, students[i].group);
        }
    }
    if (!found) {
        printf("да нету таких студентов.\n");
    }
}

void list_students_above_average(Student* students, size_t count, double avg_score, FILE* trace_file) {
    int found = 0;
    fprintf(trace_file, "студенты со средней оценкой выше %.2f:\n", avg_score);
    for (size_t i = 0; i < count; i++) {
        double student_avg = calculate_average_grade(&students[i]);
        if (student_avg > avg_score) {
            found = 1;
            fprintf(trace_file, "%s %s\n", students[i].name, students[i].last_name);
            printf("%s %s\n", students[i].name, students[i].last_name);
        }
    }
    if (!found) {
        fprintf(trace_file, "нет таких студентов.\n");
        printf("нет таких студентов.\n");
    }
}

double calculate_average_grade(const Student* student) {
    unsigned int total = 0;
    for (int i = 0; i < MAX_GRADES; i++) {
        total += student->grades[i];
    }
    return (double)total / MAX_GRADES;
}

double calculate_overall_average_grade(Student* students, size_t count) {
    unsigned int total = 0;
    for (size_t i = 0; i < count; i++) {
        total += calculate_average_grade(&students[i]);
    }
    return (double)total / count;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprint("неверное кол-во файлов\n");
        exit(EXIT_FAILURE);
    }

    size_t student_count = 0;
    Student* students = read_students_from_file(argv[1], &student_count);
    if (!students) {
        return EXIT_FAILURE;
    }

    FILE* trace_file = fopen(argv[2], "w");
    if (!trace_file) {
        perror("я не могу открыть этот файл");
        free_students(students, student_count);
        return EXIT_FAILURE;
    }

    int choice;
    while (1) {
        printf("Menu:\n");
        printf("1. поиск студента по ID\n");
        printf("2. поиск студента по фамилии\n");
        printf("3. поиск студента по имени\n");
        printf("4. поиск студента по группе\n");
        printf("5. список людей с высокой средней оценкой\n");
        printf("6. вы ход\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                unsigned int id;
                printf("введите ID: ");
                scanf("%u", &id);
                search_student_by_id(students, student_count, id, trace_file);
                break;
            }
            case 2: {
                char last_name[MAX_NAME_LEN];
                printf("введите фамилию: ");
                scanf("%s", last_name);
                search_students_by_last_name(students, student_count, last_name, trace_file);
                break;
            }
            case 3: {
                char first_name[MAX_NAME_LEN];
                printf("введите имя: ");
                scanf("%s", first_name);
                search_students_by_name(students, student_count, first_name, trace_file);
                break;
            }
            case 4: {
                char group[MAX_GROUP_LEN];
                printf("введите группу: ");
                scanf("%s", group);
                search_students_by_group(students, student_count, group, trace_file);
                break;
            }
            case 5: {
                double overall_avg = calculate_overall_average_grade(students, student_count);
                list_students_above_average(students, student_count, overall_avg, trace_file);
                break;
            }
            case 6:
                fclose(trace_file);
                free_students(students, student_count);
                return EXIT_SUCCESS;
            default:
                printf("нет такого выбора.\n");
        }
    }
    fclose(trace_file);
    free_students(students, student_count);
    return EXIT_SUCCESS;
}