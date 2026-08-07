#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "polynomial.h"

#define MAX_INITIAL_CAPACITY 5

// Assume only positive, real exponents.

// TODO: Null pointer handling for all functions.

int maximum(int a, int b) {
    return (a >= b) ? a : b;
}

Polynomial *initPolynomial() {
    Polynomial *polynomial = (Polynomial *) malloc(sizeof(Polynomial));
    polynomial->degree = -1;
    polynomial->capacity = MAX_INITIAL_CAPACITY;
    polynomial->coefficients = (double *) malloc(polynomial->capacity * sizeof(double));
    memset(polynomial->coefficients, 0, polynomial->capacity * sizeof(double));
    return polynomial;
}

void deletePolynomial(Polynomial *polynomial) {
    if (polynomial) {
        free(polynomial->coefficients);
        free(polynomial);
    }
}

void resize(Polynomial *polynomial) {
    if (polynomial->degree == polynomial->capacity) {
        double *temp = (double *) realloc(polynomial->coefficients, polynomial->capacity * 2 * sizeof(double));
        if (temp) {
            memset(temp + polynomial->capacity, 0, polynomial->capacity * sizeof(double));
            // printf("Resized from %d to %d.\n", p->capacity, p->capacity * 2);
            polynomial->capacity *= 2;
            polynomial->coefficients = temp;
            
            
        }
    } else if (polynomial->degree <= (polynomial->capacity / 4)) {
        double *temp = (double *) realloc(polynomial->coefficients, (polynomial->capacity / 2) * sizeof(double));
        if (temp) {
            // printf("Resized from %d to %d.\n", p->capacity, p->capacity / 2);
            polynomial->capacity /= 2;
            polynomial->coefficients = temp;
        }
    }
}

void addTerm(Polynomial *polynomial, double coefficient, int exponent) {
    if (exponent < 0) {
        printf("Negative exponents aren't allowed.\n");
        return;
    }

    if (exponent > polynomial->degree) {
        polynomial->degree = exponent;
        printf("Highest degree now: %d.\n", polynomial->degree);
    }

    while (polynomial->capacity <= polynomial->degree) {
        double *temp = (double *) realloc(polynomial->coefficients, (polynomial->capacity * 2) * sizeof(double));
        if (temp) {
            memset(temp + polynomial->capacity, 0, polynomial->capacity * sizeof(double));
            // printf("Resized from %d to %d.\n", p->capacity, p->capacity * 2);
            polynomial->capacity *= 2;
            polynomial->coefficients = temp;
        }
    }

    polynomial->coefficients[exponent] += coefficient;
    resize(polynomial);
}

void removeTerm(Polynomial *polynomial, int exponent) {
    if (exponent < 0 || exponent > polynomial->degree || !polynomial->coefficients[exponent]) {
        printf("Invalid exponent value: %d.\n", exponent);
        return;
    }

    if (exponent == polynomial->degree) {
        int i = exponent - 1;
        while (i >= 0) {
            if (fabs(polynomial->coefficients[i] - 0) > pow(10, -6)) {
                break;
            }
            --i;
        }
        polynomial->degree = i;
    }

    polynomial->coefficients[exponent] = 0.0;
    resize(polynomial);
}

Polynomial *addPolynomials(Polynomial *p1, Polynomial *p2) {
    Polynomial *result = (Polynomial *) malloc(sizeof(Polynomial));
    result->degree = (int) maximum(p1->degree, p2->degree);
    result->capacity = result->degree + 1;
    result->coefficients = (double *) malloc(result->capacity * sizeof(double));
    memset(result->coefficients, 0, result->capacity * sizeof(double));

    for (int i = 0; i <= result->degree; ++i) {
        if (i <= p1->degree && fabs(p1->coefficients[i] - 0) > pow(10, -6)) result->coefficients[i] += p1->coefficients[i];
        if (i <= p2->degree && fabs(p2->coefficients[i] - 0) > pow(10, -6)) result->coefficients[i] += p2->coefficients[i];
    }
    return result;
}

Polynomial *subtractPolynomials(Polynomial *p1, Polynomial *p2) {
    Polynomial *result = (Polynomial *) malloc(sizeof(Polynomial));
    result->degree = (int) maximum(p1->degree, p2->degree);
    result->capacity = result->degree + 1;
    result->coefficients = (double *) malloc(result->capacity * sizeof(double));
    memset(result->coefficients, 0, result->capacity * sizeof(double));

    for (int i = 0; i <= result->degree; ++i) {
        if (i <= p1->degree && fabs(p1->coefficients[i] - 0) > pow(10, -6)) result->coefficients[i] += p1->coefficients[i];
        if (i <= p2->degree && fabs(p2->coefficients[i] - 0) > pow(10, -6)) result->coefficients[i] -= p2->coefficients[i];
    }
    return result;
}

Polynomial *multiplyPolynomials(Polynomial *p1, Polynomial *p2) {
    Polynomial *result = (Polynomial *) malloc(sizeof(Polynomial));
    result->degree = maximum((p1->degree + p2->degree), -1);
    result->capacity = result->degree + 1;
    result->coefficients = (double *) malloc(result->capacity * sizeof(double));
    memset(result->coefficients, 0, result->capacity * sizeof(double));

    if (!result->coefficients) {
        free(result);
        return NULL;
    }

    for (int i = 0; i <= p1->degree; ++i) {
        for (int j = 0; j <= p2->degree; ++j) {
            if (
                i <= p1->degree && fabs(p1->coefficients[i] - 0) > pow(10, -6) &&
                j <= p2->degree && fabs(p2->coefficients[j] - 0) > pow(10, -6)
            ) {
                result->coefficients[i + j] += (p1->coefficients[i] * p2->coefficients[j]);
            }
        }
    }

    return result;
}

void printPolynomial(Polynomial *p) {
    for (int i = 0; i <= p->degree; ++i) {
        if (fabs(p->coefficients[i] - 0) <= pow(10, -6)) continue;

        if (i == 0) {
            printf("%.2lf", p->coefficients[i]);
        } else {
            printf("%.2lf.x^%d", p->coefficients[i], i);
        }

        if (i != p->degree) {
            printf(" + ");
        }
    }
    printf("\n");
}

int main() {
    Polynomial *p = initPolynomial();
    addTerm(p, 3, 2);
    addTerm(p, -2, 0);
    addTerm(p, 1, 1);
    printPolynomial(p);

    Polynomial *p1 = initPolynomial();
    addTerm(p1, 4, 5);
    addTerm(p1, -1, 2);
    addTerm(p1, -3, 0);
    addTerm(p1, 6, 1);
    printPolynomial(p1);

    Polynomial *result = addPolynomials(p, p1);
    printPolynomial(result);

    Polynomial *result1 = subtractPolynomials(p1, p);
    printPolynomial(result1);

    Polynomial *result2 = multiplyPolynomials(p, p1);
    printPolynomial(result2);
}
