#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "polynomial.h"

#define DEFAULT_MIN_CAPACITY 10
#define DEFAULT_MAX_CAPACITY 1000

// Assume only positive, real exponents.

int maximum(int a, int b) {
    return (a >= b) ? a : b;
}

int minimum(int a, int b) {
    return (a <= b) ? a : b;
}

Polynomial *initPolynomial() {
    Polynomial *polynomial = (Polynomial *) malloc(sizeof(Polynomial));
    if (!polynomial) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    polynomial->degree = -1;
    polynomial->capacity = DEFAULT_MIN_CAPACITY;
    polynomial->coefficients = (double *) malloc(polynomial->capacity * sizeof(double));
    if (!polynomial->coefficients) {
        printf("Memory allocation failed.\n");
        free(polynomial);
        return NULL;
    }
    memset(polynomial->coefficients, 0, polynomial->capacity * sizeof(double));
    return polynomial;
}

void deletePolynomial(Polynomial *polynomial) {
    if (polynomial) {
        free(polynomial->coefficients);
        free(polynomial);
    }
}

int resize(Polynomial *polynomial) {
    if (!polynomial) return 1;
    if (polynomial->degree == polynomial->capacity) {
        if (polynomial->capacity == DEFAULT_MAX_CAPACITY) {
            printf("Reached the maximum capacity.\n");
            return 1;
        }
        double *temp = (double *) realloc(
            polynomial->coefficients, minimum(polynomial->capacity * 2, DEFAULT_MAX_CAPACITY) * sizeof(double)
        );
        if (temp) {
            memset(temp + polynomial->capacity, 0, polynomial->capacity * sizeof(double));
            // printf("Resized from %d to %d.\n", p->capacity, p->capacity * 2);
            polynomial->capacity = minimum(polynomial->capacity * 2, DEFAULT_MAX_CAPACITY);
            polynomial->coefficients = temp;
            return 0;
        } else {
            printf("Failed to resize.\n");
            return 1;
        }
    } else if (polynomial->degree <= (polynomial->capacity / 4)) {
        if (polynomial->capacity == DEFAULT_MIN_CAPACITY) {
            printf("Already at the minimum capacity.\n");
            return 0;
        }
        double *temp = (double *) realloc(
            polynomial->coefficients, maximum(polynomial->capacity / 2, DEFAULT_MIN_CAPACITY) * sizeof(double)
        );
        if (temp) {
            // printf("Resized from %d to %d.\n", p->capacity, p->capacity / 2);
            polynomial->capacity = maximum(polynomial->capacity / 2, DEFAULT_MIN_CAPACITY);
            polynomial->coefficients = temp;
            return 0;
        } else {
            printf("Failed to resize.\n");
            return 1;
        }
    }
}

void addTerm(Polynomial *polynomial, double coefficient, int exponent) {
    if (!polynomial || !polynomial->coefficients) {
        printf("Invalid polynomial.\n");
        return;
    }

    if (exponent < 0) {
        printf("Negative exponents aren't allowed.\n");
        return;
    }

    while (polynomial->capacity <= exponent) {
        if (polynomial->capacity == DEFAULT_MAX_CAPACITY) {
            printf("Reached the maximum capacity.\n");
            return;
        }
        double *temp = (double *) realloc(
            polynomial->coefficients, minimum(polynomial->capacity * 2, DEFAULT_MAX_CAPACITY) * sizeof(double)
        );
        if (temp) {
            memset(temp + polynomial->capacity, 0, polynomial->capacity * sizeof(double));
            // printf("Resized from %d to %d.\n", p->capacity, p->capacity * 2);
            polynomial->capacity = minimum(polynomial->capacity * 2, DEFAULT_MAX_CAPACITY);
            polynomial->coefficients = temp;
        } else {
            printf("Failed to resize.\n");
            return;
        }
    }

        if (exponent > polynomial->degree) {
            polynomial->degree = exponent;
            printf("Highest degree now: %d.\n", polynomial->degree);
        }

    polynomial->coefficients[exponent] += coefficient;
    resize(polynomial);
}

void removeTerm(Polynomial *polynomial, int exponent) {
    if (!polynomial || !polynomial->coefficients) {
        printf("Invalid polynomial.\n");
        return;
    }

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
    if (!p1 || !p2 || !p1->coefficients || !p2->coefficients) {
        printf("Invalid polynomial(s).\n");
        return NULL;
    }

    Polynomial *result = (Polynomial *) malloc(sizeof(Polynomial));
    if (!result) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    result->degree = (int) maximum(p1->degree, p2->degree);
    result->capacity = result->degree + 1;
    result->coefficients = (double *) malloc(result->capacity * sizeof(double));
    if (!result->coefficients) {
        printf("Memory allocation failed.\n");
        free(result);
        return NULL;
    }

    memset(result->coefficients, 0, result->capacity * sizeof(double));

    for (int i = 0; i <= result->degree; ++i) {
        if (i <= p1->degree && fabs(p1->coefficients[i] - 0) > pow(10, -6)) result->coefficients[i] += p1->coefficients[i];
        if (i <= p2->degree && fabs(p2->coefficients[i] - 0) > pow(10, -6)) result->coefficients[i] += p2->coefficients[i];
    }
    return result;
}

Polynomial *subtractPolynomials(Polynomial *p1, Polynomial *p2) {
    if (!p1 || !p2 || !p1->coefficients || !p2->coefficients) {
        printf("Invalid polynomial(s).\n");
        return NULL;
    }

    Polynomial *result = (Polynomial *) malloc(sizeof(Polynomial));
    if (!result) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    result->degree = (int) maximum(p1->degree, p2->degree);
    result->capacity = result->degree + 1;
    result->coefficients = (double *) malloc(result->capacity * sizeof(double));
    if (!result->coefficients) {
        printf("Memory allocation failed.\n");
        free(result);
        return NULL;
    }

    memset(result->coefficients, 0, result->capacity * sizeof(double));

    for (int i = 0; i <= result->degree; ++i) {
        if (i <= p1->degree && fabs(p1->coefficients[i] - 0) > pow(10, -6)) result->coefficients[i] += p1->coefficients[i];
        if (i <= p2->degree && fabs(p2->coefficients[i] - 0) > pow(10, -6)) result->coefficients[i] -= p2->coefficients[i];
    }
    return result;
}

Polynomial *multiplyPolynomials(Polynomial *p1, Polynomial *p2) {
    if (!p1 || !p2 || !p1->coefficients || !p2->coefficients) {
        printf("Invalid polynomial(s).\n");
        return NULL;
    }

    Polynomial *result = (Polynomial *) malloc(sizeof(Polynomial));
    if (!result) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    result->degree = maximum((p1->degree + p2->degree), -1);
    result->capacity = result->degree + 1;
    result->coefficients = (double *) malloc(result->capacity * sizeof(double));
    if (!result->coefficients) {
        printf("Memory allocation failed.\n");
        free(result);
        return NULL;
    }

    memset(result->coefficients, 0, result->capacity * sizeof(double));

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
    if (!p|| !p->coefficients) {
        return;
    }

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
