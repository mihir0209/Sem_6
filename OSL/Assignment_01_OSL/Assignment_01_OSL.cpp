#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

void copy_file(const string &source, const string &destination) {
    ifstream src(source, ios::binary);
    if (!src.is_open()) {
        perror("Error opening source file");
        exit(EXIT_FAILURE); 
    }

    ofstream dest(destination, ios::binary);
    if (!dest.is_open()) {
        perror("Error opening destination file");
        src.close();
        exit(EXIT_FAILURE);
    }

    dest << src.rdbuf();

    src.close();
    dest.close();

    cout << "File copied successfully." << endl;
}

void grep_in_file(const string &filename, const string &search_term) {
    ifstream file(filename);
    if (!file.is_open()) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    string line;
    while (getline(file, line)) {
        if (line.find(search_term) != string::npos) {
            cout << line << endl;
        }
    }

    file.close();
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <command> <args>\n"
             << " 1. " << argv[0] << " cp source.txt destination.txt\n"
             << " 2. " << argv[0] << " grep search_text source.txt\n";
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        // Child process
        cout << "Child Process: PID = " << getpid() << endl;
        if (strcmp(argv[1], "cp") == 0 && argc == 4) {
            copy_file(argv[2], argv[3]);
        } else if (strcmp(argv[1], "grep") == 0 && argc == 4) {
            grep_in_file(argv[3], argv[2]);
        } else {
            cerr << "Invalid command or arguments" << endl;
        }
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        cout << "Parent Process: PID = " << getpid() << ", waiting for child to finish..." << endl;
        wait(nullptr);
        cout << "Child process finished execution." << endl;
    }

    return 0;
}