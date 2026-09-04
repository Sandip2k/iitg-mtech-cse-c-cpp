#include <stdio.h>
#include <stdlib.h>
#include "max_heap.h"
#include "operations.h"

int heapify(MaxHeap *heap, int idx) {
    if (!heap || !heap->heap) {
        printf("Invalid heap configuration.\n");
        return 1;
    }

    if (!heap->heap->size) {
        printf("Heap is empty.\n");
        return 1;
    }

    int leftChildIdx = 2 * idx;
    int rightChildIdx = 2 * idx + 1;

    int max = heap->heap->entries[idx].key, argMax = idx;
    int leftChild = (leftChildIdx < heap->heap->size) ? heap->heap->entries[leftChildIdx].key : INT_MIN;
    int rightChild = (rightChildIdx < heap->heap->size) ? heap->heap->entries[rightChildIdx].key : INT_MIN;
    
    if (max < leftChild) {
        max = leftChild;
        argMax = leftChildIdx;
    }

    if (max < rightChild) {
        max = rightChild;
        argMax = rightChildIdx;
    }

    if (argMax != idx) {
        int tempKey = heap->heap->entries[idx].key;
        heap->heap->entries[idx].key = heap->heap->entries[argMax].key;
        heap->heap->entries[argMax].key = tempKey;

        Data* tempObj = heap->heap->entries[idx].obj;
        heap->heap->entries[idx].obj = heap->heap->entries[argMax].obj;
        heap->heap->entries[argMax].obj = tempObj;
    } else {
        return 0;
    }

    return heapify(heap, argMax);
}

MaxHeap *init(DynamicArray *arr) {
    MaxHeap *result = (MaxHeap *) malloc(sizeof(MaxHeap));
    result->heap = createNew();
    insertByKey(result->heap, INT_MIN, NULL); // ? dummy at 0th position for easier calculation.
    for (int i = 0; i < arr->size; ++i) {
        if(insertByKey(result->heap, arr->entries[i].key, arr->entries[i].obj)) {
            printf("Heap initialization failed for i = %d.\n", i);
            free(result->heap->entries);
            free(result->heap);
            free(result);
            return NULL;
        }
    }

    for(int i = result->heap->size / 2; i >= 1; --i) {
        heapify(result, i);
    }

    return result;
}

Data *maximumElement(MaxHeap *heap) {
    if (!heap || !heap->heap) {
        printf("Invalid heap configuration.\n");
        return NULL;
    }

    if (!heap->heap->size) {
        printf("Heap is empty.\n");
        return NULL;
    }

    return heap->heap->entries[1].obj;
}

Data *extractMax(MaxHeap *heap) {
    if (!heap || !heap->heap) {
        printf("Invalid heap configuration.\n");
        return NULL;
    }

    if (!heap->heap->size) {
        printf("Heap is empty.\n");
        return NULL;
    }

    int tempKey = heap->heap->entries[1].key;
    heap->heap->entries[1].key = heap->heap->entries[heap->heap->size - 1].key;
    heap->heap->entries[heap->heap->size - 1].key = tempKey;

    Data* tempObj = heap->heap->entries[1].obj;
    heap->heap->entries[1].obj = heap->heap->entries[heap->heap->size - 1].obj;
    heap->heap->entries[heap->heap->size - 1].obj = tempObj;

    Data *max = heap->heap->entries[heap->heap->size - 1].obj;
    deleteFromPosition(heap->heap, heap->heap->size - 1);
    printf("Heap size: %d\n.", heap->heap->size);
    heapify(heap, 1);

    return max;
}

int increaseKey(MaxHeap* heap, int idx, int newKey);

int decreaseKey(MaxHeap* heap, int idx, int newKey) {
    if (!heap || !heap->heap) {
        printf("Invalid heap configuration.\n");
        return 1;
    }

    if (!heap->heap->size) {
        printf("Heap is empty.\n");
        return 1;
    }

    if (idx < 1 || idx > heap->heap->size) {
        printf("Invalid index.\n");
        return 1;
    }

    if (heap->heap->entries[idx].key <= newKey) {
        printf("Required: New key > current key.");
        return 1;
    }

    heap->heap->entries[idx].key = newKey; 
    return heapify(heap, idx);
    
}
int insertElement(MaxHeap *heap, int key);
int deleteElement(MaxHeap *heap, int idx);
void heapSort(DynamicArray *arr);

int main() {
    DynamicArray *arr = createNew();
    for (int i = 1; i <= 20; ++i) {
        insertByKey(arr, i, createNewData(i));
    }

    MaxHeap *heap = init(arr);
    traverse(heap->heap);

    for (int i = 1; i <= 21; ++i) {
        Data *max = extractMax(heap);
        printf("Extracted Max: %d\n", max ? max->value : INT_MIN);
    }
    traverse(heap->heap);

    printf("Size: %d\n", heap->heap->size);

    return 0;
}

