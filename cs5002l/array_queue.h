#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include "dynamic_array.h"
#include "constants.h"

// From the POV of efficient and consistent usage, an array queue has to be circular.
typedef struct Queue {
    int front, rear;
    DynamicArray *Queue;
} Queue;

Queue *init();
int enqueue(Queue *s, Data *data);
Data *dequeue(Queue *s, Data *data);
Data *peek(Queue *s);
int isEmpty(Queue *s);
int isFull(Queue *s);

#endif