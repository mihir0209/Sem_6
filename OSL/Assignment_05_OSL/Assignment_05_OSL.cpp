#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m, count = 0;
    printf("Processes and resources: ");
    scanf("%d %d", &n, &m);

    int alloc[n][m], max[n][m], need[n][m], avail[m], work[m], seq[n];
    bool finish[n];

    printf("Allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
        work[i] = avail[i];
    }

    for (int i = 0; i < n; i++) {
        finish[i] = false;
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canRun = true;
                for (int j = 0; j < m; j++)
                    if (need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                if (canRun) {
                    printf("P%d executes\n", i);
                    printf("Before: "); for (int k = 0; k < m; k++) printf("%d ", work[k]); printf("\n");
                    for (int j = 0; j < m; j++) work[j] += alloc[i][j];
                    printf("After:  "); for (int k = 0; k < m; k++) printf("%d ", work[k]); printf("\n\n");
                    seq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) return printf("Not safe\n"), 0;
    }

    printf("Safe sequence: ");
    for (int i = 0; i < n; i++) printf("P%d ", seq[i]);
    printf("\n");
}