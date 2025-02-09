#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <string.h> 
 
int main() { 
    int choice; 
    char searchTerm[100]; 
    pid_t pid; 
 
    printf("Select an option:\n"); 
    printf("1. Copy a file (cp)\n"); 
    printf("2. Search in file (grep)\n"); 
    printf("Enter choice: "); 
    scanf("%d", &choice); 
    getchar();  
    if (choice == 1) { 
        pid = fork(); 
        if (pid == -1) { 
            perror("fork failed"); 
            exit(1); 
        } 
        if (pid == 0) { 
            printf("Child (pid: %d) executing cp command\n", getpid()); 
            execl("/bin/cp", "cp", "source.txt", "destination.txt", (char *)NULL); 
            perror("execl failed"); 
            exit(1); 
        } else { 
            wait(NULL); 
            printf("Parent (pid: %d) cp process finished\n", getpid()); 
        } 
    } else if (choice == 2) { 
        printf("Enter search term: "); 
        fgets(searchTerm, sizeof(searchTerm), stdin); 
        searchTerm[strcspn(searchTerm, "\n")] = 0; 
        pid = fork(); 
        if (pid == -1) { 
            perror("fork failed"); 
            exit(1); 
        } 
        if (pid == 0) { 
            printf("Child (pid: %d) executing grep command\n", getpid()); 
            execl("/bin/grep", "grep", searchTerm, "file.txt", (char *)NULL); 
            perror("execl failed"); 
            exit(1); 
        } else { 
            wait(NULL); 
            printf("Parent (pid: %d) grep process finished\n", getpid()); 
        } 
    } else { 
        printf("Invalid choice!\n"); 
    } 
    return 0; 
} 
  
