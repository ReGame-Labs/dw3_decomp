/* The icon over the player's head */

#include "fieldstg.h"

/* The icon over the player's head: plays the animation of its substate
   (FIELDSTG_actorAnims) and follows its climbs along FIELDSTG_actorPath */
void FIELDSTG_updateActorIcon(ActorIcon *task) {
    SpriteDrawer sprite;
    Point pos;
    u8 (*anim)[2];
    Actor *actor;
    s32 step;
    s32 time;

    switch (task->state) {
    default:
    case 0:
        task->nextState(task);
    case 1:
        if (task->step == 0) {
            task->anim = FIELDSTG_actorAnims[task->substate];
            task->animStep = 0;
            task->animTime = 0;
            switch (task->substate) {
            case 1:
            case 3:
                SOUND.playSound(0x40009);
                break;
            }
            task->nextStep(task);
        }
        if (task->actor != NULL && task->actor->state == 1) {
            step = task->animStep;
            time = task->animTime;
            time += GFX.funcs.getFrameTime();
            anim = task->anim;
            if (anim[step][1] < time) {
                time -= anim[step][1];
                step++;
                if (anim[step][0] == 0xFF) {
                    step = anim[step][1];
                }
                task->frame = anim[step][0];
                task->animStep = step;
            }
            task->animTime = time;
            actor = task->actor;
            switch (actor->substate) {
            case ACTOR_CLIMB_OFF_TOP:
                if (actor->climbSide != 0) {
                    pos.x = actor->tile.x + FIELDSTG_actorPath[FIELDSTG_actorPathStep][0];
                } else {
                    pos.x = actor->tile.x - FIELDSTG_actorPath[FIELDSTG_actorPathStep][0];
                }
                pos.y = actor->tile.y + FIELDSTG_actorPath[FIELDSTG_actorPathStep][1];
                if (FIELDSTG_actorPath[FIELDSTG_actorPathStep + 1][0] != 0) {
                    FIELDSTG_actorPathStep++;
                }
                break;
            case ACTOR_GET_OVER_EDGE:
                if (FIELDSTG_actorPathStep == 0) {
                    FIELDSTG_actorPathStep = 0xE;
                }
                if (actor->climbSide != 0) {
                    pos.x = actor->tile.x + FIELDSTG_actorPath[FIELDSTG_actorPathStep][0];
                } else {
                    pos.x = actor->tile.x - FIELDSTG_actorPath[FIELDSTG_actorPathStep][0];
                }
                pos.y = actor->tile.y + FIELDSTG_actorPath[FIELDSTG_actorPathStep][1];
                if (FIELDSTG_actorPathStep != 1) {
                    FIELDSTG_actorPathStep--;
                }
                break;
            default:
                pos.x = actor->tile.x;
                FIELDSTG_actorPathStep = 0;
                pos.y = actor->tile.y;
                break;
            }
            initSpriteDrawer(&sprite);
            sprite.setTexture(0x200, 0x100);
            sprite.setLayerId(FIELD_LAYER_MAP, 2);
            sprite.draw(FILE_CACHE.getEntry(FIELD_SPRITES_FILE << 16), task->frame, pos.x, pos.y);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

/* Creates the player's icon, in the modes before MODE_NEW_GAME only */
ActorIcon *FIELDSTG_createActorIcon(Actor *actor) {
    ActorIcon *task;

    if (GAME.funcs.getMode() < MODE_NEW_GAME) {
        task = createTaskWithId(FIELDSTG_updateActorIcon, sizeof(ActorIcon), 0, FIELD_TASK_ICON);
        task->actor = actor;
        return task;
    }
    return NULL;
}
