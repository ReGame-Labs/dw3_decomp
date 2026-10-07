/* The gauge game */

#include "fieldstg.h"

/* A gauge game: a cursor runs back and forth along one of the gauge rows until
 * cross is pressed, then slows down and stops; the cell it stops on (2 bits)
 * fails (0) or calls FIELDSTG_battleFuncs.startEventBattle with 4 (1) or 7 (2). In Europe the rows are
 * random only while GAME.unk26F8 lasts, then it is row 8, all zeros. The match
 * depends on the cell read and shifted as two statements. */
void FIELDSTG_runGauge(GaugeGame *task) {
    SpriteDrawer drawer;
    SpriteDrawer gauge;
    s32 sprites;
    s32 gaugeSprites;
    u8 cell;
    s32 index;
    s32 shift;

    switch (task->state) {
    case 0:
    default:
#if VERSION_EU
        if (GAME.unk26F8 > 0) {
            task->row = RANDOM.next() & 7;
            GAME.unk26F8--;
        } else {
            task->row = 8;
        }
#else
        task->row = RANDOM.next() & 7;
#endif
        task->speed = 0x100;
        task->nextState(task);
    case 1:
        switch (task->substate) {
        case 0:
        default:
            task->step += GFX.funcs.getFrameTime();
            if (task->step > 0x5A) {
                task->nextSubstate(task);
            }
            break;
        case 1:
            switch (task->step) {
            case 0:
            default:
                if (PAD.getPressed(0) & (1 << PAD_CROSS)) {
                    if (!(RANDOM.next() & 3)) {
                        task->setStep(task, 2);
                    } else {
                        task->setStep(task, 1);
                    }
                    SOUND.playSound(SOUND_MENU_MOVE);
                }
                break;
            case 1:
                task->speed -= 0x10;
                if (task->speed == 0) {
                    task->setStep(task, 3);
                }
                break;
            case 2:
                task->speed -= 4;
                if (task->speed == 0) {
                    task->setStep(task, 3);
                }
                break;
            case 3:
#if VERSION_EU
                index = task->cursor >> 10;
                shift = (task->cursor >> 7) & 6;
                cell = FIELDSTG_gaugeRows[task->row][index];
                cell = (cell >> shift) & 3;
                if (task->counter < 0x3C) {
                    if (task->counter == 0 && cell == 1) {
                        SOUND.playSound(0x80045341);
                    }
                    task->counter += GFX.funcs.getFrameTime();
                    break;
                }
#else
                task->counter += GFX.funcs.getFrameTime();
                if (task->counter < 0x3C) {
                    break;
                }
                index = task->cursor >> 10;
                shift = (task->cursor >> 7) & 6;
                cell = FIELDSTG_gaugeRows[task->row][index];
                cell = (cell >> shift) & 3;
#endif
                switch (cell) {
                case 0:
                default:
                    task->setState(task, 3);
                    break;
                case 1:
                    FIELDSTG_battleFuncs.startEventBattle(4);
                    task->setState(task, 2);
                    break;
                case 2:
                    FIELDSTG_battleFuncs.startEventBattle(7);
                    task->setState(task, 2);
                    break;
                }
                break;
            }
            if (task->back) {
                task->cursor -= task->speed;
                if (task->cursor <= 0) {
                    task->cursor = 0;
                    task->back = 0;
                }
            } else {
                task->cursor += task->speed;
                if (task->cursor >= 0x3000) {
                    task->cursor = 0x3000;
                    task->back = 1;
                }
            }
            sprites = FILE_CACHE.getEntry(FIELD_SPRITES_FILE << 16);
            initSpriteDrawer(&drawer);
            drawer.setLayerId(FIELD_LAYER_MAP, 4);
            drawer.setTexture(0x200, 0x100);
            drawer.draw(sprites, GFX.funcs.getTime() % 48 / 12 + 0x60, task->pos.x, task->pos.y);
            gaugeSprites = FILE_CACHE.getEntry((FIELD_SPRITES_FILE << 16) | 1);
            initSpriteDrawer(&gauge);
            gauge.setLayerId(FIELD_LAYER_MAP, 0);
            gauge.setTexture(0x240, 0x100);
            gauge.setFollowScroll(0);
            gauge.draw(gaugeSprites, 0x3D, (task->cursor >> 8) + 0x18, 0xC0);
            gauge.draw(gaugeSprites, task->row + 0x3E, 0x18, 0xC0);
            gauge.draw(gaugeSprites, 0x3C, 0x18, 0xC0);
            break;
        }
        break;
    case 2:
    case 3:
        break;
    }
}

/* Creates the gauge game at a tile */
GaugeGame *FIELDSTG_createGauge(Point pos) {
    GaugeGame *task = createTask(FIELDSTG_runGauge, sizeof(GaugeGame), 0);

    task->pos = pos;
    return task;
}
