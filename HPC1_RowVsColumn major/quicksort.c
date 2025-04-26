#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// Function declarations
int compare(const void* a, const void* b);
int partition(int* array, int low, int high);

void traverseArray() {
    int size = 10000;
    int** array = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; ++i) {
        array[i] = (int*)malloc(size * sizeof(int));
    }

    // Initialize the array
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            array[i][j] = i + j;
        }
    }

    // Row-major traversal
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);
    long long sumRowMajor = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            sumRowMajor += array[i][j];
        }
    }
    gettimeofday(&endTime, NULL);
    long rowTime = (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec);
    printf("Row-major traversal time: %ld us\n", rowTime);

    // Column-major traversal
    gettimeofday(&startTime, NULL);
    long long sumColMajor = 0;
    for (int j = 0; j < size; ++j) {
        for (int i = 0; i < size; ++i) {
            sumColMajor += array[i][j];
        }
    }
    gettimeofday(&endTime, NULL);
    long colTime = (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec);
    printf("Column-major traversal time: %ld us\n", colTime);
    double betterFactor = (double)colTime / rowTime;
    printf("Row time is %.2f times faster than column time\n", betterFactor);

    for (int i = 0; i < size; ++i) {
        free(array[i]);
    }
    free(array);
}

void measureSortingEfficiency() {
    int size = 1000000;
    int* array = (int*)malloc(size * sizeof(int));
    srand(time(0));

    // Fill array with random integers
    for (int i = 0; i < size; ++i) {
        array[i] = rand();
    }

    // Measure sorting time
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);
    qsort(array, size, sizeof(int), (int (*)(const void*, const void*))compare);
    gettimeofday(&endTime, NULL);
    long sortingTime = (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec);
    printf("Sorting time: %ld us\n", sortingTime);

    free(array);
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void quickSort(int* array, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(array, low, high);
        quickSort(array, low, pivotIndex - 1);
        quickSort(array, pivotIndex + 1, high);
    }
}

int partition(int* array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (array[j] < pivot) {
            ++i;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;
}

void profileQuickSort() {
    int size = 1000000;
    int* array = (int*)malloc(size * sizeof(int));
    srand(time(0));

    // Fill array with random integers
    for (int i = 0; i < size; ++i) {
        array[i] = rand();
    }

    // Measure QuickSort time
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);
    quickSort(array, 0, size - 1);
    gettimeofday(&endTime, NULL);
    long quickSortTime = (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec);
    printf("QuickSort time: %ld us\n", quickSortTime);

    free(array);
}

int main() {
    printf("Task 1: Array Traversal\n");
    traverseArray();

    printf("\nTask 2: Sorting Efficiency\n");
    measureSortingEfficiency();

    printf("\nTask 3: Profiling QuickSort\n");
    profileQuickSort();

    return 0;
}
