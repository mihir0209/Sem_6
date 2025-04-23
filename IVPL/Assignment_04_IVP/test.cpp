#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class BankersAlgorithm {
private:
    int processes, resources;
    vector<vector<int>> allocation, maxNeed, need;
    vector<int> available;
    
public:
    void input();
    void calculateNeed();
    void displayTables();
    bool isSafe();
};

void BankersAlgorithm::input() {
    cout << "Enter number of processes: ";
    cin >> processes;
    cout << "Enter number of resources: ";
    cin >> resources;

    allocation.resize(processes, vector<int>(resources));
    maxNeed.resize(processes, vector<int>(resources));
    need.resize(processes, vector<int>(resources));
    available.resize(resources);

    cout << "Enter maximum need matrix:\n";
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            cin >> maxNeed[i][j];
        }
    }
    
    cout << "Enter allocation matrix:\n";
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter available resources: ";
    for (int i = 0; i < resources; i++) {
        cin >> available[i];
    }
}

void BankersAlgorithm::calculateNeed() {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }
    }
}

void BankersAlgorithm::displayTables() {
    cout << "\nAllocation Matrix:" << endl;
    cout << "    ";
    for (int j = 0; j < resources; j++) cout << "R" << j << "  ";
    cout << endl;
    for (int i = 0; i < processes; i++) {
        cout << "P" << i << "  ";
        for (int j = 0; j < resources; j++) {
            cout << setw(2) << allocation[i][j] << "  ";
        }
        cout << endl;
    }
    
    cout << "\nMaximum Need Matrix:" << endl;
    cout << "    ";
    for (int j = 0; j < resources; j++) cout << "R" << j << "  ";
    cout << endl;
    for (int i = 0; i < processes; i++) {
        cout << "P" << i << "  ";
        for (int j = 0; j < resources; j++) {
            cout << setw(2) << maxNeed[i][j] << "  ";
        }
        cout << endl;
    }

    cout << "\nNeed Matrix:" << endl;
    cout << "    ";
    for (int j = 0; j < resources; j++) cout << "R" << j << "  ";
    cout << endl;
    for (int i = 0; i < processes; i++) {
        cout << "P" << i << "  ";
        for (int j = 0; j < resources; j++) {
            cout << setw(2) << need[i][j] << "  ";
        }
        cout << endl;
    }

    cout << "\nAvailable Resources: ";
    for (int j = 0; j < resources; j++) {
        cout << "R" << j << ": " << available[j] << "  ";
    }
    cout << endl;
}

bool BankersAlgorithm::isSafe() {
    vector<int> work = available;
    vector<bool> finish(processes, false);
    vector<int> safeSequence;
    int count = 0;

    while (count < processes) {
        bool found = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence.push_back(i);
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            cout << "\nThe system is in an unsafe state! Deadlock is possible.\n";
            return false;
        }
    }
    cout << "\nSystem is in a safe state. Safe sequence: ";
    for (int i = 0; i < processes; i++) {
        cout << "P" << safeSequence[i] << " ";
    }
    cout << endl;
    return true;
}

int main() {
    BankersAlgorithm ba;
    ba.input();
    ba.calculateNeed();
    ba.displayTables();
    ba.isSafe();
    return 0;
}