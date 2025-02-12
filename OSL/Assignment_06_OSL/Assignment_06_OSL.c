#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct MemoryBlock {
    int start_address;
    int size;
    bool is_free;
    struct MemoryBlock* next;
} MemoryBlock;
MemoryBlock* createMemoryBlock(int start_address, int size, bool is_free) {
    MemoryBlock* block = (MemoryBlock*)malloc(sizeof(MemoryBlock));
    if (block == NULL) {
        perror("Failed to allocate memory for block");
        exit(EXIT_FAILURE);
    }
    block->start_address = start_address;
    block->size = size;
    block->is_free = is_free;
    block->next = NULL;
    return block;
}
void displayMemory(MemoryBlock* head) {
    MemoryBlock* current = head;
    while (current != NULL) {
        printf("Block(start=%d, size=%d, free=%s)\n", current->start_address, current->size, current->is_free ? "true" : "false");
        current = current->next;
    }
}
int firstFit(MemoryBlock* head, int process_size) {
    MemoryBlock* current = head;
    while (current != NULL) {
        if (current->is_free && current->size >= process_size) {
            int start_address = current->start_address;
            if (current->size == process_size) {
                current->is_free = false;
            } else {
                MemoryBlock* new_block = createMemoryBlock(current->start_address + process_size, current->size - process_size, true);
                new_block->next = current->next;
                current->next = new_block;
                current->size = process_size;
                current->is_free = false;
            }
            return start_address;
        }
        current = current->next;
    }
    return -1;
}
int bestFit(MemoryBlock* head, int process_size) {
    MemoryBlock* current = head;
    MemoryBlock* best_block = NULL;
    int min_size = __INT_MAX__;
    while (current != NULL) {
        if (current->is_free && current->size >= process_size && current->size < min_size) {
            best_block = current;
            min_size = current->size;
        }
        current = current->next;
    }
    if (best_block != NULL) {
        int start_address = best_block->start_address;
        if (best_block->size == process_size) {
            best_block->is_free = false;
        } else {
            MemoryBlock* new_block = createMemoryBlock(best_block->start_address + process_size, best_block->size - process_size, true);
            new_block->next = best_block->next;
            best_block->next = new_block;
            best_block->size = process_size;
            best_block->is_free = false;
        }
        return start_address;
    }
    return -1;
}
int worstFit(MemoryBlock* head, int process_size) {
    MemoryBlock* current = head;
    MemoryBlock* worst_block = NULL;
    int max_size = 0;
    while (current != NULL) {
        if (current->is_free && current->size >= process_size && current->size > max_size) {
            worst_block = current;
            max_size = current->size;
        }
        current = current->next;
    }
    if (worst_block != NULL) {
        int start_address = worst_block->start_address;
        if (worst_block->size == process_size) {
            worst_block->is_free = false;
        } else {
            MemoryBlock* new_block = createMemoryBlock(worst_block->start_address + process_size, worst_block->size - process_size, true);
            new_block->next = worst_block->next;
            worst_block->next = new_block;
            worst_block->size = process_size;
            worst_block->is_free = false;
        }
        return start_address;
    }
    return -1;
}
bool freeBlock(MemoryBlock* head, int start_address) {
    MemoryBlock* current = head;
    while (current != NULL) {
        if (current->start_address == start_address) {
            current->is_free = true;
            if (current->next != NULL && current->next->is_free) {
                current->size += current->next->size;
                MemoryBlock* temp = current->next;
                current->next = current->next->next;
                free(temp);
            }
            MemoryBlock* prev = head;
            if (head != current) {
                while (prev->next != current) {
                    prev = prev->next;
                }
                if (prev->is_free) {
                    prev->size += current->size;
                    prev->next = current->next;
                    free(current);
                    current = prev;
                }
            }
            return true;
        }
        current = current->next;
    }
    return false;
}
void deallocateMemory(MemoryBlock* head) {
    MemoryBlock* current = head;
    MemoryBlock* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
int main() {
    int memory_size = 200;
    MemoryBlock* memory = createMemoryBlock(0, memory_size, true);
    printf("Initial Memory:\n");
    displayMemory(memory);
    int p1_address = firstFit(memory, 40);
    if (p1_address != -1) {
        printf("Allocated 40MB to P1 at address %d\n", p1_address);
    } else {
        printf("Failed to allocate 40MB to P1\n");
    }
    printf("Memory after P1 allocation:\n");
    displayMemory(memory);
    printf("\n");
    int p2_address = bestFit(memory, 80);
    if (p2_address != -1) {
        printf("Allocated 80MB to P2 at address %d\n", p2_address);
    } else {
        printf("Failed to allocate 80MB to P2\n");
    }
    printf("Memory after P2 allocation:\n");
    displayMemory(memory);
    printf("\n");
    int p3_address = worstFit(memory, 20);
    if (p3_address != -1) {
        printf("Allocated 20MB to P3 at address %d\n", p3_address);
    } else {
        printf("Failed to allocate 20MB to P3\n");
    }
    printf("Memory after P3 allocation:\n");
    displayMemory(memory);
    printf("\n");
    freeBlock(memory, 0);
    printf("After freeing P1:\n");
    displayMemory(memory);
    deallocateMemory(memory);
    return 0;
}
