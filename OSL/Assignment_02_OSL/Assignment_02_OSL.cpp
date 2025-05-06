#include <iostream>
#include <cstdio>
#include <climits>
#include <queue>
using namespace std;

struct Process {
    int id, at, bt, remaining_bt, ct, pr;
    float wt, tat;
    bool in_queue;
};

Process p[10];
int n, timeq;

void input(int ch) {
    cout << "Enter number of processes: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Arrival Time of P" << p[i].id << ": ";
        cin >> p[i].at;
        cout << "Burst Time of P" << p[i].id << ": ";
        cin >> p[i].bt;
        p[i].remaining_bt = p[i].bt;
        p[i].in_queue = false;
        if (ch == 4 || ch == 5) {
            cout << "Priority of P" << p[i].id << ": ";
            cin >> p[i].pr;
        }
    }
    if (ch == 6) {
        cout << "Enter Time Quantum: ";
        cin >> timeq;
    }
}

void display() {
    // Sort by PID for display
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (p[j].id > p[j+1].id) {
                swap(p[j], p[j+1]);
            }
        }
    }

    float total_tat = 0, total_wt = 0;
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        printf("P%d\t%d\t%d\t%d\t%.1f\t%.1f\n", 
              p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("Avg TAT = %.2f, Avg WT = %.2f\n", total_tat / n, total_wt / n);
}

void fcfs() {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (p[j].at > p[j+1].at || (p[j].at == p[j+1].at && p[j].id > p[j+1].id)) {
                swap(p[j], p[j+1]);
            }
        }
    }
    
    int t = 0;
    for (int i = 0; i < n; i++) {
        if (t < p[i].at) t = p[i].at;
        p[i].ct = t + p[i].bt;
        t = p[i].ct;
    }
}

void sjf(bool preemptive) {
    int t = 0, done = 0;
    bool complete[10] = {false};
    
    while (done < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (!complete[i] && p[i].at <= t && p[i].remaining_bt > 0) {
                if (idx == -1 || 
                    p[i].remaining_bt < p[idx].remaining_bt || 
                    (p[i].remaining_bt == p[idx].remaining_bt && 
                     (p[i].at < p[idx].at || (p[i].at == p[idx].at && p[i].id < p[idx].id)))) {
                    idx = i;
                }
            }
        }
        
        if (idx == -1) {
            t++;
        } else {
            if (preemptive) {
                p[idx].remaining_bt--;
                t++;
                if (p[idx].remaining_bt == 0) {
                    p[idx].ct = t;
                    complete[idx] = true;
                    done++;
                }
            } else {
                t += p[idx].bt;
                p[idx].ct = t;
                complete[idx] = true;
                done++;
            }
        }
    }
}

void priority(bool preemptive) {
    int t = 0, done = 0;
    bool complete[10] = {false};
    
    while (done < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (!complete[i] && p[i].at <= t && p[i].remaining_bt > 0) {
                if (idx == -1 || 
                    p[i].pr < p[idx].pr || 
                    (p[i].pr == p[idx].pr && 
                     (p[i].at < p[idx].at || (p[i].at == p[idx].at && p[i].id < p[idx].id)))) {
                    idx = i;
                }
            }
        }
        
        if (idx == -1) {
            t++;
        } else {
            if (preemptive) {
                p[idx].remaining_bt--;
                t++;
                if (p[idx].remaining_bt == 0) {
                    p[idx].ct = t;
                    complete[idx] = true;
                    done++;
                }
            } else {
                t += p[idx].bt;
                p[idx].ct = t;
                complete[idx] = true;
                done++;
            }
        }
    }
}

void round_robin() {
    // Sort by arrival time first
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (p[j].at > p[j+1].at) {
                swap(p[j], p[j+1]);
            }
        }
    }

    queue<int> readyQueue;
    int currentTime = 0;
    int completed = 0;

    // Initialize queue with processes arriving at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].at <= currentTime) {
            readyQueue.push(i);
            p[i].in_queue = true;
        }
    }

    while (!readyQueue.empty()) {
        int idx = readyQueue.front();
        readyQueue.pop();
        p[idx].in_queue = false;

        int execTime = min(p[idx].remaining_bt, timeq);
        currentTime += execTime;
        p[idx].remaining_bt -= execTime;

        // Add newly arrived processes
        for (int i = 0; i < n; i++) {
            if (!p[i].in_queue && p[i].remaining_bt > 0 && p[i].at <= currentTime) {
                readyQueue.push(i);
                p[i].in_queue = true;
            }
        }

        // Requeue if not completed
        if (p[idx].remaining_bt > 0) {
            readyQueue.push(idx);
            p[idx].in_queue = true;
        } else {
            p[idx].ct = currentTime;
            completed++;
        }

        // Handle idle time between processes
        if (readyQueue.empty() && completed < n) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (p[i].remaining_bt > 0 && p[i].at > currentTime) {
                    nextArrival = min(nextArrival, p[i].at);
                }
            }
            if (nextArrival != INT_MAX) {
                currentTime = nextArrival;
                for (int i = 0; i < n; i++) {
                    if (p[i].at <= currentTime && !p[i].in_queue && p[i].remaining_bt > 0) {
                        readyQueue.push(i);
                        p[i].in_queue = true;
                    }
                }
            }
        }
    }
}

int main() {
    int ch;
    cout << "1.FCFS 2.SJF(NP) 3.SJF(P) 4.Priority(P) 5.Priority(NP) 6.RR\nChoice: ";
    cin >> ch;
    input(ch);
    
    switch (ch) {
        case 1: fcfs(); break;
        case 2: sjf(false); break;
        case 3: sjf(true); break;
        case 4: priority(true); break;
        case 5: priority(false); break;
        case 6: round_robin(); break;
    }
    
    display();
    return 0;
}