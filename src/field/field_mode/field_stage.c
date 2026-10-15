/* The field's own stage: the ends of its events and its setup */

#include "field/field_mode.h"

/* The ends of the events of question n's answers (FIELDSTG_events): both set
   event flag 0x400 + n, and the first answer's also applies a, the auction's
   price (SPECIAL_LOSE_*_BIT), and b */
#define END_CHOICE(n, a, b)                     \
    void FIELDSTG_endChoice##n##Answer0(void) { \
        FLAGS_00.applyAction(a, 1);             \
        FLAGS_00.applyAction(b, 1);             \
        FLAGS_00.applyAction(0x400 + n, 1);     \
    }                                           \
                                                \
    void FIELDSTG_endChoice##n##Answer1(void) { \
        FLAGS_00.applyAction(0x400 + n, 1);     \
    }

END_CHOICE(0, SPECIAL_LOSE_800_BIT, 0x8B19)
END_CHOICE(1, SPECIAL_LOSE_800_BIT, 0x8B1F)
END_CHOICE(2, SPECIAL_LOSE_1600_BIT, 0x8B1A)
END_CHOICE(3, SPECIAL_LOSE_1600_BIT, 0x8B20)
END_CHOICE(4, SPECIAL_LOSE_2700_BIT, 0x8489)
END_CHOICE(5, SPECIAL_LOSE_2700_BIT, 0x8495)
END_CHOICE(6, SPECIAL_LOSE_4000_BIT, 0x847C)
END_CHOICE(7, SPECIAL_LOSE_4000_BIT, 0x8462)
END_CHOICE(8, SPECIAL_LOSE_6000_BIT, 0x8ADE)
END_CHOICE(9, SPECIAL_LOSE_6000_BIT, 0x8AE8)
END_CHOICE(10, SPECIAL_LOSE_8700_BIT, 0x8AF4)
END_CHOICE(11, SPECIAL_LOSE_8700_BIT, 0x8AF3)
END_CHOICE(12, SPECIAL_LOSE_11500_BIT, 0x8B01)
END_CHOICE(13, SPECIAL_LOSE_17500_BIT, 0x8B0D)
END_CHOICE(14, SPECIAL_LOSE_24000_BIT, 0x8B02)
END_CHOICE(15, SPECIAL_LOSE_32000_BIT, 0x8B0F)

/* The color the field's stage starts with (FieldState.spriteColor) */
const CVECTOR FIELDSTG_startColor = {0x80, 0x80, 0x80, 0};

#if VERSION_US || VERSION_JP
#define FIELD_FILE 0x19F
#elif VERSION_EU
#define FIELD_FILE 0x1AD
#endif

/*
 * The setup of the field's own stage (FIELDSTG_initFuncs), which fills
 * FIELDSTG_state as the stage overlays' setup functions do; some points of the
 * story change its soundBank and music. As theirs, the match depends on the
 * start position being set with a constructor, (Vec2){x, y}.
 */
void FIELDSTG_setupField(void) {
#if VERSION_US || VERSION_JP
    FIELDSTG_state.textFile = TEXT_FILE(TEXT_TALKS_05);
#endif
    FIELDSTG_state.mapFile = FIELD_FILE - 1;
    FIELDSTG_state.sheetEntry = FIELD_FILE << 16;
    FIELDSTG_state.objects = FIELDSTG_mapObjects;
    FIELDSTG_state.slots = FIELDSTG_slots;
#if VERSION_US || VERSION_JP
    FIELDSTG_state.imageFile = 0x31D;
#elif VERSION_EU
    FIELDSTG_state.imageFile = 0x32C;
    FIELDSTG_state.textFile = TEXT_FILE(TEXT_TALKS_05);
#endif
    FIELDSTG_state.start = (Vec2){0x6700, 0x12300};
    FIELDSTG_state.images.field = &FIELDSTG_images.field;
    FIELDSTG_state.soundBank = MUSIC_BANK(MUSIC_CARGO_TOWER);
    FIELDSTG_state.actors = FIELDSTG_actorList;
    FIELDSTG_state.startDir = 0;
    FIELDSTG_state.music = MUSIC_CARGO_TOWER;
    FIELDSTG_state.spriteColor = FIELDSTG_startColor;
    FIELDSTG_state.events = FIELDSTG_events;
    FIELDSTG_map.setFile(0, FIELD_FILE << 16 | 2);
    FIELDSTG_map.setFile(1, FIELD_FILE << 16 | 3);
    FIELDSTG_map.setFile(FIELD_MAP_TRIGGERS, FIELD_FILE << 16 | 1);
    FIELDSTG_map.setFirstMap(0);
    switch (GAME.progress) {
    case STORY_SEIRYU_BADGE:
    case STORY_SEPIKMON_MASK_LOST:
    case STORY_LOOKING_FOR_TEDDY:
    case STORY_TEDDY_FOUND:
    case STORY_NUMEMON_FOUND:
    case STORY_CONTROL_ROOM:
    case STORY_KNIGHTMON_REPROGRAMMED:
    case STORY_BULBMON_FOUND:
    case STORY_BLUE_ID_PASS:
    case STORY_DE_KNOWLEDGE:
    case STORY_GENBU_BADGE:
    case STORY_WAY_TO_AMATERASU:
    case STORY_BLACK_ID_PASS:
    case STORY_AMATERASU_BRIDGE:
    case STORY_PRESIDENT_ARRESTED:
    case STORY_ASUKA_HEADQUARTERS:
        FIELDSTG_state.soundBank = MUSIC_BANK(MUSIC_EAUCTION);
        FIELDSTG_state.music = MUSIC_EAUCTION;
        break;
    }
}
