#ifndef DW3_SOUND_H
#define DW3_SOUND_H

/* Sound banks (sound/) */

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

/*
 * Sound ids pack everything needed to play them:
 *   bit 31     a key-on of one VAB tone (sound effect), else a SEP sequence
 *   bit 30     exclusive (music): stops the previous exclusive sound
 *   bits 18-24 the sound bank id (see findSoundBank)
 *   key-on:    program bits 11-17, tone bits 7-10, note bits 0-6
 *   sequence:  SEQ bits 8-15, track (SEP) bits 0-7
 */
#define SOUND_IS_KEY_ON(id) ((u32)(id) >> 31)
#define SOUND_IS_EXCLUSIVE(id) (((id) >> 30) & 1)
#define SOUND_BANK(id) (((id) >> 18) & 0x7F)
#define SOUND_PROG(id) (((id) >> 11) & 0x7F)
#define SOUND_TONE(id) (((id) >> 7) & 0xF)
#define SOUND_NOTE(id) ((id) & 0x7F)
#define SOUND_SEQ(id) (((id) >> 8) & 0xFF)
#define SOUND_SEP(id) ((id) & 0xFF)

/* The banks loaded at once: slot 0 keeps bank 1 (system sounds), 1 and 2 alternate */
#define SOUND_SLOT_COUNT 3

/* The tracks (SEPs) of each SEQ */
#define SOUND_SEP_COUNT 16

/* The loudest volume of a voice or track */
#define SOUND_VOLUME_MAX 0x7F

/* Sounds the overlays share, with SOUNDTST's names */
#define SOUND_SELECT 0x8004503C /* SYSTEM00: a choice is taken */
#define SOUND_MENU_CANCEL 0x800450BD /* SYSTEM01 */
#define SOUND_CURSOR 0x8004513E /* SYSTEM02: a cursor moves */
#define SOUND_MENU_OPEN 0x40019 /* SYSTEM03 */
#define SOUND_MENU_CLOSE 0x4001A /* SYSTEM04 */
#define SOUND_MENU_MOVE 0x4001B /* SYSTEM06 */
#define SOUND_MENU_CONFIRM 0x4001C /* SYSTEM07 */
#define SOUND_COUNT 0x800452C6 /* SYSTEM10: a number counts up or down */
#define SOUND_RECOVERY 0x40014 /* RECOVERY */
#define SOUND_TELEPORT 0x4001D /* TELEPORT */
#define SOUND_WIN_JINGLE 0x6004001E /* W_JINGLE: a battle won */
#define SOUND_INN_JINGLE 0x4004000D /* JINGLE04: a night at the inn */
#define SOUND_SWITCH01 0x8004103C
#define SOUND_SWITCH02 0x800410BD
#define SOUND_SWITCH03 0x8004113E
#define SOUND_COMCD103 0x800429BF
#define SOUND_COMCD115 0xA0042FCB /* held until SOUND.keyOff */
#define SOUND_COMEX113 0x800446C9
#define SOUND_PLAYER11 0xA0045EC9 /* held until SOUND.keyOff */
#define SOUND_SYSTEM05 0x80045341
#define SOUND_GONDRA_S 0x340004
#define SOUND_SE000002 0xA40006
#define SOUND_ELEVATER 0x1080001
#define SOUND_CARD_001 0x800460BD

/*
 * A field's or a battle's music (FieldState.music, Battle.music): track
 * (SEP) n of the first sequence of a sound bank, exclusive (bit 30) and with
 * bit 29, which playSound doesn't read but every one of SOUNDTST's tunes
 * has, and its loops (BT_LOOP0, EX_AT_LP), not its jingles. A stage's music
 * is of the bank it loads (FieldState.soundBank, MUSIC_BANK).
 */
#define MUSIC(bank, n) (0x60000000 | (bank) << 18 | (n))

/* The music by where the game plays it (FieldState.music, AreaBattle.music, the
   screens'), each with SOUNDTST's name for it */
#define MUSIC_CONFUSION MUSIC(1, 0) /* COM_CNFS: in a battle while a partner is confused (WFIGHTMN switchConfusionMusic) */
#define MUSIC_GAME_OVER MUSIC(1, 8) /* GAMEOVER: a battle lost (WFIGHTMN endBattleOnKnockOut) */
#define MUSIC_BATTLE MUSIC(2, 0) /* BATL0000: the maps' random battles (AreaBattle, nearly all of them) */
#define MUSIC_BATTLE_1 MUSIC(3, 0) /* BATL1000: the Digimon Arena's battles and some event battles (AreaBattle) */
#define MUSIC_ASUKA_CITY MUSIC(4, 0) /* ASKA_BGM: the Central Sector's streets and bridges, the Underground Path */
#define MUSIC_ADMIN_CENTER MUSIC(5, 0) /* KANRIBGM: the cities' Main Lobby, Admin Center, Digimon Arena, Master Room */
#define MUSIC_SEWERS MUSIC(6, 0) /* BGM_0003: the Admin Center's basement and the cities' sewers */
#define MUSIC_SHOP_1 MUSIC(7, 0) /* SHOP1BGM: the inns, shops and towers */
#define MUSIC_SHOP_2 MUSIC(8, 0) /* SHOP2BGM: Lamb Chop, the Yellow Cruiser and El Dorado */
#define MUSIC_FIELD MUSIC(9, 0) /* FIELDBGM: Central Park, the Wire Forest Entrance, Shell Beach, Plug Cape */
#define MUSIC_DUEL_ISLAND MUSIC(0xA, 0) /* BGM_0008: Duel Island */
#define MUSIC_PROTOCOL_RUINS MUSIC(0xB, 0) /* PYRA_BGM: the Protocol Ruins */
#define MUSIC_SEIRYU_CITY MUSIC(0xC, 0) /* SEIR_BGM: Seiryu City */
#define MUSIC_MAGASTA MUSIC(0xD, 0) /* BGM_0011: the Undersea Base (Magasta), and the Deeper Crevice's gondola */
#define MUSIC_STATION MUSIC(0xE, 0) /* BGM_0012: the East and South Stations */
#define MUSIC_SHAMAN_HOUSE MUSIC(0xF, 0) /* BGM_0013: the Shaman House */
#define MUSIC_RELIABILITY_SPOT MUSIC(0x10, 0) /* BGM_0014: the Reliability Spot */
#define MUSIC_JUNGLE_SHRINE MUSIC(0x11, 0) /* BGM_0015: the Jungle Grave, the Jungle Shrine and the Catacomb */
#define MUSIC_SUZAKU_CITY MUSIC(0x12, 0) /* BGM_0016: Suzaku City and its Hall */
#define MUSIC_BUG_MAZE MUSIC(0x13, 0) /* BGM_0017: the Bug Maze (Network Break) */
#define MUSIC_BADLAND MUSIC(0x14, 0) /* BGM_0018: the Badlands */
#define MUSIC_SECRET_ROOM MUSIC(0x15, 0) /* BGM_0019: the Secret Room, the rebels' hideout */
#define MUSIC_MIRAGE_HALL MUSIC(0x16, 0) /* BGM_0020: the Mirage Hall and Mirage Room */
#define MUSIC_BYAKKO_CITY MUSIC(0x17, 0) /* BGM_0021: Byakko City and the Bai Hu Dome */
#define MUSIC_LEGENDARY_GYM MUSIC(0x18, 0) /* BGM_0022: the Legendary Gym */
#define MUSIC_DUNGEON MUSIC(0x19, 0) /* BGM_0023: the Ice, Fire and Dark Dungeons */
#define MUSIC_GENBU_CITY MUSIC(0x1A, 0) /* BGM_0024: Genbu City */
#define MUSIC_ONLINE_CENTER MUSIC(0x1B, 0) /* ON_CNBGM: MAGAMI's Online Center */
#define MUSIC_GUNSLINGER MUSIC(0x1C, 0) /* BGM_0026: the Gunslinger (the Spy Satellite) */
#define MUSIC_SEABED MUSIC(0x1D, 0) /* BGM_0027: the Seabed tunnels */
#define MUSIC_CIRCUIT_BOARD MUSIC(0x1E, 0) /* BGM_0028: the Circuit Board tunnels */
#define MUSIC_CITY_CRISIS MUSIC(0x1F, 0) /* BGM_0029: the cities and their streets instead of their music while the story is at a crisis (Knightmon reprogrammed, the A.o.A's headquarters, the Amaterasu server's Oinkmon) */
#define MUSIC_MEMORY_CARD MUSIC(0x20, 0) /* BGM_0030: the memory card screen and the player's name entry */
#define MUSIC_TRAINING MUSIC(0x21, 2) /* TRAINING: the gym's training */
#define MUSIC_BOSS MUSIC(0x22, 0) /* BOSS_000: the sectors' boss battles */
#define MUSIC_BOSS_1 MUSIC(0x23, 0) /* BOSS_001: the Digimon Arena's, the cities', the dungeons' and the A.o.A's boss battles */
#define MUSIC_LAST_BOSS MUSIC(0x24, 0) /* LASTBOSS: Lord Megadeath's battle (WSTAG820) */
#define MUSIC_LAST_BOSS_1 MUSIC(0x25, 0) /* LASTB_01: the extra chapter's last battle (WSTAG927, the Digimon Arena) */
#define MUSIC_LAST_BOSS_2 MUSIC(0x26, 0) /* LASTB_02: Lord Megadeath's second form (WSTAG820, fighter 0x1D3's entrance) */
#define MUSIC_CARD_BATTLE MUSIC(0x27, 4) /* CBTLMAIN: the card battles */
#define MUSIC_STREET_CORNER MUSIC(0x29, 0) /* BGM00000: the Street Corner (Kusanagi City) */
#define MUSIC_STREET_CORNER_1 MUSIC(0x29, 1) /* BGM00001: the Street Corner at STORY_JUNGLE_SOUND */
#define MUSIC_STREET_CORNER_2 MUSIC(0x29, 2) /* BGM00002: the Street Corner at STORY_REAL_WORLD */
#define MUSIC_STREET_CORNER_3 MUSIC(0x29, 3) /* BGM00003: the Street Corner at STORY_ASUKA_HEADQUARTERS */
#define MUSIC_AOA_HEADQUARTERS MUSIC(0x2A, 0) /* ENV_0002: the A.o.A Headquarters */
#define MUSIC_CONTROL_ROOM MUSIC(0x2B, 0) /* ENV_0003: the cities' Control Room */
#define MUSIC_WATER_TUNNEL MUSIC(0x2C, 0) /* ENV_0004: the Water Tunnel */
#define MUSIC_WIRE_FOREST MUSIC(0x2D, 0) /* ENV05_00: the Wire Forests and the Kicking Forest */
#define MUSIC_WIND_PRAIRIE MUSIC(0x2E, 0) /* ENV_0006: the Wind Prairie */
#define MUSIC_TYRANNO_VALLEY MUSIC(0x2F, 0) /* ENV_0007: Tyranno Valley, Snow Mountain, Kulon Mine and the Battle Gate */
#define MUSIC_GALE_TOWER MUSIC(0x30, 0) /* ENV_0008: the Gale Tower */
#define MUSIC_FOREST_INN_BF MUSIC(0x31, 0) /* ENV_0009: the Forest Inn's basement */
#define MUSIC_PROTOCOL_FOREST MUSIC(0x32, 0) /* ENV10_00: the Protocol Forest */
#define MUSIC_DIGIMON_LAB MUSIC(0x33, 0) /* ENV_0011: Asuka's Digimon Lab and Login Room */
#define MUSIC_SWAMP MUSIC(0x34, 0) /* ENV_0012: the South Sector's swamps and Bulk Bridge */
#define MUSIC_ETHER_JUNGLE MUSIC(0x35, 0) /* ENV_0013: the Ether Jungle */
#define MUSIC_COAST MUSIC(0x36, 0) /* ENV_0014: Shell Beach, Plug Cape, Phoenix Bay and South Cape */
#define MUSIC_UG_LAKE MUSIC(0x37, 0) /* ENV_0015: the UG Lake */
#define MUSIC_DESERT MUSIC(0x38, 0) /* ENV_0016: the West Sector's deserts and the Mirage Tower */
#define MUSIC_DUM_DUM_FACTORY MUSIC(0x39, 0) /* ENV_0017: Bullet Valley, the Dum Dum Factory, its Duct Rooms and Operation Room */
#define MUSIC_WEST_SEWERS MUSIC(0x3A, 0) /* ENV_0018: the West Sector's Sewers and Secret Stairs */
#define MUSIC_STORAGE_ROOM MUSIC(0x3B, 0) /* ENV_0019: Byakko City's Storage Room */
#define MUSIC_UNDERGROUND_CAVE MUSIC(0x3C, 0) /* ENV_0020: the Underground Cave */
#define MUSIC_BOOT_MOUNTAIN MUSIC(0x3D, 0) /* ENV_0021: Boot Mountain, and the Byakko Dome */
#define MUSIC_FREEZE_MOUNTAIN MUSIC(0x3E, 0) /* ENV_0022: Freeze Mountain and the Lake of Ice */
#define MUSIC_KULON_PIT MUSIC(0x3F, 0) /* ENV_0023: the Kulon Pit */
#define MUSIC_CHAMBER_ROOM MUSIC(0x40, 1) /* ENV_0024: the Chamber Rooms */
#define MUSIC_PELCHE_OASIS MUSIC(0x41, 0) /* ENV_0025: the Pelche Oasis */
#define MUSIC_EAUCTION MUSIC(0x42, 0) /* EAUCTION: the Cargo Tower at some points of the story (FIELDSTG_setupField) */
#define MUSIC_CARGO_TOWER MUSIC(0x42, 2) /* ENV_0204: the Cargo Tower */
#define MUSIC_MAIN_LOBBY_DEMO MUSIC(0x43, 3) /* ENV_0205: the story events' copy of Asuka's Main Lobby (WSTAG212) */
#define MUSIC_SATELLITE_CONTROL_ROOM MUSIC(0x44, 1) /* ENV_0206: the Spy Satellite's Control Room */

/* The sound bank of a music, which a stage loads for it (FieldState.soundBank) */
#define MUSIC_BANK(music) ((music) >> 18 & 0x7F)

/* One of the SOUND_SLOT_COUNT loaded sound banks: a VAB and its SEP sequences */
typedef struct SoundBank {
    /* 0x00 */ s32 id;
    /* 0x04 */ s16 vabId;
    /* 0x06 */ s16 numSeqs;
    /* 0x08 */ s16 seqs[4];
    /* 0x10 */ void *headBuffer; /* VAB header and SEPs are copied here */
    /* 0x14 */ s32 spuAddr;
} SoundBank;

/* A bank's files (SOUND_BANK_FILES[id]) */
typedef struct SoundFiles {
    /* 0x00 */ s32 bodyFile; /* VAB body, sent to the SPU */
    /* 0x04 */ s32 headFile; /* archive: VAB header and SEPs */
    /* 0x08 */ s32 vhIndex; /* of the VAB header in headFile */
    /* 0x0C */ s32 bodyEntry; /* (file << 16) | slot */
    /* 0x10 */ s32 seps[FLEXIBLE]; /* indices in headFile, 0-terminated */
} SoundFiles;

/* SoundLoader.state: waiting for the header file, the body file, then the SPU */
enum SoundLoadState { SOUND_LOAD_IDLE, SOUND_LOAD_HEAD, SOUND_LOAD_BODY, SOUND_LOAD_TRANSFER };

/* Loads a bank in the background (updateSoundLoading) */
typedef struct SoundLoader {
    /* 0x0 */ SoundFiles *files;
    /* 0x4 */ s16 state; /* SOUND_LOAD_* */
    /* 0x6 */ s16 slot;
} SoundLoader;

/* The sound engine (SOUND) */
typedef struct SoundState {
    /* 0x0000 */ u8 seqTable[0x4200]; /* SsSetTableSize(6 SEQs, 16 SEPs) */
    /* 0x4200 */ SoundBank banks[SOUND_SLOT_COUNT];
    /* 0x4248 */ s32 music; /* the exclusive sound playing */
    /* 0x424C */ s32 lastSlot;
    /* 0x4250 */ SoundLoader loader;
    /* 0x4258 */ void (*init)(void);
    /* 0x425C */ short (*playSound)(s32 id); /* returns the voice of a key-on */
    /* 0x4260 */ short (*keyOn)(s32 slot, short prog, short note);
    /* 0x4264 */ void (*keyOff)(s32 id, s16 voice);
    /* 0x4268 */ void (*loadBank)(s32 id);
    /* 0x426C */ void (*loadBankInto)(s32 slot, s32 id);
    /* 0x4270 */ void (*updateLoading)(void);
    /* 0x4274 */ s32 (*isLoading)(void);
    /* 0x4278 */ void (*stopAll)(void);
    /* 0x427C */ void (*stopSound)(s32 id);
    /* 0x4280 */ void (*fadeOut)(s32 id);
} SoundState;

s32 findSoundBank(s32 id);
short playSound(s32 packed);
void stopAllSounds(void);
void stopSound(s32 packed);
void fadeOutSound(s32 packed);
s32 isSoundLoading(void);
void loadSoundBankInto(s32 index, s32 id);
void loadSoundBank(s32 id);
void updateSoundLoading(void);
short soundKeyOn(s32 slot, short prog, short note);
void soundKeyOff(s32 packed, s16 voice);
void initSound(void);

extern SoundState SOUND;
extern SoundFiles *SOUND_BANK_FILES[];
extern s32 SOUND_SPU_ADDRS[];
extern void *SOUND_HEAD_BUFFERS[];

#endif /* DW3_SOUND_H */
