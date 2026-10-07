/* A linear 0-0x1000 tween, for the questions' panel */

#include "fieldstg.h"

/* Starts a tween in (0 to 0x1000, over its duration) or out (twice as fast),
   with the menu's sound */
void FIELDSTG_startTween(Tween *tween, s32 in) {
    tween->active = 1;
    if (in) {
        SOUND.playSound(SOUND_MENU_OPEN);
        tween->value = 0;
        tween->step = 0x1000 / tween->duration;
    } else {
        SOUND.playSound(SOUND_MENU_CLOSE);
        tween->value = 0x1000;
        tween->step = -(0x1000 / tween->duration * 2);
    }
}

/* Steps a tween; returns 1 once it is done */
s32 FIELDSTG_updateTween(Tween *tween) {
    if (tween->active == 0) {
        return 1;
    }
    tween->value += tween->step;
    if (tween->step > 0) {
        if (tween->value > 0x1000) {
            tween->value = 0x1000;
            tween->active = 0;
            return 1;
        }
    } else if (tween->value < 0) {
        tween->value = 0;
        tween->active = 0;
        return 1;
    }
    return 0;
}
