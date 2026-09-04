#include <stdio.h>
#include <stdlib.h>

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

void array_print(const int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void merge_two_sorted_arrays(int *arr, int start, int mid, int end) {
    int *temp = malloc((size_t)(end - start + 1) * sizeof(*temp));
    if (temp == NULL) {
        return;
    }

    int i = start;
    int j = mid + 1;
    int k = 0;
    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= end) {
        temp[k++] = arr[j++];
    }

    for (i = start; i <= end; ++i) {
        arr[i] = temp[i - start];
    }
    free(temp);
}

void merge_sort(int *arr, int start, int end) {
    if (start >= end) {
        return;
    }

    int mid = start + (end - start) / 2;
    merge_sort(arr, start, mid);
    merge_sort(arr, mid + 1, end);
    merge_two_sorted_arrays(arr, start, mid, end);
}

int main(void) {
    int size;
    int *arr = array_input(&size);
    if (arr == NULL && size > 0) {
        return 1;
    }

    merge_sort(arr, 0, size - 1);
    array_print(arr, size);
    free(arr);
    return 0;
}
