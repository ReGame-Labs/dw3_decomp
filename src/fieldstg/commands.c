/* The commands the stage overlays send the field (0x337 to 0x386): the
   field task's substates, map objects shown or hidden, the camera's shake
   and sounds. The first object of FIELDSTG.PRO (see data/fieldstg.c). */

#include "fieldstg.h"

/* The task of script command 813: on substate 1 it stops the partners
   following */
void FIELDSTG_updateCommandTask(Task *task) {
    switch (task->state) {
    case 0:
    case 1:
    default:
        if (task->substate == 1) {
            FIELDSTG_haltPartners();
            task->setSubstate(task, 0);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

/*
 * The field's commands (0x337 to 0x386) that the stage overlays send: the
 * field task's substate, map objects 100 to 105 hidden or shown, and
 * sounds, three of which are held to be keyed off later.
 */
void FIELDSTG_handleFieldCommand(Task *task, s32 command) {
    StageTile *object;
    Task *field;
    s32 n;

    if (task == NULL) {
        return;
    }
    n = 0;
    if (command == 0x337) {
        task->setSubstate(task, 1);
    }
    switch (command) {
    case 0x34A:
        n++;
    case 0x339:
        n++;
    case 0x338:
        n++;
        field = TASK_REGISTRY.funcs.find(FIELD_TASK_ICON, -1, -1);
        field->setSubstate(field, n);
        break;
    }
    switch (command) {
    case 0x34D ... 0x352:
        for (object = FIELDSTG_state.objects; object->unk2 != 0; object++) {
            if (object->anim == command - 0x2E9) {
                object->visible = 0;
            }
        }
        break;
    case 0x353 ... 0x358:
        for (object = FIELDSTG_state.objects; object->unk2 != 0; object++) {
            if (object->anim == command - 0x2EF) {
                object->visible = 1;
            }
        }
        break;
    }
    switch (command) {
    case 0x372:
        FIELDSTG_shakeCamera(1);
        break;
    case 0x373:
        FIELDSTG_shakeCamera(0);
        break;
    }
    if (command == 0x376) {
        FIELDSTG_searchEventSpot();
    }
    switch (command) {
    case 0x365:
        SOUND.playSound(0xB80001);
        break;
    case 0x368:
        SOUND.playSound(0x80E8383C);
        break;
    case 0x369:
        SOUND.playSound(0x60040002);
        break;
    case 0x36A:
        SOUND.playSound(0xA40006);
        break;
    case 0x36B:
        SOUND.playSound(0x805458BD);
        break;
    case 0x36C:
        SOUND.playSound(0x800410BD);
        break;
    case 0x36D:
        SOUND.playSound(0x803C503C);
        break;
    case 0x36E:
        SOUND.playSound(0x01100000);
        break;
    case 0x36F:
        SOUND.playSound(0x01100002);
        break;
    case 0x374:
        SOUND.playSound(0x700001);
        break;
    case 0x375:
        SOUND.playSound(0x40015);
        break;
    case 0x377:
        SOUND.playSound(0x8004113E);
        break;
    case 0x378:
        SOUND.playSound(0x8110303C);
        break;
    case 0x379:
        SOUND.playSound(0x81103240);
        break;
    case 0x37A:
        SOUND.playSound(SOUND_TELEPORT);
        break;
    case 0x37C:
        SOUND.playSound(0x440001);
        break;
    case 0x37D:
        SOUND.playSound(0x340004);
        break;
    case 0x37E:
        SOUND.playSound(0x40013);
        break;
    case 0x37F:
        SOUND.playSound(0x800429BF);
        break;
    case 0x380:
        SOUND.playSound(0x800430BD);
        break;
    case 0x381:
        SOUND.playSound(0x80042DC7);
        break;
    case 0x383:
        SOUND.playSound(0x8004103C);
        break;
    }
    switch (command) {
    case 0x366:
        FIELDSTG_heldVoice = SOUND.playSound(0xA10C703C);
        break;
    case 0x370:
        FIELDSTG_heldVoice = SOUND.playSound(0xA0045EC9);
        break;
    case 0x382:
        FIELDSTG_heldVoice = SOUND.playSound(0xA054583C);
        break;
    case 0x384:
        FIELDSTG_heldVoice = SOUND.playSound(0xA0042FCB);
        break;
    }
    switch (command) {
    case 0x367:
        SOUND.keyOff(0xA10C703C, FIELDSTG_heldVoice);
        break;
    case 0x371:
        SOUND.keyOff(0xA0045EC9, FIELDSTG_heldVoice);
        break;
    case 0x385:
        SOUND.keyOff(0xA0042FCB, FIELDSTG_heldVoice);
        break;
    case 0x386:
        SOUND.keyOff(0xA054583C, FIELDSTG_heldVoice);
        break;
    }
}

/* Creates the task of script command 813 (the create of
   FIELDSTG_scriptCommands) */
void FIELDSTG_startCommandTask(void) {
    createTaskWithId(FIELDSTG_updateCommandTask, sizeof(Task), 0, 0x32D);
}
