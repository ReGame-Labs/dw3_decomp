/* FIGHTSTG's screen fader: its start and drawing are src/menu_common's. */

#include "fightstg.h"

#include "../menu_common/start_fader.inc.c"
#include "../menu_common/draw_fader.inc.c"

/* The screen fade's task: src/menu_common/update_fader.inc.c, but for its
   first state, which sets TASK_RUN without nextState, and the running
   state's own call to draw */
void FIGHTSTG_updateFader(ScreenFade *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->state = TASK_RUN;
        break;
    case TASK_RUN:
        if (task->substate == 0) {
            break;
        }
        task->level += task->levelStep;
        if (task->fadeIn == 0) {
            if (task->level > FADE_LEVEL_MAX) {
                task->level = FADE_LEVEL_MAX;
                task->state = TASK_DONE;
            }
        } else if (task->level < 0) {
            task->level = 0;
            task->state = TASK_DONE;
        }
        FIGHTSTG_drawFader(task);
        break;
    case TASK_DONE:
        FIGHTSTG_drawFader(task);
        break;
    case TASK_KILL:
        break;
    }
}

/* Creates the screen fade, idle until started, on layer BATTLE_LAYER_FRONT */
ScreenFade *FIGHTSTG_createFader(void) {
    ScreenFade *task = createTask(FIGHTSTG_updateFader, sizeof(ScreenFade), 0);

    task->start = FIGHTSTG_startFader;
    task->layerId = BATTLE_LAYER_FRONT;
    task->depth = 0;
    return task;
}
