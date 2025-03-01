#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);
    
    int allocation[n][m], max[n][m], need[n][m], available[m];
    bool finish[n];
    
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    
    printf("Enter the max matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("Enter the available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
        finish[i] = false;
    }
    
    printf("\nInitial Available Resources:\n");
    for (int i = 0; i < m; i++) {
        printf("%d ", available[i]);
    }
    printf("\n\n");
    
    int safeSequence[n];
    int count = 0;
    int work[m];
    
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }
    
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                
                if (j == m) {
                    printf("Process P%d is executing.\n", i);
                    printf("Available resources before execution: ");
                    for (int k = 0; k < m; k++) {
                        printf("%d ", work[k]);
                    }
                    printf("\n");
                    
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }
                    
                    printf("Available resources after execution: ");
                    for (int k = 0; k < m; k++) {
                        printf("%d ", work[k]);
                    }
                    printf("\n\n");
                    
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        
        if (!found) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }
    
    printf("System is in a safe state. Safe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    
    return 0;
}
