#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
void copy_file(const char *source, const char *destination) {
    FILE *src = fopen(source, "r");
    if (!src) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }
    FILE *dest = fopen(destination, "w");
    if (!dest) {
        perror("Error opening destination file");
        fclose(src);
        exit(EXIT_FAILURE);
    }
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }
    fclose(src);
    fclose(dest);
    printf("File copied successfully.\n");
}
void grep_in_file(const char *filename, const char *search_term) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, search_term)) {
            printf("%s", line);
        }
    }
    fclose(file);
}
int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <command> <args>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Child Process: PID = %d\n", getpid());
        if (strcmp(argv[1], "cp") == 0 && argc == 4) {
            copy_file(argv[2], argv[3]);
        } else if (strcmp(argv[1], "grep") == 0 && argc == 4) {
            grep_in_file(argv[3], argv[2]);
        } else {
            fprintf(stderr, "Invalid command or arguments\n");
        }
        exit(EXIT_SUCCESS);
    } else {
        printf("Parent Process: PID = %d, waiting for child to finish...\n", getpid());
        wait(NULL);
        printf("Child process finished execution.\n");
    }
    return 0;
}
