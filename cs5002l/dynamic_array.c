#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

DynamicArray *createNew() {
    DynamicArray *arr = (DynamicArray *) malloc(sizeof(DynamicArray));
    arr->capacity = 10;
    arr->size = 0;
    arr->entries = (DynamicArrayEntry *) malloc(arr->capacity * sizeof(DynamicArrayEntry));
    return arr;
}

int size(DynamicArray arr) { return arr.size; }

int capacity(DynamicArray arr) { return arr.capacity; }

void resize(DynamicArray *arr) {
    int size = arr->size;
    int capacity = arr->capacity;

    if (size == capacity) { // increase the size
        DynamicArrayEntry *temp = (DynamicArrayEntry *) realloc(arr->entries, capacity * 2 * sizeof(DynamicArrayEntry));
        if (temp) {
            arr->capacity = capacity * 2;
            arr->entries = temp;
        }
        printf("Resized from capacity = %d to capacity = %d\n", capacity, arr->capacity);
    } else if (size == (capacity / 4)) { // decrease the size
        // TODO: Halve the size of the array is <= 1/4 of the capacity.
    }
}

int insertByKey(DynamicArray *arr, int key, Data *obj) {
    resize(arr); // will resize if neccessary, else no operation is performed.
    arr->entries[arr->size].key = key;
    arr->entries[arr->size].obj = obj;
    arr->size++;
    printf(
            "Inserted { Key: %d, Obj->Value %d }\n",
            arr->entries[arr->size - 1].key,
            arr->entries[arr->size - 1].obj->value
        );
    return 0;
}

void traverse(DynamicArray *arr) {
    printf("Size = %d, Capacity = %d\n", arr->size, arr->capacity);
    for (int i = 0; i < arr->size; ++i) {
        // there can be another way of processing the data, but for now we're just printing it.
        // maybe in the future, we can add a function pointer to process the data in a more generic way.
        printf(
            "{ Key: %d, Obj->Value %d }\n",
            arr->entries[i].key,
            arr->entries[i].obj->value
        );
    }
}

int main() {
    DynamicArray *arr = createNew();
    for (int i = 1; i <= 20; ++i) {
        insertByKey(arr, i, createNewData(i));
    }
    traverse(arr);
    return 0;
}