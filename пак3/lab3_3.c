#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char firstName[50];
    char lastName[50];
    double salary;
} Employee;

int compareEmployees(const void *a, const void *b, void *arg) {
    Employee *empA = (Employee *)a;
    Employee *empB = (Employee *)b;
    int isAscending = *(int *)arg;

    if (empA->salary != empB->salary) {
        return isAscending ? (empA->salary > empB->salary ? 1 : -1) : (empA->salary < empB->salary ? 1 : -1);
    }
    int lastNameCmp = strcmp(empA->lastName, empB->lastName);
    if (lastNameCmp != 0) {
        return isAscending ? lastNameCmp : -lastNameCmp;
    }
    int firstNameCmp = strcmp(empA->firstName, empB->firstName);
    if (firstNameCmp != 0) {
        return isAscending ? firstNameCmp : -firstNameCmp;
    }
    return isAscending ? (empA->id - empB->id) : (empB->id - empA->id);
}

int readEmployeesFromFile(const char *filePath, Employee **employees) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror("ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    int count = 0, capacity = 10;
    *employees = malloc(capacity * sizeof(Employee));
    if (*employees == NULL) {
        perror("ошибка с паматью");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%d %49s %49s %lf", &(*employees)[count].id, (*employees)[count].firstName,
                  (*employees)[count].lastName, &(*employees)[count].salary) == 4) {
        count++;
        if (count >= capacity) {
            capacity *= 2;
            *employees = realloc(*employees, capacity * sizeof(Employee));
            if (*employees == NULL) {
                perror("ошибка с паматью");
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(file);
    return count;
}

void writeEmployeesToFile(const char *filePath, Employee *employees, int count) {
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        perror("ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %s %.2lf\n", employees[i].id, employees[i].firstName,
                employees[i].lastName, employees[i].salary);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprint("неверное кол-во аргументов");
        return 1;
    }
    char *inputFile = argv[1];
    char *flag = argv[2];
    char *outputFile = argv[3];
    int isAscending;
    if (strcmp(flag, "-a") == 0 || strcmp(flag, "/a") == 0) {
        isAscending = 1;
    }
    else if (strcmp(flag, "-d") == 0 || strcmp(flag, "/d") == 0) {
        isAscending = 0;
    }
    else {
        fprint("неправильный флаг.\n");
        return 1;
    }
    Employee *employees = NULL;
    int count = readEmployeesFromFile(inputFile, &employees);
    if (count < 0) {
        free(employees);
        return 1;
    }
    qsort_r(employees, count, sizeof(Employee), compareEmployees, &isAscending);
    writeEmployeesToFile(outputFile, employees, count);
    free(employees);
    return 0;
}