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
            printf("Resized from capacity = %d to capacity = %d.\n", capacity, arr->capacity);
        } else {
            printf("Failed to resize.\n");
        }
    } else if (size == (capacity / 4)) { // decrease the size
        DynamicArrayEntry *temp = (DynamicArrayEntry *) realloc(arr->entries, (capacity / 2) * sizeof(DynamicArrayEntry));
        if (temp) {
            arr->capacity = capacity / 2;
            arr->entries = temp;
            printf("Resized from capacity = %d to capacity = %d.\n", capacity, arr->capacity);
        } else {
            printf("Failed to resize.\n");
        }
    }
}

int insertByKey(DynamicArray *arr, int key, Data *obj) {
    resize(arr); // will resize if neccessary, else no operation is performed.
    arr->entries[arr->size].key = key;
    arr->entries[arr->size].obj = obj;
    arr->size++;
    printf(
            "Inserted { Key: %d, Obj->Value: %d } at the end.\n",
            arr->entries[arr->size - 1].key,
            arr->entries[arr->size - 1].obj->value
        );
    return 0;
}

int insertByKeyAtPosition(DynamicArray *arr, int key, Data *obj, int position) {
    if (position < 0 || position > arr->size) {
        printf("Invalid position.\n");
        return 1;
    }
    if (position == arr->size) {
        // essentially, insert at the end.
        return insertByKey(arr, key, obj);
    } else {
        resize(arr);
        // right-shift all the entries from (position + 1) to (size - 1) by 1.
        for (int i = arr->size - 1; i >= position; --i) {
            arr->entries[i + 1] = arr->entries[i];
        }
        arr->entries[position].key = key;
        arr->entries[position].obj = obj;
        arr->size++;
        printf(
            "Inserted { Key: %d, Obj->Value: %d } at position = %d.\n",
            arr->entries[position].key,
            arr->entries[position].obj->value,
            position
        );
        return 0;
    }
}

int search(DynamicArray *arr, int key) {
    // return the index of the first occurrence of the key.
    // if the key is not found, then return -1.
    for (int i = 0; i < arr->size; ++i) {
        if (arr->entries[i].key == key)
            return i;
    }
    return -1;
}

int deleteByKey(DynamicArray *arr, int key) {
    int index = search(arr, key);

    if (index == -1) {
        printf("Key not found.\n");
        return 1;
    }

    DynamicArrayEntry temp = arr->entries[index];
    for (int j = index; j < arr->size; ++j) {
        arr->entries[j] = arr->entries[j + 1];
    }
    printf(
        "Deleted { Key: %d, Obj->Value: %d } from position = %d.\n",
        temp.key,
        temp.obj->value,
        index
    );
    free(temp.obj);
    arr->size--;
    resize(arr);
    return 0;
}

void traverse(DynamicArray *arr) {
    printf("Size = %d, Capacity = %d.\n", arr->size, arr->capacity);
    for (int i = 0; i < arr->size; ++i) {
        // there can be another way of processing the data, but for now we're just printing it.
        // maybe in the future, we can add a function pointer to process the data in a more generic way.
        printf(
            "{ Key: %d, Obj->Value: %d }\n",
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
    insertByKeyAtPosition(arr, 21, createNewData(21), 5);
    insertByKeyAtPosition(arr, 22, createNewData(22), 0);
    insertByKeyAtPosition(arr, 23, createNewData(23), arr->size);
    traverse(arr);
    deleteByKey(arr, 20);
    deleteByKey(arr, 22);
    deleteByKey(arr, 7);
    traverse(arr);
    for (int i = 0; i < 18; ++i) {
        deleteByKey(arr, i);
    }
    traverse(arr);
    return 0;
}