#include "common.h"
#include "stage.h"

#include "common/update_stage.inc.c"
#include "common/start_stage.inc.c"

#if VERSION_US
#define STAGE_TEXT 0xE2
#define STAGE_FILE 0x59A
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xDA)
#define STAGE_FILE 0x5AA
#endif
void setupStage(void) {
    FIELDSTG_state.textFile = STAGE_TEXT;
    FIELDSTG_state.mapFile = STAGE_FILE - 1;
    FIELDSTG_state.sheetEntry = STAGE_FILE << 16;
    FIELDSTG_state.objects = stageObjects;
    FIELDSTG_state.slots = stageSlots;
    FIELDSTG_state.imageFile = STAGE_FILE - 2;
    FIELDSTG_state.start = (Vec2){0x1B100, 0x1DA00};
    FIELDSTG_state.images.actors = stageImages;
    FIELDSTG_state.soundBank = 0x30;
    FIELDSTG_state.music = 0x60C00000;
    FIELDSTG_state.startDir = 0;
    FIELDSTG_state.actors = stageActors;
    FIELDSTG_map.setFile(0, STAGE_FILE << 16 | 1);
    FIELDSTG_map.setFile(7, STAGE_FILE << 16 | 2);
    FIELDSTG_map.setFirstMap(0);
}

extern u16 D_800A4ECC[];
extern FieldTalk D_800A4E9C[];
extern u16 D_800A4ED8[];
extern FieldTalk D_800A4EB4[];
extern FieldActorEntry D_800A4EE4;
extern FieldActorEntry D_800A4EF8;

ActorImage stageImages[] = {
    { 0x200, 0x100, 0x21C, 0x1A6, 0x70, 0xA6, 0x230, 0x1FE },
    { 0x200, 0x100, 0x200, 0x100, 0, 0, 0x220, 0x1FE },
    { 0x200, 0x100, 0x216, 0x138, 0x58, 0x38, 0x200, 0x1FD },
    { 0x200, 0x100, 0x208, 0x1BC, 0x20, 0xBC, 0x210, 0x1FD },
    { 0x200, 0x100, 0x210, 0x1BC, 0x40, 0xBC, 0x220, 0x1FD },
    { 0x200, 0x100, 0x200, 0x1BC, 0, 0xBC, 0x230, 0x1FD },
    { 0x140, 0x100, 0x162, 0x100, 0x88, 0, 0x150, 0x1FF },
};
FieldTalk D_800A4E9C[] = {
    { NULL, NULL, 0x101 },
    { NULL, NULL, 0 },
};
FieldTalk D_800A4EB4[] = {
    { NULL, NULL, 0x102 },
    { NULL, NULL, 0 },
};
u16 D_800A4ECC[] = { 0x6026, 1, 0x1A0A, 1, 0xFFFF };
u16 D_800A4ED8[] = { 0x701A, 1, 0x1A0A, 1, 0xFFFF };
FieldActorEntry D_800A4EE4 = { D_800A4ECC, D_800A4E9C, 0x3E, 4, 256, 455, 1 };
FieldActorEntry D_800A4EF8 = { D_800A4ED8, D_800A4EB4, 0x3E, 4, 256, 455, 1 };
FieldActorEntry *stageActors[] = {
    &D_800A4EE4,
    &D_800A4EF8,
    NULL,
};
StageTile stageObjects[] = {
    { 1, 0, 0xD0, 2, 0x32, 0, 0, 0, 0, 0, 51, 95, 0, 0 },
    { 1, 0, 0xD0, 2, 0x32, 0, 0, 0, 0, 0, 300, 55, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
StageSlot stageSlots[] = {
    { { { 0xFFFF, 0 }, { 0xFFFF, 0 } }, 1, 0x29C, 0x350, 0x230, 7, 0, 0, 0 },
    { { { 0xFFFF, 0 }, { 0xFFFF, 0 } }, 0, 0, 0, 0, 0, 0, 0, 0 },
};
void (*stageFuncs[])(void) = {
    setupStage,
};
