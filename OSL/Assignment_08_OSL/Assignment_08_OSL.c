#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int abs_diff(int a, int b) {
    return abs(a - b);
}
void fcfs(int requests[], int n, int head) {
    int total_movement = 0;
    int current_position = head;
    printf("FCFS Seek Sequence: %d ", head);
    for (int i = 0; i < n; i++) {
        total_movement += abs_diff(requests[i], current_position);
        current_position = requests[i];
        printf("%d ", requests[i]);
    }
    printf("\nFCFS Total Head Movement: %d\n", total_movement);
}
void sstf(int requests[], int n, int head) {
    int total_movement = 0;
    int current_position = head;
    bool visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
    printf("SSTF Seek Sequence: %d ", head);
    for (int i = 0; i < n; i++) {
        int min_diff = 99999;
        int next_request = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int diff = abs_diff(requests[j], current_position);
                if (diff < min_diff) {
                    min_diff = diff;
                    next_request = j;
                }
            }
        }
        if (next_request != -1) {
            total_movement += min_diff;
            current_position = requests[next_request];
            visited[next_request] = true;
            printf("%d ", current_position);
        }
    }
    printf("\nSSTF Total Head Movement: %d\n", total_movement);
}
void scan(int requests[], int n, int head, int disk_size, char direction) {
    int total_movement = 0;
    int current_position = head;
    int seek_sequence[n + 2];
    int seek_count = 0;
    int left[n], right[n];
    int left_count = 0, right_count = 0;
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            left[left_count++] = requests[i];
        } else {
            right[right_count++] = requests[i];
        }
    }
    for (int i = 0; i < left_count - 1; i++) {
        for (int j = 0; j < left_count - i - 1; j++) {
            if (left[j] < left[j + 1]) {
                int temp = left[j];
                left[j] = left[j + 1];
                left[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < right_count - 1; i++) {
        for (int j = 0; j < right_count - i - 1; j++) {
            if (right[j] > right[j + 1]) {
                int temp = right[j];
                right[j] = right[j + 1];
                right[j + 1] = temp;
            }
        }
    }
    printf("SCAN Seek Sequence: %d ", head);
    if (direction == 'l') {
        for (int i = 0; i < left_count; i++) {
            total_movement += abs_diff(current_position, left[i]);
            current_position = left[i];
            printf("%d ", current_position);
        }
        total_movement += abs_diff(current_position, 0);
        current_position = 0;
        printf("%d ", current_position);
        for (int i = 0; i < right_count; i++) {
            total_movement += abs_diff(current_position, right[i]);
            current_position = right[i];
            printf("%d ", current_position);
        }
    }
    else {
        for (int i = 0; i < right_count; i++) {
            total_movement += abs_diff(current_position, right[i]);
            current_position = right[i];
            printf("%d ", current_position);
        }
        total_movement += abs_diff(current_position, disk_size - 1);
        current_position = disk_size - 1;
        printf("%d ", current_position);
        for (int i = 0; i < left_count; i++) {
            total_movement += abs_diff(current_position, left[i]);
            current_position = left[i];
            printf("%d ", current_position);
        }
    }
    printf("\nSCAN Total Head Movement: %d\n", total_movement);
}
void c_scan(int requests[], int n, int head, int disk_size, char direction) {
    int total_movement = 0;
    int current_position = head;
    int seek_sequence[n + 2];
    int seek_count = 0;
    int left[n], right[n];
    int left_count = 0, right_count = 0;
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            left[left_count++] = requests[i];
        } else {
            right[right_count++] = requests[i];
        }
    }
    for (int i = 0; i < left_count - 1; i++) {
        for (int j = 0; j < left_count - i - 1; j++) {
            if (left[j] < left[j + 1]) {
                int temp = left[j];
                left[j] = left[j + 1];
                left[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < right_count - 1; i++) {
        for (int j = 0; j < right_count - i - 1; j++) {
            if (right[j] > right[j + 1]) {
                int temp = right[j];
                right[j] = right[j + 1];
                right[j + 1] = temp;
            }
        }
    }
    printf("C-SCAN Seek Sequence: %d ", head);
    if (direction == 'l') {
        for (int i = 0; i < left_count; i++) {
            total_movement += abs_diff(current_position, left[i]);
            current_position = left[i];
            printf("%d ", current_position);
        }
        total_movement += abs_diff(current_position, 0);
        current_position = 0;
        printf("%d ", current_position);
        total_movement += abs_diff(current_position, disk_size-1);
        current_position = disk_size-1;
        printf("%d ", current_position);
        current_position = head;
        for (int i = 0; i < right_count; i++) {
            total_movement += abs_diff(current_position, right[i]);
            current_position = right[i];
            printf("%d ", current_position);
        }
    }
    else {
        for (int i = 0; i < right_count; i++) {
            total_movement += abs_diff(current_position, right[i]);
            current_position = right[i];
            printf("%d ", current_position);
        }
        total_movement += abs_diff(current_position, disk_size - 1);
        current_position = disk_size - 1;
        printf("%d ", current_position);
        total_movement += abs_diff(current_position, 0);
        current_position = 0;
        printf("%d ", current_position);
        current_position = head;
        for (int i = 0; i < left_count; i++) {
            total_movement += abs_diff(current_position, left[i]);
            current_position = left[i];
            printf("%d ", current_position);
        }
    }
    printf("\nC-SCAN Total Head Movement: %d\n", total_movement);
}
int main() {
    int n, head, disk_size;
    char direction;
    printf("Enter the number of disk I/O requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the disk I/O requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);
    printf("Enter the direction for SCAN and C-SCAN (l for left, r for right): ");
    scanf(" %c", &direction);
    printf("Disk Size: %d\n",disk_size);
    fcfs(requests, n, head);
    sstf(requests, n, head);
    scan(requests, n, head, disk_size, direction);
    c_scan(requests, n, head, disk_size, direction);
    return 0;
}
