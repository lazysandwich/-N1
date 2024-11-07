
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>

typedef struct {
    double *coordinates;
    int dimension;
} Vector;

double norm_1(Vector *v) {
    double sum = 0.0;
    for (int i = 0; i < v->dimension; i++) {
        sum += fabs(v->coordinates[i]);
    }
    return sum;
}

double norm_2(Vector *v) {
    double sum = 0.0;
    for (int i = 0; i < v->dimension; i++) {
        sum += v->coordinates[i] * v->coordinates[i];
    }
    return sqrt(sum);
}

void find_longest_vectors(int n, Vector *first_vector, ...) {
    va_list args;
    va_start(args, first_vector);
    double (*norms[])(Vector *) = {norm_1, norm_2};
    size_t norms_count = sizeof(norms) / sizeof(norms[0]);
    double max_norms[norms_count];
    memset(max_norms, 0, sizeof(max_norms));
    Vector *vectors[100];
    size_t vectors_count = 0;
    Vector *current_vector = first_vector;
    while (current_vector != NULL) {
        vectors[vectors_count++] = current_vector;
        current_vector = va_arg(args, Vector *);
    }
    va_end(args);
    for (size_t i = 0; i < vectors_count; i++) {
        for (size_t j = 0; j < norms_count; j++) {
            double current_norm = norms[j](vectors[i]);
            if (current_norm > max_norms[j]) {
                max_norms[j] = current_norm;
            }
        }
    }
    for (size_t j = 0; j < norms_count; j++) {
        printf("самый дляинный вектор %zu: ", j);
        for (size_t i = 0; i < vectors_count; i++) {
            if (norms[j](vectors[i]) == max_norms[j]) {
                printf("(");
                for (int k = 0; k < vectors[i]->dimension; k++) {
                    printf("%lf", vectors[i]->coordinates[k]);
                    if (k < vectors[i]->dimension - 1) {
                        printf(", ");
                    }
                }
                printf(")");
            }
        }
        printf("\n");
    }
}

int main() {
    double coords1[] = {1, 2};
    double coords2[] = {3, 4};
    double coords3[] = {3, -1};
    Vector v1 = {coords1, 2};
    Vector v2 = {coords2, 2};
    Vector v3 = {coords3, 2};
    find_longest_vectors(2, &v1, &v2, &v3, NULL);
    return 0;
}
