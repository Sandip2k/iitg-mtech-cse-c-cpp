#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "operations.h"

#define GROUP_SIZE 5
#define MAX 20
#define MIN 0

void arrayPrint(const int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertionSort(int *arr, int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
    }
}

int medianOfMedians(int *arr, int n) {
    if (!arr || n <= 0) {
        return INT_MIN;
    }

    if (n <= 5) {
        insertionSort(arr, n);
        return arr[(n - 1) / 2];
    }

    int numPartitions = (n + GROUP_SIZE - 1) / GROUP_SIZE;

    for (int i = 0; i < numPartitions; ++i) {
        int start = i * GROUP_SIZE;
        int currentSize = minimum(n - start, GROUP_SIZE);
        insertionSort(arr + start, currentSize);

        int medianIndex = start + currentSize / 2;

        // ? for in-place operations, put all the medians in the first partition and reuse it.
        int temporary = arr[i];
        arr[i] = arr[medianIndex];
        arr[medianIndex] = temporary;
    }

    return medianOfMedians(arr, numPartitions);
}

void partition(int *arr, int start, int end, int pivot, int *equalStart, int *equalEnd) {
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
    *equalStart = i;
    *equalEnd = k;
}

int ithRankedElement(int *arr, int start, int end, int i) {
    // i is a one-based rank relative to the current subarray.
    if (!arr || start > end || i < 1 || i > end - start + 1) {
        printf("Value of i is invalid.\n");
        return INT_MIN;
    }

    int size = (end - start) + 1;

    // Copy the subarray because medianOfMedians rearranges its input.
    int *copy = (int *) malloc(size * sizeof(int));
    if (!copy) {
        return INT_MIN;
    }

    memcpy(copy, arr + start, size * sizeof(int));

    int median = medianOfMedians(copy, size);
    free(copy);

    int equalStart;
    int equalEnd;
    // Partition into values less than, equal to, and greater than the pivot.
    partition(arr, start, end, median, &equalStart, &equalEnd);
    
    // Convert absolute partition indices into ranks relative to [start, end].
    int equalStartRank = equalStart - start;
    int equalEndRank = equalEnd - start;

    if (i > equalStartRank && i <= equalEndRank + 1) {
        return median;
    } else if (i <= equalStartRank) {
        return ithRankedElement(arr, start, equalStart - 1, i);
    } else { // The right subarray has a reduced rank after discarding smaller/equal values.
        return ithRankedElement(arr, equalEnd + 1, end, i - equalEndRank - 1);
    }
}

int main() {
    srand(time(NULL));
    int n, i;
    printf("Enter size n: ");
    scanf("%d", &n);

    int *arr = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % (MAX - MIN + 1) + MIN;
    }

    arrayPrint(arr, n);

    printf("Enter i (1 <= i <= n): ");
    scanf("%d", &i);

    printf("%dth ranked element: %d\n", i, ithRankedElement(arr, 0, n - 1, i));
    return 0;
}