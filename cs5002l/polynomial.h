#ifndef POLYNOMIAL_H

typedef struct Poly {
    double *coefficients;
    int degree;
    int capacity;
} Polynomial;

Polynomial *initPolynomial(int degree);
Polynomial *addPolynomials(Polynomial *p1, Polynomial *p2);
Polynomial *subtractPolynomials(Polynomial *p1, Polynomial *p2);
Polynomial *multiplyPolynomials(Polynomial *p1, Polynomial *p2);
void addTerm(Polynomial *p, double coefficient, int exponent);
void removeTerm(Polynomial *p, int exponent);
void printPolynomial(Polynomial *p);

#endif