#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "min_heap.h"
#include "operations.h"

static void swapEntries(DynamicArray *arr, int a, int b) {
    DynamicArrayEntry temp = arr->entries[a];
    arr->entries[a] = arr->entries[b];
    arr->entries[b] = temp;
}

int siftDown(MinHeap *heap, int idx) {
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
        int smallest = idx;

        if (
            leftChildIdx < heap->heap->size &&
            heap->heap->entries[leftChildIdx].key < heap->heap->entries[smallest].key
        ) {
            smallest = leftChildIdx;
        }

        if (
            rightChildIdx < heap->heap->size &&
            heap->heap->entries[rightChildIdx].key < heap->heap->entries[smallest].key
        ) {
            smallest = rightChildIdx;
        }

        if (smallest == idx) {
            break;
        }

        swapEntries(heap->heap, idx, smallest);
        idx = smallest;
    }

    return 0;
}

int siftUp(MinHeap *heap, int idx) {
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
        if (heap->heap->entries[idx].key >= heap->heap->entries[parentIdx].key) {
            break;
        }

        swapEntries(heap->heap, idx, parentIdx);
        idx = parentIdx;
    }

    return 0;
}

MinHeap *heapify(DynamicArray *arr) {
    MinHeap *result = (MinHeap *) malloc(sizeof(MinHeap));
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

Data *minimumElement(MinHeap *heap) {
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

Data *extractMin(MinHeap *heap) {
    if (!heap || !heap->heap) {
        printf("Invalid heap configuration.\n");
        return NULL;
    }

    if (heap->heap->size <= 1) {
        printf("Heap is empty.\n");
        return NULL;
    }

    Data *min = heap->heap->entries[1].obj;
    swapEntries(heap->heap, 1, heap->heap->size - 1);
    deleteFromPosition(heap->heap, heap->heap->size - 1);

    if (heap->heap->size > 1) {
        siftDown(heap, 1);
    }

    return min;
}

int increaseKey(MinHeap *heap, int idx, int newKey) {
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
    return siftDown(heap, idx);
}

int decreaseKey(MinHeap *heap, int idx, int newKey) {
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
    return siftUp(heap, idx);
}

int insertElement(MinHeap *heap, int key, Data *obj) {
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

int deleteElement(MinHeap *heap, int idx) {
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
        if (heap->heap->entries[idx].key < heap->heap->entries[parentIdx].key) {
            return siftUp(heap, idx);
        }
    }

    if (idx < heap->heap->size) {
        return siftDown(heap, idx);
    }

    return 0;
}

/*
 * In-place heap sort using MinHeap. The sorted order will be in descending order.
*/
void heapSort(DynamicArray *arr) {
    MinHeap *heap = (MinHeap *) malloc(sizeof(MinHeap));

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

    MinHeap *heap = heapify(arr);
    traverse(heap->heap);

    increaseKey(heap, 5, 42);
    decreaseKey(heap, 7, 2);
    traverse(heap->heap);

    Data *min = minimumElement(heap);
    if (min) {
        printf("Minimum element: %d\n", min->value);
    }

    for (int i = 1; i <= 25; ++i) {
        min = extractMin(heap);
        if (min) {
            printf("Extracted Min: %d\n", min->value);
        }
    }
    traverse(heap->heap);

    for (int i = 45; i <= 70; ++i) {
        insertElement(heap, i, createNewData(i));
    }
    traverse(heap->heap);

    for (int i = 1; i <= 25; ++i) {
        min = extractMin(heap);
        if (min) {
            printf("Extracted Min: %d\n", min->value);
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
