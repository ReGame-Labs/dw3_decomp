/*
 * WSTAG365: Forest Inn BF, East Sector.
 */

#include "common.h"
#include "field/stage.h"

#include "common/update_stage.inc.c"
#include "common/start_stage.inc.c"

#if VERSION_US || VERSION_JP
#define STAGE_TEXT TEXT_FILE(TEXT_TALKS_06)
#define STAGE_FILE 0x22B
#define STAGE_ARCHIVE 0x3C7
#elif VERSION_EU
#define STAGE_TEXT TEXT_FILE(TEXT_TALKS_06)
#define STAGE_FILE 0x23A
#define STAGE_ARCHIVE 0x3D7
#endif
/* Sets the stage up: its map and actors, playing the ambience ENV_0009 */
void setupStage(void) {
    FIELDSTG_state.textFile = STAGE_TEXT;
    FIELDSTG_state.mapFile = STAGE_FILE - 1;
    FIELDSTG_state.sheetEntry = STAGE_FILE << 16;
    FIELDSTG_state.objects = stageObjects;
    FIELDSTG_state.slots = stageSlots;
    FIELDSTG_state.imageFile = STAGE_ARCHIVE;
    FIELDSTG_state.start = (Vec2){0xB700, 0xD300};
    FIELDSTG_state.images.actors = stageImages;
    FIELDSTG_state.soundBank = MUSIC_BANK(MUSIC_FOREST_INN_BF);
    FIELDSTG_state.music = MUSIC_FOREST_INN_BF;
    FIELDSTG_state.startDir = 0;
    FIELDSTG_state.actors = stageActors;
    FIELDSTG_map.setFile(FIELD_MAP_FLOOR0, STAGE_FILE << 16 | 2);
    FIELDSTG_map.setFile(FIELD_MAP_TRIGGERS, STAGE_FILE << 16 | 1);
    FIELDSTG_map.setFirstMap(0);
}

ActorImage stageImages[] = {
    { 0x200, 0x100, 0x21C, 0x1A6, 0x70, 0xA6, 0x230, 0x1FE },
    { 0x200, 0x100, 0x200, 0x100, 0, 0, 0x220, 0x1FE },
    { 0x200, 0x100, 0x216, 0x138, 0x58, 0x38, 0x200, 0x1FD },
    { 0x200, 0x100, 0x208, 0x1BC, 0x20, 0xBC, 0x210, 0x1FD },
    { 0x200, 0x100, 0x210, 0x1BC, 0x40, 0xBC, 0x220, 0x1FD },
    { 0x200, 0x100, 0x200, 0x1BC, 0, 0xBC, 0x230, 0x1FD },
    { 0x140, 0x100, 0x176, 0x150, 0xD8, 0x50, 0x160, 0x1FF },
    { 0x140, 0x100, 0x15E, 0x138, 0x78, 0x38, 0x170, 0x1FF },
    { 0x140, 0x100, 0x166, 0x14C, 0x98, 0x4C, 0x160, 0x1FE },
};
u16 actor10Talk0Conditions[] = { ITEM(0, 0x18E), 0, CODES_END };
u16 actor10Talk0Actions[] = { ITEM(0, 0x18E), 1, SPECIAL_SHOW_ITEM_GET_ICON, 1, CODES_END };
u16 actor10Talk1Conditions[] = { ITEM(0, 0x18E), 1, CODES_END };
FieldTalk actor0Talks[] = {
    { NULL, NULL, 0x1D },
    { NULL, NULL, 0 },
};
FieldTalk actor1Talks[] = {
    { NULL, NULL, 0x10E },
    { NULL, NULL, 0 },
};
FieldTalk actor2Talks[] = {
    { NULL, NULL, 0x107 },
    { NULL, NULL, 0 },
};
FieldTalk actor3Talks[] = {
    { NULL, NULL, 0x10F },
    { NULL, NULL, 0 },
};
FieldTalk actor4Talks[] = {
    { NULL, NULL, 0x10A },
    { NULL, NULL, 0 },
};
FieldTalk actor5Talks[] = {
    { NULL, NULL, 0x10C },
    { NULL, NULL, 0 },
};
FieldTalk actor6Talks[] = {
    { NULL, NULL, 0x106 },
    { NULL, NULL, 0 },
};
FieldTalk actor7Talks[] = {
    { NULL, NULL, 0x108 },
    { NULL, NULL, 0 },
};
FieldTalk actor8Talks[] = {
    { NULL, NULL, 0x109 },
    { NULL, NULL, 0 },
};
FieldTalk actor9Talks[] = {
    { NULL, NULL, 0x10B },
    { NULL, NULL, 0 },
};
FieldTalk actor10Talks[] = {
    { actor10Talk0Conditions, actor10Talk0Actions, 0x2E7 },
    { actor10Talk1Conditions, NULL, 0x328 },
    { NULL, NULL, 0 },
};
FieldTalk actor11Talks[] = {
    { NULL, NULL, 0x10D },
    { NULL, NULL, 0 },
};
u16 actor0Conditions[] = { PROGRESS(STORY_GENJI_BEATEN), 1, CODES_END };
u16 actor1Conditions[] = { PROGRESS(STORY_MOVIE_BATTLES), 1, CODES_END };
u16 actor2Conditions[] = { PROGRESS(STORY_LOOKING_FOR_TEDDY), 1, CODES_END };
u16 actor3Conditions[] = { SPECIAL_STORY_DE_SINCERITY_TO_LISA_SAVED, 1, CODES_END };
u16 actor4Conditions[] = { SPECIAL_STORY_KNIGHTMON_REPROGRAMMED_TO_BULBMON_FOUND, 1, CODES_END };
u16 actor5Conditions[] = { PROGRESS(STORY_PRESIDENT_ARRESTED), 1, CODES_END };
u16 actor6Conditions[] = { SPECIAL_STORY_SEIRYU_BADGE_TO_ZANBAMON_DRIVEN_OFF, 1, CODES_END };
u16 actor7Conditions[] = { PROGRESS(STORY_TEDDY_FOUND), 1, CODES_END };
u16 actor8Conditions[] = { SPECIAL_STORY_BYAKKO_LEADER_FOUGHT_TO_CONTROL_ROOM, 1, CODES_END };
u16 actor9Conditions[] = { SPECIAL_STORY_JUNGLE_SOUND_TO_AMATERASU_BRIDGE, 1, CODES_END };
u16 actor10Conditions[] = {
    PROGRESS(STORY_FAKE_BLUE_CARD), 1,
    FLAG_FAKE_BLUE_CARD_TALKED, 1,
    CODES_END,
};
u16 actor11Conditions[] = { SPECIAL_STORY_ASUKA_HEADQUARTERS_TO_OPERATION_SIGMA, 1, CODES_END };
FieldActorEntry actor0 = { actor0Conditions, actor0Talks, 0x2D, 4, 241, 201, 5 };
FieldActorEntry actor1 = { actor1Conditions, actor1Talks, 0x2D, 4, 241, 201, 3 };
FieldActorEntry actor2 = { actor2Conditions, actor2Talks, 0x2D, 4, 241, 201, 5 };
FieldActorEntry actor3 = { actor3Conditions, actor3Talks, 0x2D, 4, 241, 201, 5 };
FieldActorEntry actor4 = { actor4Conditions, actor4Talks, 0x2D, 4, 241, 201, 5 };
FieldActorEntry actor5 = { actor5Conditions, actor5Talks, 0x2D, 4, 241, 201, 5 };
FieldActorEntry actor6 = { actor6Conditions, actor6Talks, 0x2D, 4, 241, 201, 5 };
FieldActorEntry actor7 = { actor7Conditions, actor7Talks, 0x2D, 4, 241, 201, 5 };
FieldActorEntry actor8 = { actor8Conditions, actor8Talks, 0x2D, 4, 241, 201, 5 };
FieldActorEntry actor9 = { actor9Conditions, actor9Talks, 0x2D, 4, 241, 201, 5 };
FieldActorEntry actor10 = { actor10Conditions, actor10Talks, 0x40, 5, 192, 633, 1 };
FieldActorEntry actor11 = { actor11Conditions, actor11Talks, 0x9D, 6, 241, 201, 5 };
FieldActorEntry *stageActors[] = {
    &actor0,
    &actor1,
    &actor2,
    &actor3,
    &actor4,
    &actor5,
    &actor6,
    &actor7,
    &actor8,
    &actor9,
    &actor10,
    &actor11,
    NULL,
};
StageTile stageObjects[] = {
    { 1, 0, 0x40, 2, 0x34, 2, 0, 7, 4, 0, 97, 134, 0, 0 },
    { 1, 0, 0x40, 2, 0x35, 2, 0, 7, 4, 0, 137, 114, 0, 0 },
    { 1, 0, 0x40, 6, 0x32, 2, 0, 7, 4, 0, 321, 137, 0, 0 },
    { 1, 0, 0x40, 6, 0x32, 2, 0, 7, 4, 0, 577, 313, 0, 0 },
    { 1, 0, 0x40, 6, 0x33, 2, 0, 7, 4, 0, 497, 272, 0, 0 },
    { 1, 0, 0x40, 6, 0x34, 2, 0, 7, 4, 0, 167, 516, 0, 0 },
    { 1, 0, 0x40, 6, 0x35, 2, 0, 7, 4, 0, 187, 293, 0, 0 },
    { 1, 0, 0x40, 6, 0x36, 2, 0, 7, 4, 0, 307, 233, 0, 0 },
    { 1, 0, 0x40, 4, 0, 0, 0, 0, 0, 0, 276, 208, 242, 0 },
    { 1, 0, 0x40, 4, 1, 0, 0, 0, 0, 0, 51, 156, 208, 0 },
    { 1, 0, 0x40, 4, 2, 0, 0, 0, 0, 0, 425, 290, 314, 0 },
    { 1, 0, 0x40, 4, 3, 0, 0, 0, 0, 0, 421, 428, 438, 0 },
    { 1, 0, 0x40, 4, 4, 0, 0, 0, 0, 0, 423, 392, 429, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
StageSlot stageSlots[] = {
    { { { CODES_END, 0 }, { CODES_END, 0 } }, SLOT_EXIT, 0x223, 0x156, 0x1B0, 3, 0, 0, 0 },
    { { { CODES_END, 0 }, { CODES_END, 0 } }, 0, 0, 0, 0, 0, 0, 0, 0 },
};
void (*stageFuncs[])(void) = {
    setupStage,
};
