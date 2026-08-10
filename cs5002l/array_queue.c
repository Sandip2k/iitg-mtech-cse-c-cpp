#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "array_queue.h"

Queue *init() {
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    if (!queue) {
        printf("Queue initialization failed.\n");
        return NULL;
    }

    queue->front = queue->rear = -1;
    DynamicArray *arr = createNew();
    if (!arr) {
        printf("Queue initialization failed.\n");
        free(queue);
        return NULL;
    }

    return queue;
}