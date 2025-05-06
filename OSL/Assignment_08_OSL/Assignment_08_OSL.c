#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int abs_diff(int a, int b) {
    return a > b ? a - b : b - a;
}

void fcfs(int req[], int n, int head) {
    int total = 0;
    printf("FCFS Seek Sequence: %d ", head);
    for (int i = 0; i < n; i++) {
        total += abs_diff(head, req[i]);
        head = req[i];
        printf("%d ", head);
    }
    printf("\nTotal Head Movement: %d\n", total);
}

void sstf(int req[], int n, int head) {
    int total = 0, done = 0, min_idx, min_dist;
    bool visited[n];
    for (int i = 0; i < n; i++) visited[i] = false;

    printf("SSTF Seek Sequence: %d ", head);
    while (done < n) {
        min_dist = 1e9;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && abs_diff(head, req[i]) < min_dist) {
                min_dist = abs_diff(head, req[i]);
                min_idx = i;
            }
        }
        total += min_dist;
        head = req[min_idx];
        visited[min_idx] = true;
        printf("%d ", head);
        done++;
    }
    printf("\nTotal Head Movement: %d\n", total);
}

void sort(int arr[], int n, bool asc) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if ((asc && arr[j] > arr[j+1]) || (!asc && arr[j] < arr[j+1])) {
                int t = arr[j]; arr[j] = arr[j+1]; arr[j+1] = t;
            }
}

void scan(int req[], int n, int head, int size, char dir) {
    int left[n], right[n], lc = 0, rc = 0, total = 0;
    for (int i = 0; i < n; i++) 
        if (req[i] < head)
            left[lc++] = req[i];
        else
            right[rc++] = req[i];


    sort(left, lc, false); sort(right, rc, true);
    printf("SCAN Seek Sequence: %d ", head);
    
    int *first = (dir == 'l') ? left : right, fc = (dir == 'l') ? lc : rc;
    int *second = (dir == 'l') ? right : left, sc = (dir == 'l') ? rc : lc;

    for (int i = 0; i < fc; i++) {
        total += abs_diff(head, first[i]);
        head = first[i];
        printf("%d ", head);
    }

    int end = (dir == 'l') ? 0 : size - 1;
    total += abs_diff(head, end);
    head = end;
    printf("%d ", head);

    for (int i = 0; i < sc; i++) {
        total += abs_diff(head, second[i]);
        head = second[i];
        printf("%d ", head);
    }

    printf("\nTotal Head Movement: %d\n", total);
}

void c_scan(int req[], int n, int head, int size, char dir) {
    int left[n], right[n], lc = 0, rc = 0, total = 0;
    for (int i = 0; i < n; i++) 
        if (req[i] < head)
            left[lc++] = req[i];
        else
            right[rc++] = req[i];


    sort(left, lc, false); sort(right, rc, true);
    printf("C-SCAN Seek Sequence: %d ", head);

    if (dir == 'l') {
        for (int i = 0; i < lc; i++) {
            total += abs_diff(head, left[i]);
            head = left[i];
            printf("%d ", head);
        }
        total += abs_diff(head, 0) + abs_diff(0, size - 1);
        head = size - 1;
        printf("0 %d ", size - 1);
        for (int i = 0; i < rc; i++) {
            total += abs_diff(head, right[i]);
            head = right[i];
            printf("%d ", head);
        }
    } else {
        for (int i = 0; i < rc; i++) {
            total += abs_diff(head, right[i]);
            head = right[i];
            printf("%d ", head);
        }
        total += abs_diff(head, size - 1) + abs_diff(0, size - 1);
        head = 0;
        printf("%d 0 ", size - 1);
        for (int i = 0; i < lc; i++) {
            total += abs_diff(head, left[i]);
            head = left[i];
            printf("%d ", head);
        }
    }

    printf("\nTotal Head Movement: %d\n", total);
}

int main() {
    int n, head, size, choice;
    char dir;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int req[n];
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size: ");
    scanf("%d", &size);
    printf("Direction (l/r) for SCAN and C-SCAN: ");
    scanf(" %c", &dir);

    while (1) {
        printf("\nMenu:\n1.FCFS\n2.SSTF\n3.SCAN\n4.C-SCAN\n5.Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: fcfs(req, n, head); break;
            case 2: sstf(req, n, head); break;
            case 3: scan(req, n, head, size, dir); break;
            case 4: c_scan(req, n, head, size, dir); break;
            case 5: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
