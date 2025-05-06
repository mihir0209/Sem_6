#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Block {
    int start, size;
    bool free;
    struct Block *next;
} Block;

Block *mem = NULL, *next_fit_ptr = NULL;

Block* create(int size, bool free) {
    Block *b = malloc(sizeof(Block));
    b->size = size; b->free = free; b->next = NULL; b->start = 0;
    return b;
}

void update(Block *head) {
    int addr = 0;
    while (head) {
        head->start = addr;
        addr += head->size;
        head = head->next;
    }
}

void show(Block *head) {
    puts("\nMemory:");
    for (; head; head = head->next)
        printf("%d %d %s\n", head->start, head->size, head->free ? "Free" : "Used");
}

int alloc(Block **head, int size, char mode) {
    Block *sel = NULL, *cur = *head, *start = NULL;
    int best = (mode == 'B') ? __INT_MAX__ : -1;
    bool loop = false;

    if (mode == 'N') start = cur = next_fit_ptr ? next_fit_ptr : *head;

    do {
        if (cur->free && cur->size >= size) {
            if (mode == 'F') { sel = cur; break; }
            if (mode == 'B' && cur->size < best) { sel = cur; best = cur->size; }
            if (mode == 'W' && cur->size > best) { sel = cur; best = cur->size; }
            if (mode == 'N') { sel = cur; break; }
        }
        cur = (mode == 'N') ? (cur->next ? cur->next : *head) : cur->next;
        if (mode == 'N' && cur == start) loop = true;
    } while ((mode != 'N' && cur) || (mode == 'N' && !loop));

    if (!sel) return -1;

    int addr = sel->start;
    if (sel->size == size) sel->free = false;
    else {
        Block *b = create(sel->size - size, true);
        b->next = sel->next;
        sel->next = b;
        sel->size = size;
        sel->free = false;
        update(*head);
    }
    if (mode == 'N') next_fit_ptr = sel->next ? sel->next : *head;
    return addr;
}

bool dealloc(Block **head, int addr) {
    Block *cur = *head, *prev = NULL;
    while (cur) {
        if (cur->start == addr) {
            cur->free = true;
            if (cur->next && cur->next->free) {
                Block *t = cur->next;
                cur->size += t->size;
                cur->next = t->next;
                free(t);
            }
            if (prev && prev->free) {
                prev->size += cur->size;
                prev->next = cur->next;
                free(cur);
                cur = prev;
            }
            update(*head);
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

void cleanup(Block *head) {
    while (head) {
        Block *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    int mem_size, blocks, ch, *sizes, size, addr;
    char mode;

    printf("Mem Size Blocks: ");
    scanf("%d %d", &mem_size, &blocks);

    sizes = malloc(sizeof(int) * blocks);
    for (int i = 0; i < blocks; i++) scanf("%d", &sizes[i]);

    for (int i = 0; i < blocks; i++) {
        Block *b = create(sizes[i], true);
        if (!mem) mem = b;
        else {
            Block *last = mem;
            while (last->next) last = last->next;
            last->next = b;
        }
    }
    update(mem);
    free(sizes);

    printf("Method (F/B/W/N): ");
    scanf(" %c", &mode);

    while (1) {
        printf("\n1:Alloc 2:Free 3:Show 0:Exit > ");
        scanf("%d", &ch);
        if (ch == 0) break;
        if (ch == 1) {
            scanf("%d", &size);
            addr = alloc(&mem, size, mode);
            printf(addr == -1 ? "Fail\n" : "At %d\n", addr);
        } else if (ch == 2) {
            scanf("%d", &addr);
            printf(dealloc(&mem, addr) ? "Freed\n" : "Invalid\n");
        } else if (ch == 3) {
            show(mem);
        }
    }
    cleanup(mem);
    return 0;
}
