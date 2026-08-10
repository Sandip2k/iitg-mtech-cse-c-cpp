#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "dynamic_array.h"
#include "constants.h"

// Assume distinct entries.
// If the satellite data is not present, INT_MIN is printed to indicate the same.
// Resizing only takes place if the capacity is between the default minimum and maximum capacity, inclusive.

DynamicArray *createNew() {
    DynamicArray *arr = (DynamicArray *) malloc(sizeof(DynamicArray));
    if (!arr) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    arr->capacity = DEFAULT_MIN_CAPACITY;
    arr->size = 0;
    arr->entries = (DynamicArrayEntry *) malloc(arr->capacity * sizeof(DynamicArrayEntry));
    if (!arr->entries) {
        printf("Memory allocation failed.\n");
        free(arr);
        return NULL;
    }
    return arr;
}

int minimum(int a, int b) {
    return (a <= b) ? a : b;
}

int maximum(int a, int b) {
    return (a >= b) ? a : b;
}

int size(DynamicArray *arr) {
    if (!arr || !arr->entries) {
        printf("Invalid array.\n");
        return -1;
    }
    return arr->size;
}

int capacity(DynamicArray *arr) {
    if (!arr || !arr->entries) {
        printf("Invalid array.\n");
        return -1;
    }
    return arr->capacity;
}

int resize(DynamicArray *arr) {
    int size = arr->size;
    int capacity = arr->capacity;

    if (size == capacity) { // increase the size
        if (capacity == DEFAULT_MAX_CAPACITY) {
            printf("Reached maximum capacity.\n");
            return 1; // can't expand further, an error scenario.
        }
        DynamicArrayEntry *temp = (DynamicArrayEntry *) realloc(
            arr->entries, minimum(capacity * 2, DEFAULT_MAX_CAPACITY) * sizeof(DynamicArrayEntry)
        );
        if (temp) {
            arr->capacity = minimum(capacity * 2, DEFAULT_MAX_CAPACITY);
            arr->entries = temp;
            printf("Resized from capacity = %d to capacity = %d.\n", capacity, arr->capacity);
            return 0;
        } else {
            printf("Failed to resize.\n");
            return 1;
        }
    } else if (size <= (capacity / 4)) { // decrease the size
        if (capacity == DEFAULT_MIN_CAPACITY) {
            printf("Already at minimum default capacity.\n");
            return 0; // can't contract further, but not an error scenario.
        }
        DynamicArrayEntry *temp = (DynamicArrayEntry *) realloc(
            arr->entries, maximum(capacity / 2, DEFAULT_MIN_CAPACITY) * sizeof(DynamicArrayEntry)
        );
        if (temp) {
            arr->capacity = maximum(capacity / 2, DEFAULT_MIN_CAPACITY);
            arr->entries = temp;
            printf("Resized from capacity = %d to capacity = %d.\n", capacity, arr->capacity);
            return 0;
        } else {
            printf("Failed to resize.\n");
            return 1;
        }
    } else {
        return 0; // no resizing needed
    }
}

int insertByKey(DynamicArray *arr, int key, Data *obj) {
    if (!arr || !arr->entries) {
        printf("Invalid array.\n");
        return 1;
    }

    if (resize(arr)) {
        printf("Failed to resize array.\n");
        return 1;
    }

    arr->entries[arr->size].key = key;
    arr->entries[arr->size].obj = obj;
    arr->size++;
    printf(
            "Inserted { Key: %d, Obj->Value: %d } at the end.\n",
            arr->entries[arr->size - 1].key,
            arr->entries[arr->size - 1].obj ? 
            arr->entries[arr->size - 1].obj->value : INT_MIN
        );
    return 0;
}

int insertByKeyAtPosition(DynamicArray *arr, int key, Data *obj, int position) {
    if (!arr || !arr->entries) {
        printf("Invalid array.\n");
        return 1;
    }
    if (position < 0 || position > arr->size) {
        printf("Invalid position.\n");
        return 1;
    }
    if (position == arr->size) {
        // essentially, insert at the end.
        return insertByKey(arr, key, obj);
    } else {
        if (resize(arr)) {
            printf("Failed to resize array.\n");
            return 1;
        }
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
            arr->entries[position].obj ?
            arr->entries[position].obj->value : INT_MIN,
            position
        );
        return 0;
    }
}

int search(DynamicArray *arr, int key) {
    if (!arr || !arr->entries) {
        printf("Invalid array.\n");
        return -1;
    }
    // return the index of the first occurrence of the key.
    // if the key is not found, then return -1.
    for (int i = 0; i < arr->size; ++i) {
        if (arr->entries[i].key == key)
            return i;
    }
    return -1;
}

int deleteByKey(DynamicArray *arr, int key) {
    if (!arr || !arr->entries) {
        printf("Invalid array.\n");
        return 1;
    }

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
        temp.obj ? temp.obj->value : INT_MIN,
        index
    );
    free(temp.obj);
    arr->size--;
    if (resize(arr)) {
        printf("Failed to resize array.\n");
        return 1;
    }
    return 0;
}

int deleteFromPosition(DynamicArray *arr, int position) {
    if (!arr || !arr->entries) {
        printf("Invalid array.\n");
        return 1;
    }

    if (position < 0 || position > arr->size - 1) {
        printf("Invalid position.\n");
        return 1;
    }

    DynamicArrayEntry temp = arr->entries[position];
    for (int j = position; j < arr->size; ++j) {
        arr->entries[j] = arr->entries[j + 1];
    }
    printf(
        "Deleted { Key: %d, Obj->Value: %d } from position = %d.\n",
        temp.key,
        temp.obj ? temp.obj->value : INT_MIN,
        position
    );
    free(temp.obj);
    arr->size--;
    if (resize(arr)) {
        printf("Failed to resize array.\n");
        return 1;
    }
    return 0;
}

int searchObj(DynamicArray *arr, Data obj) {
    if (!arr || !arr->entries) {
        printf("Invalid array.\n");
        return -1;
    }

    for (int i = 0; i < arr->size; ++i) {
        if (arr->entries[i].obj && arr->entries[i].obj->value == obj.value)
            return i;
    }
    return -1;
}

int deleteByObj(DynamicArray *arr, Data obj) {
    if (!arr || !arr->entries) {
        printf("Invalid array.\n");
        return 1;
    }

    int index = searchObj(arr, obj);

    if (index == -1) {
        printf("Object not found.\n");
        return 1;
    }

    DynamicArrayEntry temp = arr->entries[index];
    for (int j = index; j < arr->size; ++j) {
        arr->entries[j] = arr->entries[j + 1];
    }
    printf(
        "Deleted { Key: %d, Obj->Value: %d } from position = %d.\n",
        temp.key,
        temp.obj ? temp.obj->value : INT_MIN,
        index
    );
    free(temp.obj);
    arr->size--;
    if (resize(arr)) {
        printf("Failed to resize array.\n");
        return 1;
    }
    return 0;
}

int modify(DynamicArray *arr, int key, Data *newObj) {
    if (!arr || !arr->entries) {
        printf("Invalid array.\n");
        return 1;
    }

    int index = search(arr, key);

    if (index == -1) {
        printf("Object not found.\n");
        return 1;
    }

    arr->entries[index].obj = newObj;
    return 0;
}

void traverse(DynamicArray *arr) {
    if (!arr || !arr->entries) {
        printf("Invalid array.\n");
        return;
    }

    printf("Size = %d, Capacity = %d.\n", arr->size, arr->capacity);
    for (int i = 0; i < arr->size; ++i) {
        // there can be another way of processing the data, but for now we're just printing it.
        // maybe in the future, we can add a function pointer to process the data in a more generic way.
        printf(
            "{ Key: %d, Obj->Value: %d }\n",
            arr->entries[i].key,
            arr->entries[i].obj ? arr->entries[i].obj->value : INT_MIN
        );
    }
}

void mergeTwoSortedArrays(DynamicArray *arr, int start, int mid, int end) {
    int i = start, j = mid + 1, k = 0;
    DynamicArrayEntry *tempEntries = (DynamicArrayEntry *) malloc((end - start + 1) * sizeof(DynamicArrayEntry));
    while (i <= mid && j <= end) {
        if (arr->entries[i].key <= arr->entries[j].key) {
            tempEntries[k].key = arr->entries[i].key;
            tempEntries[k].obj = arr->entries[i].obj;
            k++; i++;
        } else {
            tempEntries[k].key = arr->entries[j].key;
            tempEntries[k].obj = arr->entries[j].obj;
            k++; j++;
        }
    }

    while (i <= mid) {
        tempEntries[k].key = arr->entries[i].key;
        tempEntries[k].obj = arr->entries[i].obj;
        k++; i++;
    }

    while (j <= end) {
        tempEntries[k].key = arr->entries[j].key;
        tempEntries[k].obj = arr->entries[j].obj;
        k++; j++;
    }

    // copy back.
    for (int i = start; i <= end; ++i) {
        arr->entries[i].key = tempEntries[i - start].key;
        arr->entries[i].obj = tempEntries[i - start].obj;
    }

    // free the temporary memory.
    free(tempEntries);
}

void sort(DynamicArray *arr, int start, int end) {
    if (!arr || !arr->entries) {
        printf("Invalid array.\n");
        return;
    }

    if (start >= end) {
        return;
    }

    int mid = start + (end - start) / 2;
    sort(arr, start, mid);
    sort(arr, mid + 1, end);
    mergeTwoSortedArrays(arr, start, mid, end);
}

DynamicArray **split(DynamicArray *arr, int atPosition) {
    if (!arr || !arr->entries) {
        printf("Invalid array.\n");
        return NULL;
    }

    DynamicArray **result = (DynamicArray **) malloc(2 * sizeof(DynamicArray *));
    if (!result) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    if (atPosition < -1 || atPosition >= arr->size) {
        printf("Invalid position.\n");
        return NULL;
    }

    result[0] = (DynamicArray *) malloc(sizeof(DynamicArray));
    if (!result[0]) {
        printf("Memory allocation failed.\n");
        free(result);
        return NULL;
    }
    result[0]->capacity = result[0]->size = minimum(atPosition + 1, arr->size);
    result[0]->entries = (DynamicArrayEntry *) malloc(result[0]->size * sizeof(DynamicArrayEntry));
    if (!result[0]->entries) {
        printf("Memory allocation failed.\n");
        free(result[0]);
        free(result);
        return NULL;
    }

    for (int i = 0; i <= atPosition; ++i) {
        result[0]->entries[i].key = arr->entries[i].key;
        result[0]->entries[i].obj = arr->entries[i].obj;
    }

    result[1] = (DynamicArray *) malloc(sizeof(DynamicArray));
    if (result[1] == NULL) {
        printf("Memory allocation failed.\n");
        free(result[0]->entries);
        free(result[0]);
        free(result);
        return NULL;
    }
    result[1]->capacity = result[1]->size = minimum(arr->size - 1 - atPosition, arr->size);
    result[1]->entries = (DynamicArrayEntry *) malloc(result[1]->size * sizeof(DynamicArrayEntry));
    if (!result[1]->entries) {
        printf("Memory allocation failed.\n");
        free(result[1]);
        free(result[0]->entries);
        free(result[0]);
        free(result);
        return NULL;
    }

    for (int i = atPosition + 1; i < arr->size; ++i) {
        result[1]->entries[i - (atPosition + 1)].key = arr->entries[i].key;
        result[1]->entries[i - (atPosition + 1)].obj = arr->entries[i].obj;
    }

    return result;
}

DynamicArray *join(DynamicArray *arr1, DynamicArray *arr2) {
    if (!arr1 || !arr1->entries || !arr2 || !arr2->entries) {
        printf("Invalid array(s).\n");
        return NULL;
    }

    int size = 0;
    if (arr1) {
        size += arr1->size;
    }

    if (arr2) {
        size += arr2->size;
    }

    DynamicArray *result = (DynamicArray *) malloc(sizeof(DynamicArray));
    if (!result) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    result->size = result->capacity = size;
    result->entries = (DynamicArrayEntry *) malloc(size * sizeof(DynamicArrayEntry));
    if (!result->entries) {
        printf("Memory allocation failed.\n");
        free(result);
        return NULL;
    }

    int i = 0, k = 0;
    while (i < arr1->size) {
        result->entries[k].key = arr1->entries[i].key;
        result->entries[k].obj = arr1->entries[i].obj;
        k++; i++;
    }

    i = 0;
    while (i < arr2->size) {
        result->entries[k].key = arr2->entries[i].key;
        result->entries[k].obj = arr2->entries[i].obj;
        k++; i++;
    }

    return result;
}

/*
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
    sort(arr, 0, arr->size - 1);
    traverse(arr);
    deleteByKey(arr, 20);
    deleteByKey(arr, 22);
    deleteByKey(arr, 7);
    traverse(arr);
    for (int i = 0; i < 18; ++i) {
        deleteByKey(arr, i);
    }
    traverse(arr);
    DynamicArray **splitResult = split(arr, 2);
    if (splitResult) {
        traverse(splitResult[0]);
        traverse(splitResult[1]);
        DynamicArray *joinResult = join(splitResult[0], splitResult[1]);
        traverse(joinResult);
    }
    return 0;
}
*/