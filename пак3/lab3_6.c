#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 256

typedef struct Stop {
    char vehicle_number[MAX_LINE_LENGTH];
    char stop_time[MAX_LINE_LENGTH];
    char departure_time[MAX_LINE_LENGTH];
    char type[MAX_LINE_LENGTH];
    struct Stop* next;
} Stop;

typedef struct Route {
    Stop* stops;
    struct Route* next;
} Route;

typedef struct Vehicle {
    char vehicle_number[MAX_LINE_LENGTH];
    Route* routes;
    struct Vehicle* next;
} Vehicle;

void add_stop(Route* route, const char* vehicle_number, const char* stop_time, const char* departure_time, const char* type) {
    Stop* new_stop = (Stop*)malloc(sizeof(Stop));
    strcpy(new_stop->vehicle_number, vehicle_number);
    strcpy(new_stop->stop_time, stop_time);
    strcpy(new_stop->departure_time, departure_time);
    strcpy(new_stop->type, type);
    new_stop->next = NULL;
    Stop* current = route->stops;
    Stop* previous = NULL;
    while (current != NULL && strcmp(current->stop_time, stop_time) < 0) {
        previous = current;
        current = current->next;
    }
    if (previous == NULL) {
        new_stop->next = route->stops;
        route->stops = new_stop;
    } else {
        new_stop->next = current;
        previous->next = new_stop;
    }
}

void add_route(Vehicle* vehicle, Route* route) {
    route->next = vehicle->routes;
    vehicle->routes = route;
}

void free_memory(Vehicle* vehicles) {
    while (vehicles) {
        Vehicle* temp_vehicle = vehicles;
        vehicles = vehicles->next;
        Route* route = temp_vehicle->routes;
        while (route) {
            Route* temp_route = route;
            route = route->next;
            Stop* stop = temp_route->stops;
            while (stop) {
                Stop* temp_stop = stop;
                stop = stop->next;
                free(temp_stop);
            }
            free(temp_route);
        }
        free(temp_vehicle);
    }
}

void print_routes(Vehicle* vehicles) {
    Vehicle* current_vehicle = vehicles;
    while (current_vehicle) {
        printf("номер мафынок: %s\n", current_vehicle->vehicle_number);
        Route* current_route = current_vehicle->routes;
        while (current_route) {
            Stop* current_stop = current_route->stops;
            while (current_stop) {
                printf("  остановка: %s, отправка: %s, тип: %s\n", current_stop->stop_time, current_stop->departure_time, current_stop->type);
                current_stop = current_stop->next;
            }
            current_route = current_route->next;
        }
        current_vehicle = current_vehicle->next;
    }
}

void process_file(const char* file_path, Vehicle** vehicles) {
    FILE* file = fopen(file_path, "r");
    if (!file) {
        perror("файл не открыл");
        exit(EXIT_FAILURE);
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char vehicle_number[MAX_LINE_LENGTH], stop_time[MAX_LINE_LENGTH], departure_time[MAX_LINE_LENGTH], type[MAX_LINE_LENGTH];
        sscanf(line, "%s %s %s %s", vehicle_number, stop_time, departure_time, type);
        Vehicle* vehicle = *vehicles;
        while (vehicle) {
            if (strcmp(vehicle->vehicle_number, vehicle_number) == 0) {
                break;
            }
            vehicle = vehicle->next;
        }
        if (!vehicle) {
            vehicle = (Vehicle*)malloc(sizeof(Vehicle));
            strcpy(vehicle->vehicle_number, vehicle_number);
            vehicle->routes = NULL;
            vehicle->next = *vehicles;
            *vehicles = vehicle;
        }
        Route* route = (Route*)malloc(sizeof(Route));
        route->stops = NULL;
        route->next = NULL;
        add_stop(route, vehicle_number, stop_time, departure_time, type);
        add_route(vehicle, route);
    }
    fclose(file);
}

void search_vehicles(Vehicle* vehicles) {
    int choice;
    do {
        printf("1. найти машину по наиб маршруту\n");
        printf("2. найти машину по наим маршруту\n");
        printf("3. найти машину по наиб остановке\n");
        printf("4. найти машину по наиб безделию\n");
        printf("5. выход\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                search_by_route_length(vehicles, 1);
                break;
            case 2:
                search_by_route_length(vehicles, 0);
                break;
            case 5:
                break;
            default:
                printf(" ВЫ ******. нет такого выбора.\n");
        }
    } while (choice != 5);
}

double calculate_route_length(Route* route) {
    return 0.0; 
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprint("Неверное кол-во аргументов\n");
        return EXIT_FAILURE;
    }
    Vehicle* vehicles = NULL;
    for (int i = 1; i < argc; i++) {
        process_file(argv[i], &vehicles);
    }
    print_routes(vehicles);
    search_vehicles(vehicles);
    free_memory(vehicles);
    return EXIT_SUCCESS;
}