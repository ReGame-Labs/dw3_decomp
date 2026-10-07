/* FIGHTSTG's Digimon change: the effect of a digivolution, or of a blast's. */

#include "fightstg.h"

/* where FIGHTSTG_updateDigimonChange's effects are: the first (1000, 1001
   or 1007) when the old Digimon starts being wiped away, the second (1002)
   once it's gone, the third (1003 or 1008), behind (z -1), once the new one
   is shown whole; all are screen positions */
const SVECTOR FIGHTSTG_changeStartPos = { 0, 0, 0x7FFF, 0 };
const SVECTOR FIGHTSTG_changeMidPos = { 160, 120, 0x7FFF, 0 };
const SVECTOR FIGHTSTG_changeEndPos = { -160, -120, -1, 0 };

/* A partner Digimon's change: a stage of its own, the new Digimon's model in
   front of a sprite effect, the old one wiped away by the clips of layers 0x1004
   and 0x1003, and a fade back to the battle. The match depends on the block
   of its own for substate 2's control, on z read and then negated, on the
   if/else of the motion, on clip1.h written before clip1.y in substate 3 and on
   the layers kept in blocks of their own */
void FIGHTSTG_updateDigimonChange(DigimonChange *task, DigimonChangeChildren *children) {
    Models *models = task->models;
    BattleCamera *camera = task->camera;
    FightStage *stage = task->stage;
    TimLoader loader;
    ModelControl *control;
    s32 z;
    s32 t;
    s16 y;

    switch (task->state) {
    case 0:
    default:
        switch (task->substate) {
        case 0:
        default:
            switch (task->step) {
            case 0:
            default:
                SOUND.loadBank(0x45);
                task->nextStep(task);
            case 1:
                if (SOUND.isLoading() == 0) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 1:
            models = TASK_REGISTRY.funcs.find(BATTLE_TASK_MODELS, -1, -1);
            task->models = models;
            task->camera = TASK_REGISTRY.funcs.find(BATTLE_TASK_CAMERA, -1, -1);
            task->stage = TASK_REGISTRY.funcs.find(BATTLE_TASK_STAGE, -1, -1);
            task->file = FIGHTSTG_fighterCache.funcs.getInfo(task->key1)->model >> 16;
            FILE_CACHE.request(task->file);
            task->idleMotion = models->get(models, 0)->idleMotion;
            task->nextSubstate(task);
        case 2:
            if (FILE_CACHE.isLoading(task->file) != 0) {
                break;
            }
            FILE_CACHE.request(FILE_CHANGE);
            task->nextSubstate(task);
        case 3:
            if (FILE_CACHE.isLoading(FILE_CHANGE) != 0) {
                break;
            }
            initTimLoader(&loader);
            loader.setImagePos(0x300, 0x100);
            loader.loadArchive(FILE_CACHE.getEntry((FILE_CHANGE << 16) | 5));
            task->nextState(task);
            break;
        }
        break;
    case 1:
        switch (task->substate) {
        case 0:
        default:
            stage->setStage(stage, task->key2 != 0 ? 0x1F : 0x1C, 0x20, 0x20);
            task->nextSubstate(task);
        case 1:
            switch (task->step) {
            case 0:
            default:
                if (stage->state == 2) {
                    break;
                }
                SOUND.playSound(0x41140000);
                models->add(models, 1, task->key1, 0);
                task->nextStep(task);
            case 1:
                task->counter += GFX.funcs.getFrameTime();
                if (task->counter >= 180) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 2:
            {
                ModelControl *control;

                task->clip0.x = 0;
                task->clip0.y = 0;
                task->clip0.w = 320;
                task->clip0.h = 240;
                task->clip1.x = 0;
                task->clip1.y = 240;
                task->clip1.w = 320;
                task->clip1.h = 0;
                control = models->get(models, 0);
                camera->getFighterView(camera, 0, 9);
                z = control->homePos.z;
                z = -z;
                FIGHTSTG_fighterView.vpz += z;
                FIGHTSTG_fighterView.vrz += z;
                camera->set(camera, &FIGHTSTG_fighterView);
                control->unk34[1].enabled = 1;
                control->unk34[1].alt = 1;
                control->unk34[1].arg = 0x1003;
                control->pos.x = 0;
                control->pos.z = 0;
                control->rot.x = 0;
                control->rot.y = 0x800;
                control->rot.z = 0;
                control->pos.y = control->homePos.y;
                if (task->key2 != 0) {
                    control->motion = 14;
                } else {
                    control->motion = 13;
                }
                models->get(models, 0x10)->unk34[0].enabled = 0;
                if (task->key2 == 0) {
                    children->effects[0] = FIGHTSTG_startSpriteEffect(1000, (SVECTOR *)&FIGHTSTG_changeStartPos);
                    children->effects[1] = FIGHTSTG_startSpriteEffect(1001, (SVECTOR *)&FIGHTSTG_changeStartPos);
                } else {
                    children->effects[0] = FIGHTSTG_startSpriteEffect(1007, (SVECTOR *)&FIGHTSTG_changeStartPos);
                }
            }
            task->nextSubstate(task);
        case 3:
            t = GFX.funcs.getFrameTime();
            task->clip0.h -= t * 2;
            task->clip1.h += t * 2;
            task->clip1.y -= t * 2;
            if (task->clip1.y <= 0) {
                task->clip0.h = 0;
                task->clip1.h = 240;
                task->clip1.y = 0;
                models->get(models, 0)->unk34[0].enabled = 0;
                children->effects[2] = FIGHTSTG_startSpriteEffect(1002, (SVECTOR *)&FIGHTSTG_changeMidPos);
                task->nextSubstate(task);
            }
            {
                Layer *layer = GFX.funcs.getLayer(0x1004);

                layer->setClipPos(layer, task->clip0.x, task->clip0.y);
                layer->setClipSize(layer, task->clip0.w, task->clip0.h);
                layer = GFX.funcs.getLayer(0x1003);
                layer->setClipPos(layer, task->clip1.x, task->clip1.y);
                layer->setClipSize(layer, task->clip1.w, task->clip1.h);
            }
            break;
        case 4:
            task->counter += GFX.funcs.getFrameTime();
            if (task->counter >= 120) {
                task->nextSubstate(task);
            }
            break;
        case 5:
            switch (task->step) {
            case 0:
            default:
                children->fade = FIGHTSTG_startWhiteFlash(32);
                task->nextStep(task);
                break;
            case 1:
                if (children->fade->substate != 0) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 6:
            models->setId(models, 1, 0);
            control = models->get(models, 0);
            control->unk34[0].enabled = 1;
            control->unk34[0].arg = 0x1004;
            control->unk34[0].alt = 0;
            control->unk34[1].enabled = 1;
            control->unk34[1].alt = 1;
            control->unk34[1].arg = 0x1003;
            models->face(models, 0);
            camera->getFighterView(camera, 0, 9);
            z = control->homePos.z;
            z = -z;
            FIGHTSTG_fighterView.vpz += z;
            FIGHTSTG_fighterView.vrz += z;
            camera->set(camera, &FIGHTSTG_fighterView);
            control->pos.x = 0;
            control->pos.z = 0;
            control->rot.x = 0;
            control->rot.y = 0x800;
            control->rot.z = 0;
            control->pos.y = control->homePos.y;
            task->clip0.x = 0;
            task->clip0.y = 0;
            task->clip0.w = 320;
            task->clip0.h = 0;
            task->clip1.x = 0;
            task->clip1.y = 0;
            task->clip1.w = 320;
            task->clip1.h = 240;
            task->nextSubstate(task);
        case 7:
            switch (task->step) {
            case 0:
            default:
                children->fade->setState(children->fade, 2);
                task->nextStep(task);
                break;
            case 1:
                if (children->fade == NULL) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 8:
            t = GFX.funcs.getFrameTime();
            task->clip0.h += t * 2;
            task->clip1.y += t * 2;
            task->clip1.h -= t * 2;
            if (task->clip0.h >= 240) {
                task->clip0.h = 240;
                task->clip1.y = 240;
                task->clip1.h = 0;
                models->get(models, 0)->unk34[1].enabled = 0;
                children->effects[3] = FIGHTSTG_startSpriteEffect(task->key2 == 0 ? 1003 : 1008, (SVECTOR *)&FIGHTSTG_changeEndPos);
                task->nextSubstate(task);
            }
            {
                Layer *layer = GFX.funcs.getLayer(0x1004);

                layer->setClipPos(layer, task->clip0.x, task->clip0.y);
                layer->setClipSize(layer, task->clip0.w, task->clip0.h);
                layer = GFX.funcs.getLayer(0x1003);
                layer->setClipPos(layer, task->clip1.x, task->clip1.y);
                layer->setClipSize(layer, task->clip1.w, task->clip1.h);
            }
            break;
        case 9:
            models->get(models, 0)->motion = 13;
            task->nextSubstate(task);
        case 10:
            task->counter += GFX.funcs.getFrameTime();
            if (task->counter >= 180) {
                task->nextSubstate(task);
            }
            break;
        case 11:
            stage->setStage(stage, BATTLE_SETUP.stage, 0x20, 0x20);
            task->nextSubstate(task);
        case 12:
            if (stage->state != 2) {
                models->face(models, 0);
                camera->set(camera, camera->getFighterView(camera, 0, 9));
                task->nextSubstate(task);
            }
            break;
        case 13:
            task->nextSubstate(task);
            break;
        case 14:
            switch (task->step) {
            case 0:
            default:
                models->get(models, 0x10)->unk34[0].enabled = 1;
                models->get(models, 0)->motion = task->key2 != 0 || task->idleMotion == 0 ? 1 : 2;
                camera->fade(camera, NULL, camera->getEnemyView(camera), 60);
                SOUND.playSound(BATTLE_SETUP.music);
                task->nextStep(task);
                break;
            case 1:
                task->counter += GFX.funcs.getFrameTime();
                if (task->counter >= 60) {
                    task->setState(task, 3);
                }
                break;
            }
            break;
        }
        break;
    case 2:
    case 3:
        break;
    }
}

/* Starts a partner's Digimon change (FIGHTSTG_updateDigimonChange) */
DigimonChange *FIGHTSTG_startDigimonChange(s32 key1, s32 key2) {
    DigimonChange *task = createTask(FIGHTSTG_updateDigimonChange, sizeof(DigimonChange), 6 * sizeof(Task *));

    task->key1 = key1;
    task->key2 = key2;
    return task;
}
