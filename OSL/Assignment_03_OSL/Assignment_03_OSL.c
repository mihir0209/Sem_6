#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void child_process(int write_fd) {
    char message[] = "Hello from Child Process!";
    write(write_fd, message, sizeof(message));
    close(write_fd);
    exit(0);
}
void parent_process() {
    int pipe_fd[2];
    char buffer[100];
    if (pipe(pipe_fd) == -1) {
        perror("Pipe failed");
        exit(1);
    }
    pid_t pid = fork();
    if (pid > 0) {
        close(pipe_fd[1]);
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
        close(pipe_fd[0]);
    } else if (pid == 0) {
        close(pipe_fd[0]);
        child_process(pipe_fd[1]);
    } else {
        perror("Fork failed");
        exit(1);
    }
}
int main() {
    parent_process();
    return 0;
}
