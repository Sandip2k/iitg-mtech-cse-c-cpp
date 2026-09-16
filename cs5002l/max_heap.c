#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "max_heap.h"
#include "operations.h"

static void swapEntries(DynamicArray *arr, int a, int b) {
    DynamicArrayEntry temp = arr->entries[a];
    arr->entries[a] = arr->entries[b];
    arr->entries[b] = temp;
}

int siftDown(MaxHeap *heap, int idx) {
    if (!heap || !heap->heap) {
        printf("Invalid heap configuration.\n");
        return 1;
    }

    if (heap->heap->size <= 1) {
        printf("Heap is empty.\n");
        return 1;
    }

    while (2 * idx < heap->heap->size) {
        int leftChildIdx = 2 * idx;
        int rightChildIdx = 2 * idx + 1;
        int largest = idx;

        if (
            leftChildIdx < heap->heap->size &&
            heap->heap->entries[leftChildIdx].key > heap->heap->entries[largest].key
        ) {
            largest = leftChildIdx;
        }

        if (
            rightChildIdx < heap->heap->size &&
            heap->heap->entries[rightChildIdx].key > heap->heap->entries[largest].key
        ) {
            largest = rightChildIdx;
        }

        if (largest == idx) {
            break;
        }

        swapEntries(heap->heap, idx, largest);
        idx = largest;
    }

    return 0;
}

int siftUp(MaxHeap *heap, int idx) {
    if (!heap || !heap->heap) {
        printf("Invalid heap configuration.\n");
        return 1;
    }

    if (heap->heap->size <= 1) {
        printf("Heap is empty.\n");
        return 1;
    }

    while (idx > 1) {
        int parentIdx = idx / 2;
        if (heap->heap->entries[idx].key <= heap->heap->entries[parentIdx].key) {
            break;
        }

        swapEntries(heap->heap, idx, parentIdx);
        idx = parentIdx;
    }

    return 0;
}

MaxHeap *heapify(DynamicArray *arr) {
    MaxHeap *result = (MaxHeap *) malloc(sizeof(MaxHeap));
    if (!result) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    result->heap = createNew();
    if (!result->heap) {
        free(result);
        return NULL;
    }

    insertByKey(result->heap, INT_MIN, NULL);
    for (int i = 0; i < arr->size; ++i) {
        if (insertByKey(result->heap, arr->entries[i].key, arr->entries[i].obj)) {
            printf("Heap initialization failed for i = %d.\n", i);
            free(result->heap->entries);
            free(result->heap);
            free(result);
            return NULL;
        }
    }

    for (int i = result->heap->size / 2; i >= 1; --i) {
        siftDown(result, i);
    }

    return result;
}

Data *maximumElement(MaxHeap *heap) {
    if (!heap || !heap->heap) {
        printf("Invalid heap configuration.\n");
        return NULL;
    }

    if (heap->heap->size <= 1) {
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

    if (heap->heap->size <= 1) {
        printf("Heap is empty.\n");
        return NULL;
    }

    Data *max = heap->heap->entries[1].obj;
    swapEntries(heap->heap, 1, heap->heap->size - 1);
    deleteFromPosition(heap->heap, heap->heap->size - 1);

    if (heap->heap->size > 1) {
        siftDown(heap, 1);
    }

    return max;
}

int increaseKey(MaxHeap *heap, int idx, int newKey) {
    if (!heap || !heap->heap) {
        printf("Invalid heap configuration.\n");
        return 1;
    }

    if (heap->heap->size <= 1) {
        printf("Heap is empty.\n");
        return 1;
    }

    if (idx < 1 || idx >= heap->heap->size) {
        printf("Invalid index.\n");
        return 1;
    }

    if (heap->heap->entries[idx].key > newKey) {
        printf("Required: New key >= current key.\n");
        return 1;
    }

    heap->heap->entries[idx].key = newKey;
    return siftUp(heap, idx);
}

int decreaseKey(MaxHeap *heap, int idx, int newKey) {
    if (!heap || !heap->heap) {
        printf("Invalid heap configuration.\n");
        return 1;
    }

    if (heap->heap->size <= 1) {
        printf("Heap is empty.\n");
        return 1;
    }

    if (idx < 1 || idx >= heap->heap->size) {
        printf("Invalid index.\n");
        return 1;
    }

    if (heap->heap->entries[idx].key < newKey) {
        printf("Required: New key <= current key.\n");
        return 1;
    }

    heap->heap->entries[idx].key = newKey;
    return siftDown(heap, idx);
}

int insertElement(MaxHeap *heap, int key, Data *obj) {
    if (!heap || !heap->heap) {
        printf("Invalid heap configuration.\n");
        return 1;
    }

    if (insertByKey(heap->heap, key, obj)) {
        printf("Insert operation failed for the key: %d.\n", key);
        return 1;
    }

    return siftUp(heap, heap->heap->size - 1);
}

int deleteElement(MaxHeap *heap, int idx) {
    if (!heap || !heap->heap) {
        printf("Invalid heap configuration.\n");
        return 1;
    }

    if (idx < 1 || idx >= heap->heap->size) {
        printf("Invalid index.\n");
        return 1;
    }

    int lastIndex = heap->heap->size - 1;
    if (idx != lastIndex) {
        swapEntries(heap->heap, idx, lastIndex);
    }

    if (deleteFromPosition(heap->heap, lastIndex)) {
        printf("Delete operation failed for the idx: %d.\n", idx);
        return 1;
    }

    if (idx < heap->heap->size && idx > 1) {
        int parentIdx = idx / 2;
        if (heap->heap->entries[idx].key > heap->heap->entries[parentIdx].key) {
            return siftUp(heap, idx);
        }
    }

    if (idx < heap->heap->size) {
        return siftDown(heap, idx);
    }

    return 0;
}

/*
 * In-place heap sort using MaxHeap. The sorted order will be in ascending order.
*/
void heapSort(DynamicArray *arr) {
    MaxHeap *heap = (MaxHeap *) malloc(sizeof(MaxHeap));

    if (!heap) {
        printf("Memory allocation failed.\n");
        return;
    }

    heap->heap = arr;
    insertByKeyAtPosition(heap->heap, INT_MIN, NULL, 0);
    int originalSize = arr->size;

    for (int i = heap->heap->size / 2; i >= 1; --i) {
        siftDown(heap, i);
    }

    traverse(heap->heap);

    for (int i = heap->heap->size - 1; i > 0; --i) {
        swapEntries(heap->heap, 1, i);
        heap->heap->size--;
        siftDown(heap, 1);
    }

    heap->heap->size = originalSize;
    deleteFromPosition(heap->heap, 0);
}

int main() {
    DynamicArray *arr = createNew();
    for (int i = 1; i <= 20; ++i) {
        insertByKey(arr, i, createNewData(i));
    }

    MaxHeap *heap = heapify(arr);
    traverse(heap->heap);

    increaseKey(heap, 5, 42);
    decreaseKey(heap, 7, 2);
    traverse(heap->heap);

    Data *max = maximumElement(heap);
    if (max) {
        printf("Maximum element: %d\n", max->value);
    }

    for (int i = 1; i <= 25; ++i) {
        max = extractMax(heap);
        if (max) {
            printf("Extracted Max: %d\n", max->value);
        }
    }
    traverse(heap->heap);

    for (int i = 45; i <= 70; ++i) {
        insertElement(heap, i, createNewData(i));
    }
    traverse(heap->heap);

    for (int i = 1; i <= 25; ++i) {
        max = extractMax(heap);
        if (max) {
            printf("Extracted Max: %d\n", max->value);
        }
    }
    traverse(heap->heap);

    printf("Size: %d\n", heap->heap->size);

    DynamicArray *arr2 = createNew();
    insertByKey(arr2, 5, NULL);
    insertByKey(arr2, 1, NULL);
    insertByKey(arr2, -2, NULL);
    insertByKey(arr2, 5, NULL);
    insertByKey(arr2, 7, NULL);
    insertByKey(arr2, 12, NULL);
    insertByKey(arr2, 3, NULL);

    heapSort(arr2);
    traverse(arr2);

    return 0;
}
