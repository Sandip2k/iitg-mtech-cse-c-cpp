#ifndef DYNAMIC_ARRAY_H

#include "data.h"

typedef struct DynamicArrayEntry {
    int key;
    Data *obj;
} DynamicArrayEntry;

typedef struct DynamicArray {
    DynamicArrayEntry *entries;
    int size;
    int capacity;
} DynamicArray;

DynamicArray *createNew();
int size(DynamicArray arr);
int capacity(DynamicArray arr);
int insertByKey(DynamicArray *arr, int key, Data *obj); // at the end
int insertByKeyAtPosition(DynamicArray *arr, int key, Data *obj, int position); // at the given position
int deleteByKey(DynamicArray *arr, int key);
int deleteFromPosition(DynamicArray *arr, int position);
int deleteByObj(DynamicArray *arr, Data obj);
int deleteAllByObj(DynamicArray *arr, Data obj);
int modify(DynamicArray *arr, int key, Data newObj);
void sort(DynamicArray *arr);
int search(DynamicArray arr);
void traverse(DynamicArray *arr);

#endif