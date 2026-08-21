#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "constants.h"
#include "array_queue.h"
#include "operations.h"

int resizeQueue(Queue *queue) {
    int size = queue->size;
    int capacity = queue->capacity;

    if (size == capacity) { // increase the size
        if (capacity == DEFAULT_MAX_CAPACITY) {
            printf("Reached maximum capacity.\n");
            return 1; // can't expand further, an error scenario.
        }
        DynamicArrayEntry *temp = (DynamicArrayEntry *) malloc(
            minimum(capacity * 2, DEFAULT_MAX_CAPACITY) * sizeof(DynamicArrayEntry)
        );
        if (temp) {
            queue->capacity = minimum(capacity * 2, DEFAULT_MAX_CAPACITY);
            int k = 0;
            if (queue->front <= queue->rear) {
                for (int i = queue->front; i <= queue->rear; ++i) {
                    temp[k].key = queue->entries[i].key;
                    temp[k].obj = queue->entries[i].obj;
                    k++;
                }
            } else {
                for (int i = queue->front; i < queue->size; ++i) {
                    temp[k].key = queue->entries[i].key;
                    temp[k].obj = queue->entries[i].obj;
                    k++;
                }
                for (int i = 0; i <= queue->rear; ++i) {
                    temp[k].key = queue->entries[i].key;
                    temp[k].obj = queue->entries[i].obj;
                    k++;
                }
            }
            queue->front = 0;
            queue->rear = k - 1;
            queue->entries = temp;
            printf("Resized from capacity = %d to capacity = %d.\n", capacity, queue->capacity);
            return 0;
        } else {
            printf("Failed to resize.\n");
            return 1;
        }
    } else if (size <= (capacity / 4)) { // decrease the size
        if (capacity == DEFAULT_MIN_CAPACITY) {
            printf("Already at minimum default capacity.\n");
            return 0; // can't contract further, but not an error scenario.
        }
        DynamicArrayEntry *temp = (DynamicArrayEntry *) malloc(
            maximum(capacity / 2, DEFAULT_MIN_CAPACITY) * sizeof(DynamicArrayEntry)
        );
        if (temp) {
            queue->capacity = maximum(capacity / 2, DEFAULT_MIN_CAPACITY);
                        int k = 0;
            if (queue->front <= queue->rear) {
                for (int i = queue->front; i <= queue->rear; ++i) {
                    temp[k].key = queue->entries[i].key;
                    temp[k].obj = queue->entries[i].obj;
                    k++;
                }
            } else {
                for (int i = queue->front; i < queue->size; ++i) {
                    temp[k].key = queue->entries[i].key;
                    temp[k].obj = queue->entries[i].obj;
                    k++;
                }
                for (int i = 0; i <= queue->rear; ++i) {
                    temp[k].key = queue->entries[i].key;
                    temp[k].obj = queue->entries[i].obj;
                    k++;
                }
            }
            queue->front = 0;
            queue->rear = k - 1;
            queue->entries = temp;
            printf("Resized from capacity = %d to capacity = %d.\n", capacity, queue->capacity);
            return 0;
        } else {
            printf("Failed to resize.\n");
            return 1;
        }
    } else {
        return 0; // no resizing needed
    }
}

Queue *init() {
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    if (!queue) {
        printf("Queue initialization failed.\n");
        return NULL;
    }

    queue->front = queue->rear = -1;
    queue->size = 0;
    queue->capacity = DEFAULT_MIN_CAPACITY;
    queue->entries = (DynamicArrayEntry *) malloc(queue->capacity * sizeof(DynamicArrayEntry));
    if (!queue->entries) {
        printf("Queue initialization failed.\n");
        free(queue);
        return NULL;
    }

    return queue;
}

int isFull(Queue *queue) {
    return queue->size == DEFAULT_MAX_CAPACITY;
}

int isEmpty(Queue *queue) {
    return !queue->size;
}

int enqueue(Queue *queue, Data *data) {
    if (isFull(queue)) {
        printf("Overflow.\n");
        return 1;
    }

    if (resizeQueue(queue)) {
        printf("Failed to resize.\n");
        return 1;
    }

    if (queue->rear == -1) { // empty queue.
        queue->front = queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % queue->capacity;
    }
    queue->entries[queue->rear].key = data->value;
    queue->entries[queue->rear].obj = data;
    queue->size++;
    return 0;
}

Data *dequeue(Queue *queue) {
    if (isEmpty(queue)) {
        printf("Underflow.\n");
        return NULL;
    }

    if (resizeQueue(queue)) {
        printf("Failed to resize.\n");
        return NULL;
    }

    Data *dequeued = queue->entries[queue->front].obj;
    if (queue->size == 1) { // Only one element.
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->capacity;
    }
    queue->size--;
    return dequeued;
}

Data *peek(Queue *queue) {
    if (isEmpty(queue)) {
        return NULL;
    }
    return queue->entries[queue->front].obj;
}

int main() {
    Queue *queue = init();
    for (int i = 1; i <= 8; ++i) {
        enqueue(queue, createNewData(i));
    }

    printf("Front: %d, Rear: %d\n", queue->front, queue->rear);

    Data *peekResult = peek(queue);
    printf("Peeked value: %d\n", peekResult ? peekResult->value : INT_MIN);

    for (int i = 1; i <= 5; ++i) {
        Data *dequeuedResult = dequeue(queue);
        printf("Dequeued value: %d\n", dequeuedResult ? dequeuedResult->value : INT_MIN);
    }

    printf("Front: %d, Rear: %d\n", queue->front, queue->rear);

    for (int i = 9; i <= 16; ++i) {
        enqueue(queue, createNewData(i));
    }

    printf("Front: %d, Rear: %d\n", queue->front, queue->rear);

    for (int i = 1; i <= 10; ++i) {
        Data *dequeuedResult = dequeue(queue);
        printf("Dequeued value: %d\n", dequeuedResult ? dequeuedResult->value : INT_MIN);
    }

    printf("Front: %d, Rear: %d\n", queue->front, queue->rear);

    printf("Queue size: %d\n", queue->size);

    return 0;
}