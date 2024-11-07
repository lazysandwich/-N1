#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LENGTH 50
#define MAX_LINE_LENGTH 256

typedef struct Liver {
    char last_name[MAX_NAME_LENGTH];
    char first_name[MAX_NAME_LENGTH];
    char middle_name[MAX_NAME_LENGTH];
    int day, month, year; 
    char gender; // 'M' или 'W'
    double average_income;
    struct Liver* next;
} Liver;

typedef struct Modification {
    char operation; // 'A' для добавления, 'D' для удаления, 'M' для изменения
    Liver* resident;
    struct Modification* next;
} Modification;

void print_menu() {
    printf("\nMenu:\n");
    printf("1. добавить человека\n");
    printf("2. вывести человека\n");
    printf("3. найти человека\n");
    printf("4. изменить человека\n");
    printf("5. удалить человека\n");
    printf("6. сохохранить файл\n");
    printf("7. убрать прошлое изменение\n");
    printf("8. выход\n");
}

Liver* create_resident(const char* last_name, const char* first_name, const char* middle_name,
    int day, int month, int year, char gender, double income) {
    Liver* resident = (Liver*)malloc(sizeof(Liver));
    strcpy(resident->last_name, last_name);
    strcpy(resident->first_name, first_name);
    strcpy(resident->middle_name, middle_name);
    resident->day = day;
    resident->month = month;
    resident->year = year;
    resident->gender = gender;
    resident->average_income = income;
    resident->next = NULL;
    return resident;
}

void add_resident(Liver** head, Liver* new_resident) {
    if (*head == NULL || calculate_age(new_resident->day, new_resident->month, new_resident->year) < 
        calculate_age((*head)->day, (*head)->month, (*head)->year)) {
        new_resident->next = *head;
        *head = new_resident;
    }
    else {
        Liver* current = *head;
        while (current->next != NULL && 
               calculate_age(new_resident->day, new_resident->month, new_resident->year) > 
               calculate_age(current->next->day, current->next->month, current->next->year)) {
            current = current->next;
        }
        new_resident->next = current->next;
        current->next = new_resident;
    }
}

int calculate_age(int day, int month, int year) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int age = tm.tm_year + 1900 - year;
    if (tm.tm_mon + 1 < month || (tm.tm_mon + 1 == month && tm.tm_mday < day)) {
        age--;
    }
    return age;
}

void print_residents(Liver* head) {
    if (head == NULL) {
        printf("не найдено человека.\n");
        return;
    }
    printf("люди:\n");
    while (head) {
        printf("%s %s %s, дата рождения: %02d.%02d.%d, пол: %c, доход: %.2f\n", 
               head->last_name, head->first_name, head->middle_name,
               head->day, head->month, head->year, head->gender, head->average_income);
        head = head->next;
    }
}

void free_residents(Liver* head) {
    while (head) {
        Liver* temp = head;
        head = head->next;
        free(temp);
    }
}

void load_from_file(const char* filename, Liver** head) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("я чет не могу открыть файл");
        exit(EXIT_FAILURE);
    }
    while (!feof(file)) {
        char last_name[MAX_NAME_LENGTH], first_name[MAX_NAME_LENGTH], middle_name[MAX_NAME_LENGTH];
        int day, month, year;
        char gender;
        double income;
        if (fscanf(file, "%s %s %s %d %d %d %c %lf", last_name, first_name, middle_name, &day, &month, &year, &gender, &income) == 8) {
            Liver* new_resident = create_resident(last_name, first_name, middle_name, day, month, year, gender, income);
            add_resident(head, new_resident);
        }
    }
    fclose(file);
}

void save_to_file(const char* filename, Liver* head) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("файл фигня. я проверил");
        exit(EXIT_FAILURE);
    }
    while (head) {
        fprintf(file, "%s %s %s %d %d %d %c %.2f\n", 
                head->last_name, head->first_name, head->middle_name,
                head->day, head->month, head->year, head->gender, head->average_income);
        head = head->next;
    }
    fclose(file);
}

void search_resident(Liver* head) {
    char last_name[MAX_NAME_LENGTH];
    printf("введите фамилию: ");
    scanf("%s", last_name);
    while (head) {
        if (strcmp(head->last_name, last_name) == 0) {
            printf("найдено: %s %s %s, дата рождения: %02d.%02d.%d, пол: %c, доход: %.2f\n", 
                   head->last_name, head->first_name, head->middle_name,
                   head->day, head->month, head->year, head->gender, head->average_income);
            return;
        }
        head = head->next;
    }
    printf("я таких не видел.\n");
}

void modify_resident(Liver* head) {
    char last_name[MAX_NAME_LENGTH];
    printf("введите фамилию человека для изменения: ");
    scanf("%s", last_name);
    while (head) {
        if (strcmp(head->last_name, last_name) == 0) {
            printf("изменение информации для %s %s %s:\n", head->last_name, head->first_name, head->middle_name);
            printf("введите имя: ");
            scanf("%s", head->first_name);
            printf("введите отчество: ");
            scanf("%s", head->middle_name);
            printf("введите новую дату рождения: ");
            scanf("%d %d %d", &head->day, &head->month, &head->year);
            printf("введите новый пол: ");
            scanf(" %c", &head->gender);
            printf("введите новый доход: ");
            scanf("%lf", &head->average_income);
            return;
        }
        head = head->next;
    }
    printf("чувак не найден.\n");
}

void delete_resident(Liver** head) {
    char last_name[MAX_NAME_LENGTH];
    printf("впишите фамилию резидента для удаления(не из жизни): ");
    scanf("%s", last_name);
    Liver* current = *head;
    Liver* previous = NULL;
    while (current) {
        if (strcmp(current->last_name, last_name) == 0) {
            if (previous) {
                previous->next = current->next;
            }
            else {
                *head = current->next;
            }
            free(current);
            printf("челобрек удален.\n");
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("нет таких.\n");
}

void undo_modifications(Modification* undo_stack, Liver* residents) {
    int count = 0;
    Modification* temp = &undo_stack;
    while (temp) {
        count++;
        temp = temp->next;
    }
    int undo_count = count / 2;
    while (undo_count > 0 && &undo_stack) {
        Modification* undo = &undo_stack;
        undo_stack = (undo_stack)->next;
        if (undo->operation == 'A') {
            delete_resident(residents);
        } else if (undo->operation == 'D') {
            add_resident(residents, undo->resident);
        }
        free(undo);
        undo_count--;
    }
    printf("возвращено %d действий.\n", count / 2);
}

void push_modification(Modification** undo_stack, char operation, Liver* resident) {
    Modification* new_modification = (Modification*)malloc(sizeof(Modification));
    new_modification->operation = operation;
    new_modification->resident = resident;
    new_modification->next = *undo_stack;
    *undo_stack = new_modification;
}

int main() {
    Liver* residents = NULL;
    Modification* undo_stack = NULL;
    char filename[MAX_LINE_LENGTH];

    printf("Введите путь к файлу с людьмиe: ");
    scanf("%s", filename);
    load_from_file(filename, &residents);

    int choice;
    do {
        print_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                char last_name[MAX_NAME_LENGTH], first_name[MAX_NAME_LENGTH], middle_name[MAX_NAME_LENGTH];
                int day, month, year;
                char gender;
                double income;
                printf("фамилия: ");
                scanf("%s", last_name);
                printf("имя: ");
                scanf("%s", first_name);
                printf("отчество: ");
                scanf("%s", middle_name);
                printf("дата рождения: ");
                scanf("%d %d %d", &day, &month, &year);
                printf("пол: ");
                scanf(" %c", &gender);
                printf("доход: ");
                scanf("%lf", &income);
                Liver* new_resident = create_resident(last_name, first_name, middle_name, day, month, year, gender, income);
                add_resident(&residents, new_resident);
                push_modification(&undo_stack, 'A', new_resident);
                break;
            }
            case 2:
                print_residents(residents);
                break;
            case 3:
                search_resident(residents);
                break;
            case 4:
                modify_resident(residents);
                break;
            case 5:
                printf("Enter last name of the resident to delete: ");
                char last_name[MAX_NAME_LENGTH];
                scanf("%s", last_name);
                delete_resident(&residents);
                break;
            case 6: 
                printf("Enter the path to save the file: ");
                scanf("%s", filename);
                save_to_file(filename, residents);
                break;
            case 7: 
                undo_modifications(undo_stack, residents);
                break;
            case 8: 
                free_residents(residents);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (choice != 8);
    return 0;
}