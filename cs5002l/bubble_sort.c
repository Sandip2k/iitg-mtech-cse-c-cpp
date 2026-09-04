#include <stdbool.h>
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

void bubble_sort(int *arr, int size) {
    for (int i = size - 1; i >= 0; --i) {
        bool did_swap = false;
        for (int j = 0; j < i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                did_swap = true;
            }
        }
        if (!did_swap) {
            break;
        }
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

    bubble_sort(arr, size);
    array_print(arr, size);
    free(arr);
    return 0;
}
