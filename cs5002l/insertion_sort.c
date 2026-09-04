#include <stdio.h>
#include <stdlib.h>

void array_print(const int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertion_sort(int *arr, int size) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
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

    insertion_sort(arr, size);
    array_print(arr, size);
    free(arr);
    return 0;
}
