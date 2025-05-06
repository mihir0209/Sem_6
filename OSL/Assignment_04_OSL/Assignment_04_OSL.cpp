#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
using namespace std;

#define MAX 50

string sharedData = "Nothing written yet.";
int readCount = 0;
sem_t mutex, writeLock;

void* reader(void* arg) {
    int id = *(int*)arg;
    while (true) {
        sleep(rand() % 5 + 1); // Random delay

        sem_wait(&mutex);
        readCount++;
        if (readCount == 1) sem_wait(&writeLock);
        sem_post(&mutex);

        cout << "\n[Reader " << id << "] Reading: " << sharedData << endl;

        sem_wait(&mutex);
        readCount--;
        if (readCount == 0) sem_post(&writeLock);
        sem_post(&mutex);
    }
    return nullptr;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    while (true) {
        sleep(rand() % 5 + 1); // Random delay

        sem_wait(&writeLock);
        string input;
        cout << "\n[Writer " << id << "] Enter data to write: ";
        getline(cin, input); // Manual user input
        sharedData = "[Writer " + to_string(id) + "] " + input;
        cout << "[Writer " << id << "] Wrote: " << sharedData << endl;
        sem_post(&writeLock);
    }
    return nullptr;
}

int main() {
    srand(time(0));
    int readers, writers;
    cout << "Enter number of readers: "; cin >> readers;
    cout << "Enter number of writers: "; cin >> writers;
    cin.ignore(); // Clear input buffer for getline

    pthread_t rthreads[MAX], wthreads[MAX];
    int ids[MAX];

    sem_init(&mutex, 0, 1);
    sem_init(&writeLock, 0, 1);

    for (int i = 0; i < max(readers, writers); ++i) ids[i] = i + 1;
    for (int i = 0; i < readers; ++i)
        pthread_create(&rthreads[i], NULL, reader, &ids[i]);
    for (int i = 0; i < writers; ++i)
        pthread_create(&wthreads[i], NULL, writer, &ids[i]);

    for (int i = 0; i < readers; ++i)
        pthread_join(rthreads[i], NULL);
    for (int i = 0; i < writers; ++i)
        pthread_join(wthreads[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&writeLock);
    return 0;
}
