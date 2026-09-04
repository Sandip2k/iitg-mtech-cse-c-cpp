#include "operations.h"

int minimum(int a, int b) {
    return (a <= b) ? a : b;
}

int maximum(int a, int b) {
    return (a >= b) ? a : b;
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}