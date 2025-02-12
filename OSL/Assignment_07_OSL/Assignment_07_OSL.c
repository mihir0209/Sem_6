#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to implement FCFS page replacement algorithm
int fcfs(int reference_string[], int n, int capacity) {
    int frames[capacity];
    int frame_index = 0;
    int page_faults = 0;
    bool present;

    // Initialize frames with -1 (indicating empty)
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    printf("FCFS Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        present = false;
        // Check if page is already in frame
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == reference_string[i]) {
                present = true;
                break;
            }
        }

        if (!present) {
            // Page fault occurred
            page_faults++;
            frames[frame_index] = reference_string[i];
            frame_index = (frame_index + 1) % capacity; // Circular queue
        }

        // Print current state of frames
        printf("Reference: %d | Frames: ", reference_string[i]);
        for (int j = 0; j < capacity; j++) {
            printf("%d ", frames[j]);
        }
        printf("| Page Fault: %s\n", present ? "No" : "Yes");
    }

    return page_faults;
}

// Function to implement LRU page replacement algorithm
int lru(int reference_string[], int n, int capacity) {
    int frames[capacity];
    int time[capacity]; // To track the last time each page was used
    int page_faults = 0;
    bool present;

    // Initialize frames with -1 (indicating empty) and time with 0
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    int current_time = 0; // Global timer

    printf("LRU Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        present = false;
        // Check if page is already in frame
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == reference_string[i]) {
                present = true;
                time[j] = ++current_time; // Update last used time
                break;
            }
        }

        if (!present) {
            // Page fault occurred
            page_faults++;

            // Find the least recently used page
            int lru_index = 0;
            for (int j = 1; j < capacity; j++) {
                if (time[j] < time[lru_index]) {
                    lru_index = j;
                }
            }

            frames[lru_index] = reference_string[i];
            time[lru_index] = ++current_time; // Update last used time
        }

        // Print current state of frames
        printf("Reference: %d | Frames: ", reference_string[i]);
        for (int j = 0; j < capacity; j++) {
            printf("%d ", frames[j]);
        }
        printf("| Page Fault: %s\n", present ? "No" : "Yes");
    }

    return page_faults;
}

// Function to implement Optimal page replacement algorithm
int optimal(int reference_string[], int n, int capacity) {
    int frames[capacity];
    int page_faults = 0;
    bool present;

    // Initialize frames with -1 (indicating empty)
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    printf("Optimal Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        present = false;

        // Check if page is already in frame
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == reference_string[i]) {
                present = true;
                break;
            }
        }

        if (!present) {
            // Page fault occurred
            page_faults++;

            // Find the page to replace
            int farthest = -1;
            int replace_index = -1;
            for (int j = 0; j < capacity; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == reference_string[k]) {
                        if (k > farthest) {
                            farthest = k;
                            replace_index = j;
                        }
                        break;
                    }
                }
                if (k == n) {
                    // Page will not be used in the future
                    replace_index = j;
                    break;
                }
            }

            // If frames are initially empty, replace the first one
            if (replace_index == -1) {
                for (int j = 0; j < capacity; j++) {
                    if (frames[j] == -1) {
                        replace_index = j;
                        break;
                    }
                }
                if (replace_index == -1) replace_index = 0;
            }


            frames[replace_index] = reference_string[i];
        }

        // Print current state of frames
        printf("Reference: %d | Frames: ", reference_string[i]);
        for (int j = 0; j < capacity; j++) {
            printf("%d ", frames[j]);
        }
        printf("| Page Fault: %s\n", present ? "No" : "Yes");
    }

    return page_faults;
}

int main() {
    int reference_string[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 3};
    int n = sizeof(reference_string) / sizeof(reference_string[0]);
    int capacity = 3;

    int fcfs_faults = fcfs(reference_string, n, capacity);
    printf("\nFCFS Total Page Faults: %d\n", fcfs_faults);

    int lru_faults = lru(reference_string, n, capacity);
    printf("\nLRU Total Page Faults: %d\n", lru_faults);

    int optimal_faults = optimal(reference_string, n, capacity);
    printf("\nOptimal Total Page Faults: %d\n", optimal_faults);

    return 0;
}
