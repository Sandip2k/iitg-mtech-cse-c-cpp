#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "max_heap.h"
#include "operations.h"

int siftDown(MaxHeap *heap, int idx) {
    if (!heap || !heap->heap) {
        printf("Invalid heap configuration.\n");
        return 1;
    }

    if (heap->heap->size <= 1) {
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

    return siftDown(heap, argMax);
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

    if (idx == 1) {
        return 0;
    }

    int parentIdx = idx / 2;
    int siblingIdx = (idx == 2 * parentIdx) ? (2 * parentIdx + 1) : (2 * parentIdx);

    int max = heap->heap->entries[idx].key, argMax = idx;
    int parent = heap->heap->entries[parentIdx].key;
    int sibling = (siblingIdx < heap->heap->size) ? heap->heap->entries[siblingIdx].key : INT_MIN;

    if (max < parent) {
        max = parent;
        argMax = parentIdx;
    }

    if (max < sibling) {
        max = sibling;
        argMax = siblingIdx;
    }

    if (argMax != parentIdx) {
        int tempKey = heap->heap->entries[parentIdx].key;
        heap->heap->entries[parentIdx].key = heap->heap->entries[argMax].key;
        heap->heap->entries[argMax].key = tempKey;

        Data *tempObj= heap->heap->entries[parentIdx].obj;
        heap->heap->entries[parentIdx].obj = heap->heap->entries[argMax].obj;
        heap->heap->entries[argMax].obj = tempObj;
    } else {
        return 0;
    }

    return siftUp(heap, parentIdx);
}

MaxHeap *heapify(DynamicArray *arr) {
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

    int tempKey = heap->heap->entries[1].key;
    heap->heap->entries[1].key = heap->heap->entries[heap->heap->size - 1].key;
    heap->heap->entries[heap->heap->size - 1].key = tempKey;

    Data* tempObj = heap->heap->entries[1].obj;
    heap->heap->entries[1].obj = heap->heap->entries[heap->heap->size - 1].obj;
    heap->heap->entries[heap->heap->size - 1].obj = tempObj;

    Data *max = heap->heap->entries[heap->heap->size - 1].obj;
    deleteFromPosition(heap->heap, heap->heap->size - 1);
    siftDown(heap, 1);

    return max;
}

int increaseKey(MaxHeap* heap, int idx, int newKey) {
    if (!heap || !heap->heap) {
        printf("Invalid heap configuration.\n");
        return 1;
    }

    if (heap->heap->size <= 1) {
        printf("Heap is empty.\n");
        return 1;
    }

    if (idx < 1 || idx > heap->heap->size) {
        printf("Invalid index.\n");
        return 1;
    }

    if (heap->heap->entries[idx].key > newKey) {
        printf("Required: New key < current key.\n");
        return 1;
    }

    heap->heap->entries[idx].key = newKey;
    return siftUp(heap, idx);
}

int decreaseKey(MaxHeap* heap, int idx, int newKey) {
    if (!heap || !heap->heap) {
        printf("Invalid heap configuration.\n");
        return 1;
    }

    if (heap->heap->size <= 1) {
        printf("Heap is empty.\n");
        return 1;
    }

    if (idx < 1 || idx > heap->heap->size) {
        printf("Invalid index.\n");
        return 1;
    }

    if (heap->heap->entries[idx].key < newKey) {
        printf("Required: New key > current key.\n");
        return 1;
    }

    heap->heap->entries[idx].key = newKey; 
    return siftDown(heap, idx);
    
}

int insertElement(MaxHeap *heap, int key, Data *obj) {
    if (insertByKey(heap->heap, key, obj)) {
        printf("Insert operation failed for the key: %d.\n", key);
        return 1;
    }

    return siftUp(heap, heap->heap->size - 1);
}

int deleteElement(MaxHeap *heap, int idx) {
    int tempKey = heap->heap->entries[idx].key;
    heap->heap->entries[idx].key = heap->heap->entries[heap->heap->size - 1].key;
    heap->heap->entries[heap->heap->size - 1].key = tempKey;

    Data* tempObj = heap->heap->entries[idx].obj;
    heap->heap->entries[idx].obj = heap->heap->entries[heap->heap->size - 1].obj;
    heap->heap->entries[heap->heap->size - 1].obj = tempObj;

    if (!deleteFromPosition(heap->heap, heap->heap->size - 1)) {
        printf("Insert operation failed for the idx: %d.\n", idx);
        return 1;
    }

    return siftDown(heap, idx);
}

void heapSort(DynamicArray *arr) {

}

int main() {
    DynamicArray *arr = createNew();
    for (int i = 1; i <= 20; ++i) {
        insertByKey(arr, i, createNewData(i));
    }

    MaxHeap *heap = heapify(arr);
    traverse(heap->heap);

    increaseKey(heap, 5, 42);
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

    return 0;
}
