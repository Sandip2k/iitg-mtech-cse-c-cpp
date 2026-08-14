#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "dynamic_array.h"
#include "constants.h"

typedef struct Stack {
    int top;
    DynamicArray *stack;
} Stack;

Stack *init();
int push(Stack *s, Data *data);
Data *pop(Stack *s);
Data *peek(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);

#endif