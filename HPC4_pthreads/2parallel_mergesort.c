#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 3  

typedef struct {
    int *arr;
    int left;
    int right;
    int depth;
} MergeSortArgs;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void *mergeSort(void *args) {
    MergeSortArgs *arg = (MergeSortArgs *)args;
    int *arr = arg->arr, left = arg->left, right = arg->right, depth = arg->depth;

    if (left < right) {
        int mid = left + (right - left) / 2;
        pthread_t left_thread, right_thread;
        MergeSortArgs left_args = {arr, left, mid, depth + 1};
        MergeSortArgs right_args = {arr, mid + 1, right, depth + 1};

        if (depth < NUM_THREADS) {
            pthread_create(&left_thread, NULL, mergeSort, &left_args);
            pthread_create(&right_thread, NULL, mergeSort, &right_args);
            pthread_join(left_thread, NULL);
            pthread_join(right_thread, NULL);
        } else {
            mergeSort(&left_args);
            mergeSort(&right_args);
        }

        merge(arr, left, mid, right);
    }
    return NULL;
}

int main() {
    int arr[] = {42, 23, 74, 11, 65, 58, 92, 37, 18, 49, 81, 29, 4, 70, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    MergeSortArgs args = {arr, 0, n - 1, 0};
    clock_t start = clock();
    mergeSort(&args);
    clock_t end = clock();

    printf("Sorted array:   ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    printf("Execution time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
