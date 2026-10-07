#include "game.h"

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
