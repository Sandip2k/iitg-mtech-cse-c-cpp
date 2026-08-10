#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "array_stack.h"

Stack *init() {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->top = -1;
    stack->stack = createNew();
    return stack;
}

int push(Stack *s, Data *data) {
    if (!s || !s->stack) {
        printf("Stack not initialized.\n");
        return 1;
    }

    int response = insertByKey(s->stack, data->value, data);
    if (!response) {
        // insert by key must be successful, for top to be incremented.
        s->top++;
    }
    return response;
}

int isEmpty(Stack *s) {
    if (!s || !s->stack) {
        printf("Stack not initialized.\n");
        return 1; // treat as empty.
    }
    return s->top == -1;
}

int isFull(Stack *s) {
    if (!s || !s->stack) {
        printf("Stack not initialized.\n");
        return 0; // treat as empty.
    }
    return s->stack->size == DEFAULT_MAX_CAPACITY;
}

Data *pop(Stack *s) {
    if (!s || !s->stack) {
        printf("Stack not initialized.\n");
        return NULL; // error scenario.
    }

    if (isEmpty(s)) {
        printf("Underflow.\n");
        return NULL;
    }

    Data *poppedData =  createNewData(s->stack->entries[s->top].key); // since the address is freed in the dynamic array delete logic, we must create a copy.
    int response = deleteFromPosition(s->stack, s->top);
    if (!response) {
        // delete from position must be successful, for top to be decremented.
        s->top--;
        return poppedData;
    } else {
        return NULL;
    }
    
}

Data *peek(Stack *s) {
    if (!s || !s->stack) {
        printf("Stack not initialized.\n");
        return NULL; // error scenario.
    }

    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return NULL;
    }

    return s->stack->entries[s->top].obj;
}

int main(void) {
    Stack *s = init();
    Data *peekResult = peek(s);
    if (peekResult) {
        printf("Peek: %d\n", peekResult->value);
    }
    pop(s);
    printf("Stack is empty: %s\n", (isEmpty(s) ? "YES" : "NO"));
    for (int i = 1; i <= 20; ++i) {
        push(s, createNewData(i));
    }
    peekResult = peek(s);
    if (peekResult) {
        printf("Peek Result: %d\n", peekResult->value);
    }
    Data *poppedResult;
    for (int i = 0; i < 25; ++i) {
        poppedResult = pop(s);
        if (poppedResult) {
            printf("Popped Result: %d\n", poppedResult->value);
        }
    }

    return 0;
}