#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include "dynamic_array.h"

typedef struct MinHeap {
    DynamicArray *heap;
} MinHeap;

MinHeap *heapify(DynamicArray *arr);
Data *minimumElement(MinHeap *heap);
Data *extractMin(MinHeap *heap);
int increaseKey(MinHeap *heap, int idx, int newKey);
int decreaseKey(MinHeap *heap, int idx, int newKey);
int insertElement(MinHeap *heap, int key, Data *obj);
int deleteElement(MinHeap *heap, int idx);
void heapSort(DynamicArray *arr);

#endif