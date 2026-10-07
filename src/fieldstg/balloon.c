/* The balloons over an actor's head */

#include "fieldstg.h"

/* Steps a balloon's animation (FIELDSTG_triggerAnims) and returns its frame */
s32 FIELDSTG_stepBalloonAnim(Balloon *task) {
    task->time -= GFX.funcs.getFrameTime();
    if (task->time < 0) {
        task->frame += 2;
        if (FIELDSTG_triggerAnims[task->key2][task->frame] == 0xFF) {
            task->frame = 0;
        }
        task->time = FIELDSTG_triggerAnims[task->key2][task->frame + 1];
    }
    return FIELDSTG_triggerAnims[task->key2][task->frame];
}

/* Draws a balloon over its actor: its frame, and once open, its animation */
void FIELDSTG_drawBalloon(Balloon *task) {
    SpriteDrawer sprite;
    Point pos;
    s32 frame;

    pos.x = task->actor->tile.x;
    pos.y = task->actor->tile.y - (task->actor->z >> 8);
    initSpriteDrawer(&sprite);
    sprite.setLayerId(FIELD_LAYER_MAP, 1);
    sprite.setTexture(0x200, 0x100);
    if (task->substate == 2) {
        frame = FIELDSTG_stepBalloonAnim(task);
        sprite.draw(FILE_CACHE.getEntry(FIELD_SPRITES_FILE << 16), frame, pos.x, pos.y - 0x1B);
    }
    sprite.draw(FILE_CACHE.getEntry(FIELD_SPRITES_FILE << 16), task->pop >> 2, pos.x, pos.y - 0x1B);
}

/* A balloon's update: it pops open over the player (or another actor), stays
   while the trigger is on offer and pops shut on state 2 */
void FIELDSTG_updateBalloon(Balloon *task) {
    switch (task->state) {
        default:
        case 0:
            if (task->actor == NULL) {
                task->actor = TASK_REGISTRY.funcs.find(FIELD_TASK_ACTOR, -1, 0);
                if (task->actor == NULL) {
                    break;
                }
            }
            if (task->key1 == 0) {
                task->popStart = 0xC8;
                task->popOpen = 0xD4;
                task->popEnd = 0xDC;
            } else {
                task->popStart = 0x104;
                task->popOpen = 0x10C;
                task->popEnd = 0x114;
            }
            if (task->key2 != 1) {
                SOUND.playSound(0x40007);
            }
            task->nextState(task);
            /* fallthrough */
        case 1:
            if (FIELDSTG_state.innOpen != 0) {
                break;
            }
            switch (task->substate) {
                default:
                case 0:
                    task->pop = task->popStart;
                    task->nextSubstate(task);
                    /* fallthrough */
                case 1:
                    task->pop += GFX.funcs.getFrameTime();
                    if (task->pop >= task->popOpen) {
                        task->pop = task->popOpen;
                        task->nextSubstate(task);
                    }
                    break;
                case 2:
                    break;
            }
            FIELDSTG_drawBalloon(task);
            break;
        case 2:
            task->pop += GFX.funcs.getFrameTime();
            if (task->pop >= task->popEnd) {
                task->pop = task->popEnd;
                task->setState(task, 3);
            }
            FIELDSTG_drawBalloon(task);
            break;
        case 3:
            break;
    }
}

/* Creates a balloon of a kind (its sprites) with an animation, under a task
   id */
Balloon *FIELDSTG_createBalloon(s32 kind, s32 anim, s32 id) {
    Balloon *task = createTaskWithId(FIELDSTG_updateBalloon, sizeof(Balloon), 0, id);
    task->key1 = kind;
    task->key2 = anim;
    return task;
}

/* The balloon over the player: script commands 803 to 806
   (FIELDSTG_scriptCommands) */
void FIELDSTG_createPlayerBalloon(s32 id) {
    FIELDSTG_createBalloon(0, 0, id);
}

/* A balloon's script commands: 0x325 and 0x327 put it over the actor id with
   animation 0 or 1, 0x326 pops it shut */
void FIELDSTG_balloonCommand(Balloon *task, s32 command, s32 id) {
    if (task != NULL) {
        switch (command) {
        case 0x325:
            task->key2 = 0;
            break;
        case 0x327:
            task->key2 = 1;
            break;
        case 0x326:
            task->setState(task, 2);
            break;
        }
        if (command == 0x325 || command == 0x327) {
            task->actor = TASK_REGISTRY.funcs.find(FIELD_TASK_ACTOR, id, -1);
        }
    }
}
