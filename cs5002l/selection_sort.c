#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void array_print(const int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void selection_sort(int *arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        int minimum_index = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[minimum_index]) {
                minimum_index = j;
            }
        }
        swap(&arr[i], &arr[minimum_index]);
    }
}

int *array_input(int *size) {
    printf("Enter size: ");
    if (scanf("%d", size) != 1 || *size < 0) {
        return NULL;
    }

    int *arr = malloc((size_t)*size * sizeof(*arr));
    if (*size > 0 && arr == NULL) {
        return NULL;
    }

    if (*size > 0) {
        printf("Enter array elements: ");
        for (int i = 0; i < *size; ++i) {
            scanf("%d", &arr[i]);
        }
    }
    return arr;
}

int main(void) {
    int size;
    int *arr = array_input(&size);
    if (arr == NULL && size > 0) {
        return 1;
    }

    selection_sort(arr, size);
    array_print(arr, size);
    free(arr);
    return 0;
}
