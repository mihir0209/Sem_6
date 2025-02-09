#include <stdio.h>
#include <stdlib.h>
// This is wrong for now... Don't refer to the Round Robin algorithm
int main() {
    int n, i, j, quantum, choice;
    int total_wt = 0, total_tat = 0;
    int t = 0, done;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], waiting_time[n], turnaround_time[n], priority[n], remaining_time[n];
    printf("Enter burst times of %d processes: ", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &burst_time[i]);
        processes[i] = i + 1;
    }

    printf("Choose Scheduling Algorithm:\n1. FCFS\n2. SJF\n3. Round Robin\n4. Priority\nEnter choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: // FCFS
            waiting_time[0] = 0;
            for(i = 1; i < n; i++) {
                waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
            }
            for(i = 0; i < n; i++) {
                turnaround_time[i] = burst_time[i] + waiting_time[i];
            }
            printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
            for(i = 0; i < n; i++) {
                total_wt += waiting_time[i];
                total_tat += turnaround_time[i];
                printf("%d\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);
            }
            printf("\nAverage Waiting Time: %.2f", (float)total_wt/n);
            printf("\nAverage Turnaround Time: %.2f", (float)total_tat/n);
            break;

        case 2: // SJF
            for(i = 0; i < n; i++) {
                for(j = i + 1; j < n; j++) {
                    if(burst_time[i] > burst_time[j]) {
                        int temp = burst_time[i];
                        burst_time[i] = burst_time[j];
                        burst_time[j] = temp;
                        temp = processes[i];
                        processes[i] = processes[j];
                        processes[j] = temp;
                    }
                }
            }
            waiting_time[0] = 0;
            for(i = 1; i < n; i++) {
                waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
            }
            for(i = 0; i < n; i++) {
                turnaround_time[i] = burst_time[i] + waiting_time[i];
            }
            printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
            for(i = 0; i < n; i++) {
                total_wt += waiting_time[i];
                total_tat += turnaround_time[i];
                printf("%d\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);
            }
            printf("\nAverage Waiting Time: %.2f", (float)total_wt/n);
            printf("\nAverage Turnaround Time: %.2f", (float)total_tat/n);
            break;

        case 3: // Round Robin
            printf("Enter time quantum: ");
            scanf("%d", &quantum);
            for(i = 0; i < n; i++) {
                remaining_time[i] = burst_time[i];
            }
            while(1) {
                done = 1;
                for(i = 0; i < n; i++) {
                    if(remaining_time[i] > 0) {
                        done = 0;
                        if(remaining_time[i] > quantum) {
                            t += quantum;
                            remaining_time[i] -= quantum;
                        } else {
                            t += remaining_time[i];
                            waiting_time[i] = t - burst_time[i];
                            remaining_time[i] = 0;
                        }
                    }
                }
                if(done == 1) break;
            }
            for(i = 0; i < n; i++) {
                turnaround_time[i] = burst_time[i] + waiting_time[i];
            }
            printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
            for(i = 0; i < n; i++) {
                total_wt += waiting_time[i];
                total_tat += turnaround_time[i];
                printf("%d\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);
            }
            printf("\nAverage Waiting Time: %.2f", (float)total_wt/n);
            printf("\nAverage Turnaround Time: %.2f", (float)total_tat/n);
            break;

        case 4: // Priority
            printf("Enter priorities of %d processes: ", n);
            for(i = 0; i < n; i++) {
                scanf("%d", &priority[i]);
            }
            for(i = 0; i < n; i++) {
                for(j = i + 1; j < n; j++) {
                    if(priority[i] > priority[j]) {
                        int temp = priority[i];
                        priority[i] = priority[j];
                        priority[j] = temp;
                        temp = burst_time[i];
                        burst_time[i] = burst_time[j];
                        burst_time[j] = temp;
                        temp = processes[i];
                        processes[i] = processes[j];
                        processes[j] = temp;
                    }
                }
            }
            waiting_time[0] = 0;
            for(i = 1; i < n; i++) {
                waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
            }
            for(i = 0; i < n; i++) {
                turnaround_time[i] = burst_time[i] + waiting_time[i];
            }
            printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
            for(i = 0; i < n; i++) {
                total_wt += waiting_time[i];
                total_tat += turnaround_time[i];
                printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], priority[i], waiting_time[i], turnaround_time[i]);
            }
            printf("\nAverage Waiting Time: %.2f", (float)total_wt/n);
            printf("\nAverage Turnaround Time: %.2f", (float)total_tat/n);
            break;

        default:
            printf("Invalid choice!\n");
            break;
    }
    return 0;
}
