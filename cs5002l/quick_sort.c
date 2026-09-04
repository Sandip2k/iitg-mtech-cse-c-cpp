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

int partition(int *arr, int start, int end, int pivot) {
    int i = start;
    int j = start;
    int k = end;

    while (j <= k) {
        if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            ++i;
            ++j;
        } else if (arr[j] > pivot) {
            swap(&arr[j], &arr[k]);
            --k;
        } else {
            ++j;
        }
    }
    return i;
}

void quick_sort(int *arr, int start, int end) {
    if (start >= end) {
        return;
    }

    int mid = start + (end - start) / 2;
    int pivot = arr[mid];
    int partition_index = partition(arr, start, end, pivot);
    quick_sort(arr, start, partition_index - 1);
    quick_sort(arr, partition_index + 1, end);
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

    quick_sort(arr, 0, size - 1);
    array_print(arr, size);
    free(arr);
    return 0;
}
