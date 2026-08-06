#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "polynomial.h"

#define MAX_INITIAL_CAPACITY 5

Polynomial *initPolynomial(int degree) {
    Polynomial *p = (Polynomial *) malloc(sizeof(Polynomial));
    p->degree = degree + 1;
    p->capacity = MAX_INITIAL_CAPACITY;
    p->coefficients = (double *) calloc(p->degree, sizeof(double));
    return p;
}

void resize(Polynomial *p) {
    if (p->degree == p->capacity) {
        double *temp = (double *) realloc(p->coefficients, p->capacity * 2 * sizeof(double));
        if (temp) {
            p->capacity *= 2;
            p->coefficients = temp;
        }
    } else if (p->degree <= (p->capacity / 4)) {
        double *temp = (double *) realloc(p->coefficients, (p->capacity / 2) * sizeof(double));
        if (temp) {
            p->capacity /= 2;
            p->coefficients = temp;
        }
    }
}

void addTerm(Polynomial *p, double coefficient, int power) {
    if (power > p->capacity) {
        while (p->capacity <= power) {
            double *temp = (double *) realloc(p->coefficients, p->capacity * 2 * sizeof(double));
            if (temp) {
                p->capacity *= 2;
                p->coefficients = temp;
            }
        }
    }
    if (power > p->degree) {
        p->degree = power;
    }
    p->coefficients[power] = coefficient;
}

void printPolynomial(Polynomial *p) {
    for (int i = 0; i <= p->degree; ++i) {
        if (fabs(p->coefficients[i] - 0) <= pow(10, -6)) continue;

        if (i == 0) {
            printf("%.2lf", p->coefficients[i]);
        } else {
            printf("%.2lf.x^{%d}", p->coefficients[i], i);
        }

        if (i != p->degree) {
            printf(" + ");
        }
    }
    printf("\n");
}

int main() {
    Polynomial *p = initPolynomial(4);
    addTerm(p, 2.5, 0);
    addTerm(p, 2.5, 1);
    addTerm(p, 2.5, 2);
    addTerm(p, 2.5, 3);
    addTerm(p, 2.5, 4);
    addTerm(p, 2.5, 5);
    // addTerm(p, 2.5, 9);
    // addTerm(p, 2.5, 15);
    // addTerm(p, 2.5, 47);
    printPolynomial(p);
    printf("%d, %d\n", p->degree, p->capacity);
}
