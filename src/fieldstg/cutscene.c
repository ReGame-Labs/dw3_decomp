/* The animations of a cutscene over the field */

#include "fieldstg.h"

/* A cutscene's animation over the field (FIELDSTG_createCutsceneAnim): kind 0 plays once,
   kind 1 loops two animations until 160 ticks of frame time pass. The match
   depends on the if/else around the file calls (not a ?: in their argument)
   and on case 0 next to default. */
void FIELDSTG_playCutsceneAnim(CutsceneAnim *task) {
    TimLoader loader;
    SpriteDrawer drawer;
    s32 loading;

    switch (task->state) {
    case 0:
    default:
        switch (task->substate) {
        case 0:
        default:
            if (task->kind) {
                FILE_CACHE.request(FIELD_ANIM_FILE + 1);
            } else {
                FILE_CACHE.request(FIELD_ANIM_FILE);
            }
            task->nextSubstate(task);
        case 1:
            if (task->kind) {
                loading = FILE_CACHE.isLoading(FIELD_ANIM_FILE + 1);
            } else {
                loading = FILE_CACHE.isLoading(FIELD_ANIM_FILE);
            }
            if (loading == 0) {
                initTimLoader(&loader);
                loader.setImagePos(0x280, 0);
                loader.setClutPos(0, 0xF0);
                if (task->kind) {
                    loader.loadArchive(FILE_CACHE.getEntry(((FIELD_ANIM_FILE + 1) << 16) | 1));
                    SOUND.playSound(0x40003);
                } else {
                    loader.loadArchive(FILE_CACHE.getEntry((FIELD_ANIM_FILE << 16) | 1));
                    SOUND.playSound(0x40018);
                }
                task->nextState(task);
            }
            break;
        }
        break;
    case 1:
        if (task->kind == 0) {
            if (task->timer <= 0) {
                task->index++;
                task->frame = FIELDSTG_cutsceneAnim[task->index].frame;
                task->timer = FIELDSTG_cutsceneAnim[task->index].duration;
            } else {
                task->timer -= GFX.funcs.getFrameTime();
            }
            if (task->frame == -1) {
                task->setState(task, 2);
            }
        }
        break;
    case 2:
    case 3:
        break;
    }

    if (task->state == 1 || task->state == 2) {
        if (task->kind) {
            while (1) {
                if (task->timer <= 0) {
                    task->index++;
                    task->frame = FIELDSTG_cutsceneLoopAnim[task->index].frame;
                    task->timer = FIELDSTG_cutsceneLoopAnim[task->index].duration;
                } else {
                    task->timer -= GFX.funcs.getFrameTime();
                }
                if (task->frame != -1) {
                    break;
                }
                task->index = task->timer;
                task->timer = -1;
            }
            while (1) {
                if (task->timer2 <= 0) {
                    task->index2++;
                    task->frame2 = FIELDSTG_cutsceneLoopAnim2[task->index2].frame;
                    task->timer2 = FIELDSTG_cutsceneLoopAnim2[task->index2].duration;
                } else {
                    task->timer2 -= GFX.funcs.getFrameTime();
                }
                if (task->frame2 != -1) {
                    break;
                }
                task->index2 = task->timer2;
                task->timer2 = -1;
            }
            task->counter += GFX.funcs.getFrameTime();
            if (task->counter > 0xA0) {
                task->setState(task, 2);
            }
        }
        initSpriteDrawer(&drawer);
        drawer.setFollowScroll(0);
        drawer.setLayerId(FIELD_LAYER_MAP, 7);
        drawer.setTexture(0x280, 0);
        drawer.setAltClut(0, 0xF0);
        if (task->kind) {
            drawer.draw(FILE_CACHE.getEntry((FIELD_ANIM_FILE + 1) << 16), task->frame, 0, 0);
            if (task->frame2 != 0) {
                drawer.draw(FILE_CACHE.getEntry((FIELD_ANIM_FILE + 1) << 16), task->frame2, 0, 0);
            }
        } else if (task->state == 1) {
            drawer.draw(FILE_CACHE.getEntry(FIELD_ANIM_FILE << 16), task->frame, 0, 0);
        }
        if (task->kind) {
            drawer.draw(FILE_CACHE.getEntry((FIELD_ANIM_FILE + 1) << 16), 0, 0, 0);
        } else {
            drawer.draw(FILE_CACHE.getEntry(FIELD_ANIM_FILE << 16), 10, 0, 0);
        }
    }
}

/* Creates a cutscene animation of a kind */
CutsceneAnim *FIELDSTG_createCutsceneAnim(s32 kind) {
    CutsceneAnim *task = createTask(FIELDSTG_playCutsceneAnim, sizeof(CutsceneAnim), 0);

    task->kind = kind;
    return task;
}
