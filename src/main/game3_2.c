#include "game.h"

/* The index of Digimon `id` among a partner's entries, or -1 */
s32 findPartnerEntry(s32 partner, s32 id) {
    s32 i;

    for (i = 0; i < PARTNER_ENTRY_COUNT; i++) {
        if (GAME.partners[partner].info.entries[i].id < FIRST_ENTRY_ID) {
            continue;
        }
        if (GAME.partners[partner].info.entries[i].id == id) {
            return i;
        }
    }
    return -1;
}

/* Copies the ids of the Digimon a partner takes to battle; returns how many there are */
s32 getPartnerSlots(s32 partner, s16 *out) {
    s32 i;
    s32 n;
    s32 index;

    for (i = 0, n = 0; i < PARTNER_SLOT_COUNT; i++) {
        if (GAME.partners[partner].info.slots[i] >= FIRST_ENTRY_ID) {
            index = findPartnerEntry(partner, GAME.partners[partner].info.slots[i]);
            if (index >= 0 && GAME.partners[partner].info.entries[index].id >= FIRST_ENTRY_ID) {
                out[n] = GAME.partners[partner].info.entries[index].id;
                n++;
            }
        }
    }
    for (i = n; i < PARTNER_SLOT_COUNT; i++) {
        out[i] = -1;
    }
    return n;
}

/* Picks the Digimon a partner takes to battle (-1 for ids it does not have) */
void setPartnerSlots(s32 partner, s16 *ids) {
    s32 i;
    s32 index;

    for (i = 0; i < PARTNER_SLOT_COUNT; i++) {
        index = findPartnerEntry(partner, ids[i]);
        if (index >= 0) {
            GAME.partners[partner].info.slots[i] = GAME.partners[partner].info.entries[index].id;
        } else {
            GAME.partners[partner].info.slots[i] = -1;
        }
    }
}

/* Copies the ids of a partner's Digimon, zero-filled; returns how many there are */
s32 listPartnerEntries(s32 partner, u16 *out) {
    s32 i;
    s32 n;
    s32 count;

    for (n = i = 0; i < PARTNER_ENTRY_COUNT; i++) {
        if (GAME.partners[partner].info.entries[i].id >= FIRST_ENTRY_ID) {
            out[n] = GAME.partners[partner].info.entries[i].id;
            n++;
        }
    }
    count = n;
    for (; n < PARTNER_ENTRY_COUNT; n++) {
        out[n] = 0;
    }
    return count;
}

/* Gives a partner Digimon `id` at level 1; 0 if it has it already or has no room */
s32 addPartnerEntry(s32 partner, s32 id) {
    s32 i;
    s32 index;

    if (findPartnerEntry(partner, id) != -1) {
        return 0;
    }
    for (i = 0, index = -1; i < PARTNER_ENTRY_COUNT; i++) {
        if (GAME.partners[partner].info.entries[i].id == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return 0;
    }
    GET_DIGIMON(id); /* its result goes unused */
    GAME.partners[partner].info.entries[index].id = id;
    GAME.partners[partner].info.entries[index].level = 1;
    return 1;
}

/* Copies a partner's Digimon `id`; returns its index, or -1 */
s32 getPartnerEntry(s32 partner, s32 id, PartnerEntry *out) {
    s32 i = findPartnerEntry(partner, id);

    if (i != -1) {
        *out = GAME.partners[partner].info.entries[i];
    }
    return i;
}

/* Overwrites a partner's Digimon `id`; returns its index, or -1 */
s32 setPartnerEntry(s32 partner, s32 id, PartnerEntry *in) {
    s32 i = findPartnerEntry(partner, id);

    if (i != -1) {
        GAME.partners[partner].info.entries[i] = *in;
    }
    return i;
}

/* A partner's name, stats and Digimon */
PartnerStats *getPartnerStats(s32 partner) {
    return &GAME.partners[partner].info;
}

/* Frees a heap block, merging it with the free blocks around it */
void freeMem(void *ptr) {
    MemBlock *block = (MemBlock *)ptr - 1;
    MemBlock *prev;
    MemBlock *next;

    if (ptr != NULL) {
        prev = block->prev;
        next = block->next;
        block->tag = MEM_FREE;
        if (next->tag == MEM_FREE) {
            block->next = next->next;
            next->next->prev = block;
        }
        if (prev->tag == MEM_FREE) {
            prev->next = block->next;
            block->next->prev = prev;
        }
    }
}

/* HEAP.nop: empty, and nothing calls it */
void heapNop(void) {
}

/* Frees every heap block with tag `tag` */
void freeMemByTag(s32 tag) {
    MemBlock *block;

    for (block = HEAP.first; block->tag != MEM_END; block = block->next) {
        if (block->tag == tag) {
            freeMem(block + 1);
        }
    }
}

/* Makes the heap one free block from HEAP_START, followed by the end marker */
void initHeap(void) {
    MemBlock *start;
    MemBlock *last;

    HEAP.end = (MemBlock *)HEAP_END;
    last = (MemBlock *)HEAP_END - 1;
    start = HEAP_START;
    HEAP.first = start;
    HEAP.size = (u8 *)HEAP_END - (u8 *)start;
    start->prev = start;
    start->next = last;
    start->tag = MEM_FREE;
    last->prev = start;
    last->tag = MEM_END;
    last->next = HEAP.end;
}

/* Clears `size` bytes, a word at a time when size is a multiple of 4 */
void zeroMem(void *dst, s32 size) {
    s32 i;

    if (size & 3) {
        u8 *p = dst;

        for (i = 0; i < size; i++) {
            *p++ = 0;
        }
    } else {
        s32 *p = dst;

        size >>= 2;
        for (i = 0; i < size; i++) {
            *p++ = 0;
        }
    }
}

/* Sets `count` bytes to `value` */
void fillMem(s8 *dst, s8 value, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        *dst++ = value;
    }
}

/* First fit from the start of the heap */
void *tryAllocMem(u32 size, s32 tag) {
    MemBlock *b;
    MemBlock *new;
    u32 avail;
    u32 splitSize;

    size = (size + 3) >> 2 << 2;
    splitSize = size + 20;
    for (b = HEAP.first; b->tag != MEM_END; b = b->next) {
        if (b->tag == MEM_FREE) {
            avail = (u8 *)b->next - (u8 *)b - sizeof(MemBlock);
            if (avail >= size) {
                if (avail > splitSize) {
                    new = (MemBlock *)((u8 *)b + size + sizeof(MemBlock));
                    new->prev = b;
                    new->next = b->next;
                    new->tag = MEM_FREE;
                    b->next->prev = new;
                    b->next = new;
                }
                b->tag = tag;
                return b + 1;
            }
        }
    }
    return NULL;
}

/* First fit from the end of the heap */
void *tryAllocMemHigh(u32 size, s32 tag) {
    MemBlock *b;
    MemBlock *prev;
    MemBlock *new;
    u32 avail;

    size = ((size + 3) >> 2 << 2) + sizeof(MemBlock);
    for (b = HEAP.end - 1; HEAP.first != b; b = b->prev) {
        prev = b->prev;
        if (prev->tag == MEM_FREE) {
            avail = (u8 *)b - (u8 *)prev;
            if (size == avail) {
                new = prev;
                new->tag = tag;
                return new + 1;
            }
            if (size < avail) {
                new = (MemBlock *)((u8 *)b - size);
                new->prev = prev;
                new->next = b;
                new->tag = tag;
                b->prev->next = new;
                b->prev = new;
                return new + 1;
            }
        }
    }
    return NULL;
}

/* Evicts cached files until the allocation fits */
void *allocMem(s32 size, s32 tag) {
    void *ptr;

    while ((ptr = tryAllocMem(size, tag)) == NULL) {
        FILE_CACHE.evictOldest();
    }
    return ptr;
}

/* The block is returned in v0, left there by tryAllocMemHigh */
void allocMemHigh(s32 size, s32 tag) {
    while (tryAllocMemHigh(size, tag) == 0) {
        FILE_CACHE.evictOldest();
    }
}

/* allocMem, cleared */
void *allocMemZeroed(s32 size, s32 tag) {
    void *ret = allocMem(size, tag);

    zeroMem(ret, size);
    return ret;
}

/* Keeps a block alive across mode changes, or hands it back to the mode */
void lockMem(void *ptr, s32 lock) {
    MemBlock *block = (MemBlock *)ptr - 1;

    if (lock) {
        block->tag = MEM_LOCKED;
    } else {
        block->tag = MEM_MODE;
    }
}

/* Forgets every registered task */
void clearTaskRegistry(void) {
    s32 i;

    for (i = TASK_REGISTRY_SIZE - 1; i >= 0; i--) {
        TASK_REGISTRY.tasks[i] = 0;
    }
}

/* Adds a task to the first free entry of the registry (ignored when it is full) */
void registerTask(s32 task) {
    s32 i;
    s32 *p;

    for (i = 0, p = TASK_REGISTRY.tasks; i < TASK_REGISTRY_SIZE; i++, p++) {
        if (*p == 0) {
            *p = task;
            return;
        }
    }
}

/* Removes a task from the registry */
void unregisterTask(s32 task) {
    s32 i;
    s32 *p;

    for (i = 0, p = TASK_REGISTRY.tasks; i < TASK_REGISTRY_SIZE; i++, p++) {
        if (*p == task) {
            *p = 0;
            return;
        }
    }
}

/* The next registered task that matches findTask's id and keys (-1 matches anything), or NULL */
void *findNextTask(void) {
    s32 i;
    s32 *e;

    for (i = TASK_REGISTRY.findNext; i < TASK_REGISTRY_SIZE; i++) {
        e = (s32 *)TASK_REGISTRY.tasks[i];
        if (e != NULL && (TASK_REGISTRY.findId == -1 || e[0] == TASK_REGISTRY.findId) &&
            (TASK_REGISTRY.findKey1 == -1 || e[1] == TASK_REGISTRY.findKey1) &&
            (TASK_REGISTRY.findKey2 == -1 || e[2] == TASK_REGISTRY.findKey2)) {
            TASK_REGISTRY.findNext = i + 1;
            return (void *)TASK_REGISTRY.tasks[i];
        }
    }
    return NULL;
}

/* Returns (in v0, through findNextTask) the first registered task that matches */
void findTask(s32 id, s32 key1, s32 key2) {
    TASK_REGISTRY.findId = id;
    TASK_REGISTRY.findKey1 = key1;
    TASK_REGISTRY.findKey2 = key2;
    TASK_REGISTRY.findNext = 0;
    findNextTask();
}

/* The update runs with its stack in the scratchpad */
#define SetSpadStack(addr) \
    __asm__ volatile("move $8,%0\n\tsw $29,0($8)\n\taddiu $8,$8,-16\n\tmove $29,$8" : : "r"(addr) : "$8", "memory")
#define ResetSpadStack() __asm__ volatile("addiu $29,$29,16\n\tlw $29,0($29)" : : : "memory")

/* One frame of a task and its children; returns NULL once the task is gone */
Task *executeTask(Task *task) {
    s32 dying = task->state == TASK_KILL;

    SetSpadStack(0x1F8003FC);
    if (task->state == TASK_RUN && task->paused != 0) {
        if (task->paused > 0) {
            task->paused = -1;
        }
    } else {
        task->update(task, task->children);
    }
    ResetSpadStack();
    if (!dying) {
        if (task->state != TASK_RUN || task->paused == 0) {
            TASK_REGISTRY.funcs.runChildren(task);
        }
    } else {
        task->destroy(task);
        task = NULL;
    }
    return task;
}

/* Runs a frame of each child of a task, dropping the ones that end */
void runChildTasks(Task *task) {
    s32 count = task->childCount;
    s32 *children = task->children;
    s32 i;

    for (i = 0; i < count; i++) {
        if (children[i] != 0) {
            children[i] = (s32)executeTask((Task *)children[i]);
        }
    }
}

/* Runs a frame of a task and its children; returns it, or 0 once it is gone */
s32 runTask(s32 task) {
    if (task != 0) {
        return (s32)executeTask((Task *)task);
    }
    return 0;
}

/* Ends a task now: its last update and destroy run at once */
void killTask(Task *task) {
    if (task != NULL) {
        task->setState(task, TASK_KILL);
        TASK_REGISTRY.funcs.run(task);
    }
}

/* The functions that return what a call left in v0 (allocMemHigh, findTask) and the ones that take
   other types are cast to what the tables give their callers */
Heap HEAP = {
    0,
    NULL,
    NULL,
    initHeap,
    freeMem,
    freeMemByTag,
    allocMem,
    (void *(*)(s32, s32))allocMemHigh,
    allocMemZeroed,
    zeroMem,
    (void (*)(void *, s32, s32))fillMem,
    lockMem,
    heapNop,
};

TaskRegistry TASK_REGISTRY = {
    .funcs = {
        clearTaskRegistry,
        registerTask,
        unregisterTask,
        (void *(*)(s32, s32, s32))findTask,
        findNextTask,
        runChildTasks,
        (void *(*)(void *))runTask,
        (void (*)(s32))killTask,
    },
};
