#include "common.h"
#include "stage.h"
const CVECTOR stageColor = { 0x80, 0x80, 0x80, 0x00 };

/* Defined below, after the code that uses them */
extern s32 partyActorIds[];
void *createSpritePair(s32 x, s32 y);
extern AnimFrame updateSpritePairFrames_0[];
extern AnimFrame updateSpritePairFrames_1[];
extern AnimFrame *updateSpritePairFrames[];

void updateEvent9015(StageTask *task, StagePartyChildren *children) {
    StageActor *player;
    StageActor *actor;
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        switch (task->substate) {
        case 0:
        default:
            switch (task->step) {
            case 0:
            default:
                player = TASK_REGISTRY.funcs.find(FIELD_TASK_ACTOR, -1, 0);
                player->setSubstate(player, 1);
                SOUND.playSound(SOUND_SWITCH02);
                task->nextStep(task);
            case 1:
                task->counter += GFX.funcs.getFrameTime();
                if (task->counter >= 0x1E) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 1:
        case 2:
        case 3:
            switch (task->step) {
            case 0:
            default:
                i = task->substate - 1;
                actor = TASK_REGISTRY.funcs.find(FIELD_TASK_ACTOR, -1, partyActorIds[i]);
                if (actor != NULL) {
                    children->party[i] = createSpritePair(actor->tileX, actor->tileY);
                    SOUND.playSound(SOUND_COMEX113);
                    actor->setSubstate(actor, 4);
                    GAME.partners[GAME.party[i]].info.stats[STAT_HP] = 1;
                    task->nextStep(task);
                } else {
                    task->nextSubstate(task);
                }
                break;
            case 1:
                task->counter += GFX.funcs.getFrameTime();
                if (task->counter >= 0x1E) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 4:
            task->nextState(task);
            break;
        }
        break;
    case TASK_RUN:
        if (children->party[0] == NULL) {
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *startEvents9000To9015(void) {
    return createTask(updateEvent9015, sizeof(StageTask), sizeof(StagePartyChildren));
}

void updateStage(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        if (FLAGS_00.checkCondition(FLAG(0x40, 0x84), 1) && FLAGS_00.checkCondition(FLAG(0x40, 0x85), 0)) {
            children[1] = FIELDSTG_startEvent(0x510);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

#define STAGE_CHILDREN_SIZE 0x8
#include "common/start_stage.inc.c"

#include "common/step_state_animation_once.inc.c"

#include "common/draw_pair_sprite.inc.c"

void updateSpritePair(StageSpritePair *task) {
    Layer *layer = GFX.funcs.getLayer(FIELD_LAYER_MAP);
    s32 done;
    s32 i;
    s32 frame;
    s32 y;
    void (*draw)();

    switch (task->state) {
    case TASK_INIT:
    default:
        task->anims[0].index = 0;
        task->anims[0].timer = updateSpritePairFrames_0[0].duration;
        task->anims[1].index = 0;
        task->anims[1].timer = updateSpritePairFrames_1[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        done = 0;
        i = 0;
        draw = drawPairSprite;
        for (; i < 2; i++) {
            frame = stepAnimationOnce(&task->anims[i], updateSpritePairFrames[i], 0);
            switch (frame) {
            case 0xFF:
                task->sprites[i].frame = 0;
                done++;
                break;
            case 0x12C:
                task->sprites[i].frame = 0;
                break;
            default:
                task->sprites[i].frame = frame;
                break;
            }
            if (task->sprites[i].frame != 0) {
                y = task->y;
                if (i == 0) {
                    y -= 0xF0;
                } else {
                    y += 0x14;
                }
                layer->addSortedCallback(layer, draw, task, y, i);
            }
        }
        if (done == 2) {
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

#include "common/create_sprite_pair.inc.c"

void endEvent1295(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0x84), 1);
    FLAGS_00.applyAction(EVENT_BATTLE(0), 1);
}

void endEvent1296(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0x85), 1);
    FLAGS_00.applyAction(ITEM(1, 0x33), 1);
}

void endEvent9000(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xBA), 1);
}

void endEvent9001(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xBB), 1);
}

void endEvent9002(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xBC), 1);
}

void endEvent9003(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xBD), 1);
}

void endEvent9004(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xBE), 1);
}

void endEvent9005(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xBF), 1);
}

void endEvent9006(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xC0), 1);
}

void endEvent9007(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xC1), 1);
}

void endEvent9008(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xC2), 1);
}

void endEvent9009(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xC3), 1);
}

void endEvent9010(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xC4), 1);
}

void endEvent9011(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xC5), 1);
}

void endEvent9012(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xC6), 1);
}

void endEvent9013(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xC7), 1);
}

void endEvent9014(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xC8), 1);
}

void endEvent9015(void) {
    FLAGS_00.applyAction(FLAG(0x40, 0xC9), 1);
}

#if VERSION_US
#define STAGE_TEXT 0xFE
#define EVENT_TEXT_FILE 0x143
#define STAGE_FILE 0x741
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xF6)
#define EVENT_TEXT_FILE 0x14A
#define STAGE_FILE 0x751
#endif
void setupStage(void) {
    FIELDSTG_state.textFile = STAGE_TEXT;
    FIELDSTG_state.mapFile = STAGE_FILE - 1;
    FIELDSTG_state.sheetEntry = STAGE_FILE << 16;
    FIELDSTG_state.objects = stageObjects;
    FIELDSTG_state.slots = stageSlots;
    FIELDSTG_state.imageFile = STAGE_FILE - 2;
    FIELDSTG_state.start = (Vec2){0x1CD00, 0x29A00};
    FIELDSTG_state.images.actors = stageImages;
    FIELDSTG_state.soundBank = 0x19;
    FIELDSTG_state.music = MUSIC(0x19, 0);
    FIELDSTG_state.actors = stageActors;
    FIELDSTG_state.startDir = 0;
    FIELDSTG_state.spriteColor = stageColor;
    FIELDSTG_state.battles = stageBattles;
    FIELDSTG_state.events = stageEvents;
    FIELDSTG_map.setFile(FIELD_MAP_FLOOR0, STAGE_FILE << 16 | 1);
    FIELDSTG_map.setFile(FIELD_MAP_TRIGGERS, STAGE_FILE << 16 | 2);
    FIELDSTG_map.setFile(FIELD_MAP_AREAS, STAGE_FILE << 16 | 3);
    FIELDSTG_map.setFirstMap(0);
}

s16 script1295[] = {
    0x600, 1, 2,
    0x102, 2, 0x215, 0x2AC, 3,
    0x100, 0xCC, 0x200, 0x2A1,
    0x101, 0xCC, 1, 7,
    0x101, FIELD_TASK_COMMANDS, FIELD_COMMAND_HALT_PARTNERS, 2,
    0x302, 2,
    0x101, 2, 1, 3,
    0x300, 0x1E,
    0x200, 0, 1, 0xCC, 2,
    0x301,
    0x300, 0x1E,
    0x200, 0, 2, 2, 1,
    0x101, 2, 7, 3,
    0x301,
    0x101, 2, 1, 3,
    0x300, 0x1E,
    0x200, 0, 3, 0xCC, 2,
    0x301,
    0x200, 0, 4, 2, 1,
    0x101, 2, 7, 3,
    0x301,
    0x101, 2, 1, 3,
    0x300, 0x1E,
    0,
};
s16 script1296[] = {
    0x600, 1, 0xCC,
    0x100, 2, 0x215, 0x2AC,
    0x101, 2, 1, 3,
    0x100, 0xCC, 0x200, 0x2A1,
    0x101, 0xCC, 1, 7,
    0x300, 0x78,
    0x200, 0, 1, 0xCC, 0,
    0x301,
    0x101, FIELD_TASK_COMMANDS, FIELD_COMMAND_ICON3, 2,
    0x300, 0x3C,
    0x200, 0, 2, 2, 3,
    0x101, 2, 7, 3,
    0x301,
    0x101, 2, 1, 3,
    0x101, 0xCC, 1, 3,
    0x300, 0x1E,
    0x102, 0xCC, 0x1D0, 0x288, 3,
    0x302, 0xCC,
    0x101, 0xCC, 1, 7,
    0x300, 0x1E,
    0x102, 2, 0x200, 0x2A1, 3,
    0x302, 2,
    0x101, 2, 1, 3,
    0x300, 0x1E,
    0x200, 0, 3, 0xCC, 2,
    0x301,
    0x600, 1, 2,
    0x300, 0x1E,
    0,
};
s32 partyActorIds[] = {
    2, 4, 8,
};
AnimFrame updateSpritePairFrames_0[] = {
    { 50, 4 }, { 51, 4 }, { 52, 4 }, { 53, 4 },
    { 54, 4 }, { 55, 4 }, { 255, 0x3E7 },
};
AnimFrame updateSpritePairFrames_1[] = {
    { 0x12C, 4 }, { 56, 4 }, { 57, 4 }, { 58, 4 },
    { 59, 4 }, { 60, 4 }, { 61, 4 }, { 62, 4 },
    { 63, 4 }, { 64, 4 }, { 65, 4 }, { 66, 4 },
    { 67, 4 }, { 255, 0x3E7 },
};
AnimFrame *updateSpritePairFrames[] = {
    updateSpritePairFrames_0, updateSpritePairFrames_1,
};
Battle area0Battle0 = { 136, 24, MUSIC(2, 0) };
Battle area0Battle1 = { 136, 24, MUSIC(2, 0) };
Battle area0Battle2 = { 136, 24, MUSIC(2, 0) };
Battle area0Battle3 = { 183, 24, MUSIC(2, 0) };
Battle area0Battle4 = { 183, 24, MUSIC(2, 0) };
Battle area0Battle5 = { 183, 24, MUSIC(2, 0) };
Battle area0Battle6 = { 118, 24, MUSIC(2, 0) };
Battle area0Battle7 = { 118, 24, MUSIC(2, 0) };
BattleList area0Battles = {
    5,
    { &area0Battle0, &area0Battle1, &area0Battle2, &area0Battle3,
      &area0Battle4, &area0Battle5, &area0Battle6, &area0Battle7 },
};
Battle area1Battle0 = { 0, 0, MUSIC(1, 0) };
Battle area1Battle1 = { 0, 0, MUSIC(1, 0) };
Battle area1Battle2 = { 0, 0, MUSIC(1, 0) };
Battle area1Battle3 = { 0, 0, MUSIC(1, 0) };
Battle area1Battle4 = { 0, 0, MUSIC(1, 0) };
Battle area1Battle5 = { 0, 0, MUSIC(1, 0) };
Battle area1Battle6 = { 0, 0, MUSIC(1, 0) };
Battle area1Battle7 = { 0, 0, MUSIC(1, 0) };
BattleList area1Battles = {
    0,
    { &area1Battle0, &area1Battle1, &area1Battle2, &area1Battle3,
      &area1Battle4, &area1Battle5, &area1Battle6, &area1Battle7 },
};
Battle area2Battle0 = { 0, 0, MUSIC(1, 0) };
Battle area2Battle1 = { 0, 0, MUSIC(1, 0) };
Battle area2Battle2 = { 0, 0, MUSIC(1, 0) };
Battle area2Battle3 = { 0, 0, MUSIC(1, 0) };
Battle area2Battle4 = { 0, 0, MUSIC(1, 0) };
Battle area2Battle5 = { 0, 0, MUSIC(1, 0) };
Battle area2Battle6 = { 0, 0, MUSIC(1, 0) };
Battle area2Battle7 = { 0, 0, MUSIC(1, 0) };
BattleList area2Battles = {
    0,
    { &area2Battle0, &area2Battle1, &area2Battle2, &area2Battle3,
      &area2Battle4, &area2Battle5, &area2Battle6, &area2Battle7 },
};
Battle area3Battle0 = { 28, 24, MUSIC(0x23, 0) };
Battle area3Battle1 = { 0, 0, MUSIC(1, 0) };
Battle area3Battle2 = { 0, 0, MUSIC(1, 0) };
Battle area3Battle3 = { 0, 0, MUSIC(1, 0) };
Battle area3Battle4 = { 0, 0, MUSIC(1, 0) };
Battle area3Battle5 = { 0, 0, MUSIC(1, 0) };
Battle area3Battle6 = { 0, 0, MUSIC(1, 0) };
Battle area3Battle7 = { 0, 0, MUSIC(1, 0) };
BattleList area3Battles = {
    0,
    { &area3Battle0, &area3Battle1, &area3Battle2, &area3Battle3,
      &area3Battle4, &area3Battle5, &area3Battle6, &area3Battle7 },
};
FieldBattles stageBattles[] = {
    { 121, 0, 0, { &area0Battles, &area1Battles, &area2Battles, &area3Battles } },
};
ActorImage stageImages[] = {
    { 0x200, 0x100, 0x21C, 0x1A6, 0x70, 0xA6, 0x230, 0x1FE },
    { 0x200, 0x100, 0x200, 0x100, 0, 0, 0x220, 0x1FE },
    { 0x200, 0x100, 0x216, 0x138, 0x58, 0x38, 0x200, 0x1FD },
    { 0x200, 0x100, 0x208, 0x1BC, 0x20, 0xBC, 0x210, 0x1FD },
    { 0x200, 0x100, 0x210, 0x1BC, 0x40, 0xBC, 0x220, 0x1FD },
    { 0x200, 0x100, 0x200, 0x1BC, 0, 0xBC, 0x230, 0x1FD },
    { 0x180, 0x100, 0x180, 0x158, 0x100, 0x58, 0x140, 0x1FB },
    { 0x180, 0x100, 0x1A6, 0x158, 0x198, 0x58, 0x150, 0x1FB },
};
u16 actor2Talk0Conditions[] = { SPECIAL(0x1D), 1, CODES_END };
u16 actor2Talk1Conditions[] = { PROGRESS(0x25), 1, CODES_END };
u16 actor2Talk2Conditions[] = { PROGRESS(0x26), 1, CODES_END };
u16 actor2Talk3Conditions[] = { PROGRESS(0x2B), 1, CODES_END };
u16 actor3Talk0Conditions[] = { SPECIAL(0x1D), 1, CODES_END };
u16 actor3Talk1Conditions[] = { PROGRESS(0x25), 1, CODES_END };
u16 actor3Talk2Conditions[] = { PROGRESS(0x26), 1, CODES_END };
u16 actor3Talk3Conditions[] = { PROGRESS(0x2B), 1, CODES_END };
FieldTalk actor0Talks[] = {
    { NULL, NULL, 0x214 },
    { NULL, NULL, 0 },
};
FieldTalk actor1Talks[] = {
    { NULL, NULL, 0x214 },
    { NULL, NULL, 0 },
};
FieldTalk actor2Talks[] = {
    { actor2Talk0Conditions, NULL, 0x211 },
    { actor2Talk1Conditions, NULL, 0x212 },
    { actor2Talk2Conditions, NULL, 0x213 },
    { actor2Talk3Conditions, NULL, 0x206 },
    { NULL, NULL, 0 },
};
FieldTalk actor3Talks[] = {
    { actor3Talk0Conditions, NULL, 0x211 },
    { actor3Talk1Conditions, NULL, 0x212 },
    { actor3Talk2Conditions, NULL, 0x213 },
    { actor3Talk3Conditions, NULL, 0x215 },
    { NULL, NULL, 0 },
};
u16 actor0Conditions[] = { FLAG(0x40, 0x85), 0, SPECIAL(0x1A), 1, CODES_END };
u16 actor1Conditions[] = { SPECIAL(0x1A), 1, FLAG(0x40, 0x85), 1, CODES_END };
u16 actor2Conditions[] = { SPECIAL(8), 1, FLAG(0x40, 0x85), 0, SPECIAL(0x1A), 0, CODES_END };
u16 actor3Conditions[] = { SPECIAL(8), 1, FLAG(0x40, 0x85), 1, SPECIAL(0x1A), 0, CODES_END };
FieldActorEntry actor0 = { actor0Conditions, actor0Talks, 0x9D, 4, 512, 673, 7 };
FieldActorEntry actor1 = { actor1Conditions, actor1Talks, 0x9D, 4, 464, 648, 7 };
FieldActorEntry actor2 = { actor2Conditions, actor2Talks, 0xCC, 5, 512, 673, 7 };
FieldActorEntry actor3 = { actor3Conditions, actor3Talks, 0xCC, 5, 464, 648, 7 };
FieldActorEntry *stageActors[] = {
    &actor0,
    &actor1,
    &actor2,
    &actor3,
    NULL,
};
StageTile stageObjects[] = {
    { 1, 0, 0x40, 4, 0x50, 1, 0x50, 0x63, 6, 0, 224, 601, 638, 0 },
    { 1, 0, 0x40, 4, 0x50, 1, 0x50, 0x63, 5, 0, 253, 334, 371, 0 },
    { 1, 0, 0x40, 4, 0x50, 1, 0x50, 0x63, 5, 0, 465, 242, 274, 0 },
    { 1, 0, 0x40, 4, 0x50, 1, 0x50, 0x63, 6, 0, 607, 402, 441, 0 },
    { 1, 0, 0x40, 4, 0x50, 1, 0x50, 0x63, 4, 0, 647, 343, 371, 0 },
    { 1, 0, 0x40, 4, 0x50, 1, 0x50, 0x63, 4, 0, 699, 740, 781, 0 },
    { 1, 0, 0x40, 4, 0x50, 1, 0x50, 0x63, 4, 0, 760, 579, 615, 0 },
    { 1, 0, 0x40, 4, 0xA, 1, 0xA, 0x1D, 5, 0, 213, 576, 638, 0 },
    { 1, 0, 0x40, 4, 0xA, 1, 0xA, 0x1D, 6, 0, 267, 297, 371, 0 },
    { 1, 0, 0x40, 4, 0xA, 1, 0xA, 0x1D, 4, 0, 472, 403, 466, 0 },
    { 1, 0, 0x40, 4, 0xA, 1, 0xA, 0x1D, 5, 0, 616, 385, 441, 0 },
    { 1, 0, 0x40, 4, 0xA, 1, 0xA, 0x1D, 6, 0, 855, 692, 756, 0 },
    { 1, 0, 0x40, 4, 0x1E, 1, 0x1E, 0x31, 5, 0, 331, 427, 493, 0 },
    { 1, 0, 0x40, 4, 0x1E, 1, 0x1E, 0x31, 6, 0, 465, 211, 274, 0 },
    { 1, 0, 0x40, 4, 0x1E, 1, 0x1E, 0x31, 4, 0, 698, 429, 493, 0 },
    { 1, 0, 0x40, 4, 0x1E, 1, 0x1E, 0x31, 5, 0, 699, 715, 781, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
StageSlot stageSlots[] = {
    { { { CODES_END, 0 }, { CODES_END, 0 } }, SLOT_EXIT, 0x2D2, 0x70, 0x2EC, 5, 0, 0, 0 },
    { { { CODES_END, 0 }, { CODES_END, 0 } }, SLOT_EXIT, 0x2D4, 0x448, 0x288, 1, 0, 0, 0 },
    { { { FLAG(0x40, 0xBA), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x2328, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0xBB), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x2329, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0xBC), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x232A, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0xBD), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x232B, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0xBE), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x232C, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0xBF), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x232D, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0xC0), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x232E, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0xC1), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x232F, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0xC2), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x2330, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0xC3), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x2331, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0xC4), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x2332, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0xC5), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x2333, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0xC6), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x2334, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0xC7), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x2335, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0xC8), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x2336, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0xC9), 0 }, { CODES_END, 0 } }, SLOT_EVENT, 0x2337, 0, 0, 0, 0, 0, 0 },
    { { { FLAG(0x40, 0x84), 0 }, { SPECIAL(0x1A), 0 } }, SLOT_EVENT, 0x50F, 0, 0, 0, 0, 0, 0 },
    { { { CODES_END, 0 }, { CODES_END, 0 } }, 0, 0, 0, 0, 0, 0, 0, 0 },
};
void (*stageFuncs[])(void) = {
    setupStage,
};
FieldEvent stageEvents[] = {
    { 1295, script1295, EVENT_TEXT(0x15), NULL, endEvent1295 },
    { 1296, script1296, EVENT_TEXT(0x16), NULL, endEvent1296 },
    { 9000, NULL, 0, startEvents9000To9015, endEvent9000 },
    { 9001, NULL, 0, startEvents9000To9015, endEvent9001 },
    { 9002, NULL, 0, startEvents9000To9015, endEvent9002 },
    { 9003, NULL, 0, startEvents9000To9015, endEvent9003 },
    { 9004, NULL, 0, startEvents9000To9015, endEvent9004 },
    { 9005, NULL, 0, startEvents9000To9015, endEvent9005 },
    { 9006, NULL, 0, startEvents9000To9015, endEvent9006 },
    { 9007, NULL, 0, startEvents9000To9015, endEvent9007 },
    { 9008, NULL, 0, startEvents9000To9015, endEvent9008 },
    { 9009, NULL, 0, startEvents9000To9015, endEvent9009 },
    { 9010, NULL, 0, startEvents9000To9015, endEvent9010 },
    { 9011, NULL, 0, startEvents9000To9015, endEvent9011 },
    { 9012, NULL, 0, startEvents9000To9015, endEvent9012 },
    { 9013, NULL, 0, startEvents9000To9015, endEvent9013 },
    { 9014, NULL, 0, startEvents9000To9015, endEvent9014 },
    { 9015, NULL, 0, startEvents9000To9015, endEvent9015 },
    { -1, NULL, 0, NULL, NULL },
};
