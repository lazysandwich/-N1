#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Term {
    int coefficient;
    int exponent;
    struct Term* next;
} Term;

typedef struct Polynomial {
    Term* head;
} Polynomial;

Polynomial* create_polynomial() {
    Polynomial* poly = (Polynomial*)malloc(sizeof(Polynomial));
    poly->head = NULL;
    return poly;
}

void free_polynomial(Polynomial* poly) {
    Term* current = poly->head;
    while (current) {
        Term* temp = current;
        current = current->next;
        free(temp);
    }
    free(poly);
}

void add_term(Polynomial* poly, int coefficient, int exponent) {
    if (coefficient == 0) return;
    Term* new_term = (Term*)malloc(sizeof(Term));
    new_term->coefficient = coefficient;
    new_term->exponent = exponent;
    new_term->next = NULL;
    if (!poly->head || poly->head->exponent < exponent) {
        new_term->next = poly->head;
        poly->head = new_term;
    } 
    else {
        Term* current = poly->head;
        Term* prev = NULL;
        while (current && current->exponent >= exponent) {
            if (current->exponent == exponent) {
                current->coefficient += coefficient;
                free(new_term);
                if (current->coefficient == 0) {
                    if (prev) {
                        prev->next = current->next;
                    } 
                    else {
                        poly->head = current->next;
                    }
                    free(current);
                }
                return;
            }
            prev = current;
            current = current->next;
        }
        new_term->next = current;
        prev->next = new_term;
    }
}

void print_polynomial(Polynomial* poly) {
    if (!poly->head) {
        printf("0\n");
        return;
    }

    Term* current = poly->head;
    while (current) {
        if (current->coefficient > 0 && current != poly->head) {
            printf("+");
        }
        printf("%dx^%d ", current->coefficient, current->exponent);
        current = current->next;
    }
    printf("\n");
}

Polynomial* add_polynomials(Polynomial* a, Polynomial* b) {
    Polynomial* result = create_polynomial();
    Term* current = a->head;
    while (current) {
        add_term(result, current->coefficient, current->exponent);
        current = current->next;
    }
    current = b->head;
    while (current) {
        add_term(result, current->coefficient, current->exponent);
        current = current->next;
    }
    return result;
}

Polynomial* subtract_polynomials(Polynomial* a, Polynomial* b) {
    Polynomial* result = create_polynomial();
    Term* current = a->head;
    while (current) {
        add_term(result, current->coefficient, current->exponent);
        current = current->next;
    }
    current = b->head;
    while (current) {
        add_term(result, -current->coefficient, current->exponent);
        current = current->next;
    }
    return result;
}

Polynomial* multiply_polynomials(Polynomial* a, Polynomial* b) {
    Polynomial* result = create_polynomial();
    Term* current_a = a->head;
    while (current_a) {
        Term* current_b = b->head;
        while (current_b) {
            int coeff = current_a->coefficient * current_b->coefficient;
            int exp = current_a->exponent + current_b->exponent;
            add_term(result, coeff, exp);
            current_b = current_b->next;
        }
        current_a = current_a->next;
    }
    return result;
}

Polynomial* divide_polynomials(Polynomial* dividend, Polynomial* divisor) {
    if (!divisor->head || (divisor->head->coefficient == 0)) {
        printf("не дели на ноль.\n");
        exit(EXIT_FAILURE);
    }
    Polynomial* result = create_polynomial();
    Polynomial* remainder = create_polynomial();
    Term* current = dividend->head;
    while (current) {
        add_term(remainder, current->coefficient, current->exponent);
        current = current->next;
    }
    while (remainder->head && remainder->head->exponent >= divisor->head->exponent) {
        int coeff = remainder->head->coefficient / divisor->head->coefficient;
        int exp = remainder->head->exponent - divisor->head->exponent;
        add_term(result, coeff, exp);
        Polynomial* temp = create_polynomial();
        add_term(temp, coeff, exp);
        Polynomial* product = multiply_polynomials(temp, divisor);
        remainder = subtract_polynomials(remainder, product);
        free_polynomial(temp);
        free_polynomial(product);
    }
    free_polynomial(remainder);
    return result;
}

Polynomial* remainder_polynomials(Polynomial* dividend, Polynomial* divisor) {
    if (!divisor->head || (divisor->head->coefficient == 0)) {
        printf("не дели на ноль.\n");
        exit(EXIT_FAILURE);
    }
    Polynomial* remainder = create_polynomial();
    Term* current = dividend->head;
    while (current) {
        add_term(remainder, current->coefficient, current->exponent);
        current = current->next;
    }
    while (remainder->head && remainder->head->exponent >= divisor->head->exponent) {
        int coeff = remainder->head->coefficient / divisor->head->coefficient;
        int exp = remainder->head->exponent - divisor->head->exponent;
        Polynomial* temp = create_polynomial();
        add_term(temp, coeff, exp);
        Polynomial* product = multiply_polynomials(temp, divisor);
        remainder = subtract_polynomials(remainder, product);
        free_polynomial(temp);
        free_polynomial(product);
    }
    return remainder;
}

int evaluate_polynomial(Polynomial* poly, int x) {
    int result = 0;
    Term* current = poly->head;
    while (current) {
        result += current->coefficient * (int)pow(x, current->exponent);
        current = current->next;
    }
    return result;
}

Polynomial* differentiate_polynomial(Polynomial* poly) {
    Polynomial* result = create_polynomial();
    Term* current = poly->head;
    while (current) {
        if (current->exponent > 0) {
            add_term(result, current->coefficient * current->exponent, current->exponent - 1);
        }
        current = current->next;
    }
    return result;
}

Polynomial* compose_polynomials(Polynomial* outer, Polynomial* inner) {
    Polynomial* result = create_polynomial();
    Term* current = outer->head;
    while (current) {
        Polynomial* temp = create_polynomial();
        add_term(temp, current->coefficient, current->exponent);
        Polynomial* composed = multiply_polynomials(temp, inner);
        result = add_polynomials(result, composed);
        free_polynomial(temp);
        free_polynomial(composed);
        current = current->next;
    }
    return result;
}

void parse_polynomial(const char* str, Polynomial* poly) {
    char* token = strtok((char*)str, "+-");
    int sign = 1;
    while (token) {
        int coeff = 1;
        int exp = 0;
        if (strchr(token, 'x')) {
            char* x_pos = strchr(token, 'x');
            if (x_pos != token) {
                coeff = atoi(token);
            }
            if (*(x_pos + 1) == '^') {
                exp = atoi(x_pos + 2);
            } else {
                exp = 1;
            }
        } 
        else {
            coeff = atoi(token);
        }
        add_term(poly, sign * coeff, exp);
        if (strchr(token, '-')) {
            sign = -1;
        } 
        else {
            sign = 1;
        }
        token = strtok(NULL, "+-");
    }
}

void process_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("файл не открыл");
        exit(EXIT_FAILURE);
    }
    char line[256];
    Polynomial* adder = create_polynomial();
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '%') {
            continue;
        }
        if (line[0] == '[') {
            continue;
        }
        char command[10];
        sscanf(line, "%s", command);
        if (strncmp(command, "Add", 3) == 0) {
            char args[100];
            sscanf(line + strlen(command), "(%[^)])", args);
            Polynomial* temp_poly = create_polynomial();
            parse_polynomial(args, temp_poly);
            adder = add_polynomials(adder, temp_poly);
            print_polynomial(adder);
            free_polynomial(temp_poly);
        }
        else if (strncmp(command, "Sub", 3) == 0) {
        }
        else if (strncmp(command, "Mult", 4) == 0) {
        }
        else if (strncmp(command, "Div", 3) == 0) {
        }
        else if (strncmp(command, "Eval", 4) == 0) {
        }
        else if (strncmp(command, "Diff", 4) == 0) {
        }
        else if (strncmp(command, "Cmps", 4) == 0) {
        }
    }
    fclose(file);
    free_polynomial(adder);
}

int main() {
    process_file("polynomials.txt");
    return 0;
}