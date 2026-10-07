/* FIELDSTG's entry point, which the executable starts the field mode with */

#include "fieldstg.h"

/* FIELDSTG's root task: notes whether the mode is new (GAME.clearTempFlags)
   and creates the field */
void FIELDSTG_updateRoot(Task *task, Task **children) {
    s32 mode;

    switch (task->state) {
        default:
        case 0:
            mode = GAME.funcs.getMode();
            if (GAME.unk26D4 != mode) {
                GAME.unk26D4 = mode;
                GAME.clearTempFlags = 1;
#if VERSION_EU
                GAME.unk26F8 = 0x10;
#endif
            } else {
                GAME.clearTempFlags = 0;
            }
            children[0] = FIELDSTG_createField();
            task->nextState(task);
            break;
        case 1:
        case 2:
        case 3:
            break;
    }
}

/* FIELDSTG's entry point: creates its root task */
Task *FIELDSTG_start(void) {
    return createTask(FIELDSTG_updateRoot, sizeof(Task), 0xC);
}
