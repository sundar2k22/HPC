#include <stdio.h>
#include <windows.h>

#define THREAD_COUNT 10
#define INCREMENT_ITERATIONS 1000

int shared_counter = 0;  
HANDLE counter_mutex;      

DWORD WINAPI increment_counter(LPVOID use_mutex) {
    int enable_locking = *((int*)use_mutex);  // Get user choice

    for (int i = 0; i < INCREMENT_ITERATIONS; ++i) {
        if (enable_locking) {
            WaitForSingleObject(counter_mutex, INFINITE);  // Lock
        }

        shared_counter++;  // Critical section

        if (enable_locking) {
            ReleaseMutex(counter_mutex);  // Unlock
        }
    }
    return 0;
}

int main() {
    HANDLE thread_handles[THREAD_COUNT];
    int enable_locking;

    printf("Choose Counter Implementation:\n");
    printf("1. Without Locking (Race Condition)\n");
    printf("2. With Mutex Locking (Thread Safe)\n");
    printf("Enter your choice: ");
    scanf("%d", &enable_locking);

    if (enable_locking == 2) {
        counter_mutex = CreateMutex(NULL, FALSE, NULL);  // Initialize Mutex
    }

    // Create threads
    for (int i = 0; i < THREAD_COUNT; ++i) {
        thread_handles[i] = CreateThread(NULL, 0, increment_counter, &enable_locking, 0, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < THREAD_COUNT; ++i) {
        WaitForSingleObject(thread_handles[i], INFINITE);
        CloseHandle(thread_handles[i]);
    }

    if (enable_locking == 2) {
        CloseHandle(counter_mutex);  // Destroy mutex
    }

    printf("Final Counter Value: %d\n", shared_counter);
    return 0;
}
