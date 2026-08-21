#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 10

void enqueue(int *queue, int *size, int data, int *front, int *rear) {
    if (*size == MAX_CAPACITY) {
        printf("Overflow.\n");
        return;
    }

    if (*rear == -1) { // empty queue.
        *front = *rear = 0;
    } else {
        *rear = (*rear + 1) % MAX_CAPACITY;
    }
    queue[*rear] = data;
    (*size)++;
}

int dequeue(int *queue, int *size, int *front, int *rear) {
    if (!(*size)) {
        printf("Underflow.\n");
        return INT_MIN;
    }

    int dequeued = queue[*front];
    if (*size == 1) { // single element to be removed.
        *front = *rear = -1;
    } else {
        *front = (*front + 1) % MAX_CAPACITY;
    }
    (*size)--;
    return dequeued;
}

int peek(int *queue, int size, int front, int rear) {
    if (!size) {
        return INT_MIN;
    }
    return queue[front];
}

int main() {
    int queue[MAX_CAPACITY];
    int size = 0;
    int front = -1, rear = -1; // initial values of front and rear.
    enqueue(queue, &size, 1, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);
    enqueue(queue, &size, 2, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);
    enqueue(queue, &size, 3, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);
    enqueue(queue, &size, 4, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);
    enqueue(queue, &size, 5, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);
    enqueue(queue, &size, 6, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);

    int dequeued = dequeue(queue, &size, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);
    printf("Dequeued element = %d\n", dequeued);
    dequeued = dequeue(queue, &size, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);
    printf("Dequeued element = %d\n", dequeued);
    dequeued = dequeue(queue, &size, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);
    printf("Dequeued element = %d\n", dequeued);
    dequeued = dequeue(queue, &size, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);
    printf("Dequeued element = %d\n", dequeued);

    enqueue(queue, &size, 6, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);
    enqueue(queue, &size, 7, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);
    enqueue(queue, &size, 8, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);
    enqueue(queue, &size, 9, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);
    enqueue(queue, &size, 10, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);
    enqueue(queue, &size, 11, &front, &rear);
    printf("Front: %d, Rear: %d\n", front, rear);

    int peekVal = peek(queue, size, front, rear);
    printf("Peeked element = %d\n", peekVal);
    return 0;
}