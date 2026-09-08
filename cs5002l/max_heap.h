#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include "dynamic_array.h"

typedef struct MaxHeap {
    DynamicArray *heap;
} MaxHeap;

MaxHeap *heapify(DynamicArray *arr);
Data *maximumElement(MaxHeap *heap);
Data *extractMax(MaxHeap *heap);
int increaseKey(MaxHeap* heap, int idx, int newKey);
int decreaseKey(MaxHeap* heap, int idx, int newKey);
int insertElement(MaxHeap *heap, int key, Data *obj);
int deleteElement(MaxHeap *heap, int idx);
void heapSort(DynamicArray *arr);

#endif