/* The story events, which start at a point of the story */

#include "field/field_mode.h"

/*
 * Runs the story events: marks the map object 1 for the progresses that have
 * one, then starts the first event of FIELDSTG_progressEvents whose progress, flag and
 * condition hold, and its next script once the first one ends.
 */
void FIELDSTG_runStoryEvents(StoryEvents *task, StoryEventsChildren *children) {
    StageTile *object;
    ProgressEvent *event;
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        task->script = 0;
        for (object = FIELDSTG_state.objects; object->margin != 0; object++) {
            if (object->anim == 1) {
                break;
            }
        }
        switch (GAME.progress) {
        case STORY_SEIRYU_BADGE:
        case STORY_SEPIKMON_MASK_LOST:
        case STORY_LOOKING_FOR_TEDDY:
        case STORY_TEDDY_FOUND:
        case STORY_NUMEMON_FOUND:
        case STORY_CONTROL_ROOM:
        case STORY_KNIGHTMON_REPROGRAMMED:
        case STORY_BULBMON_FOUND:
        case STORY_BLUE_ID_PASS:
        case STORY_DE_KNOWLEDGE:
        case STORY_GENBU_BADGE:
        case STORY_WAY_TO_AMATERASU:
        case STORY_BLACK_ID_PASS:
        case STORY_AMATERASU_BRIDGE:
        case STORY_PRESIDENT_ARRESTED:
        case STORY_ASUKA_HEADQUARTERS:
            object->visible = 1;
            break;
        default:
            object->visible = 0;
            break;
        }
        children->lift = FIELDSTG_createLift(0x33A);
        for (i = 0; FIELDSTG_progressEvents[i].progress != -1; i++) {
            event = &FIELDSTG_progressEvents[i];
            if (GAME.progress == event->progress && FLAGS_00.checkCondition(event->flag, 0) &&
                FLAGS_00.checkCondition(event->condition, 1)) {
                children->script = FIELDSTG_startEvent(event->script);
                task->script = event->nextScript;
                break;
            }
        }
        break;
    case TASK_RUN:
        if (children->script == NULL && task->script != 0) {
            children->script = FIELDSTG_startEvent(task->script);
            task->script = 0;
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Creates the story events, and loads the field's sound bank and files */
StoryEvents *FIELDSTG_createStoryEvents(void *owner) {
    StoryEvents *task = createTask(FIELDSTG_runStoryEvents, sizeof(StoryEvents), 8);

    task->owner = owner;
    FIELDSTG_initFuncs[0]();
    return task;
}
