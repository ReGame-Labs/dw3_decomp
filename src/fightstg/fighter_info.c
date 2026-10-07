/* FIGHTSTG's fighter data, loaded into FIGHTSTG_fighterCache. */

#include "fightstg.h"

/* the match depends on reaching the cache through the symbol until a fighter
   is found, and on each branch storing and returning its own info */
FighterInfo *FIGHTSTG_getFighterInfo(s32 id) {
    FightersFile *file;
    FighterEntry *entry;
    u8 *partners;
    u8 *enemies;
    FighterCache *cache;
    FighterInfo *info;
    s32 i;

    if (id == FIGHTSTG_fighterCache.id) {
        if (FIGHTSTG_fighterCache.isEnemy) {
            return FIGHTSTG_fighterCache.enemyInfo;
        }
        return FIGHTSTG_fighterCache.partnerInfo;
    }
    file = (FightersFile *)FILE_CACHE.load(FILE_FIGHTERS);
    entry = (FighterEntry *)((u8 *)file + file->entries);
    partners = (u8 *)file + file->partners;
    enemies = (u8 *)file + file->enemies;
    while (entry->id != 0) {
        if (entry->id == id) {
            FIGHTSTG_fighterCache.id = id;
            cache = &FIGHTSTG_fighterCache;
            cache->index = i = entry->index;
            cache->kind = entry->kind;
            cache->isEnemy = entry->kind >= 0x3A;
            if (cache->isEnemy) {
                info = (FighterInfo *)(enemies + i * 0x48);
                cache->partnerInfo = info;
                cache->enemyInfo = info;
                return info;
            } else {
                info = (FighterInfo *)(partners + i * 0xC4);
                cache->partnerInfo = info;
                cache->enemyInfo = info;
                return info;
            }
        }
        entry++;
    }
    return NULL;
}

/* Loads entry index of the fighters file into FIGHTSTG_fighterCache: its id
   and kind, and its info, an enemy's from kind 0x3A on or else a partner's */
void FIGHTSTG_cacheFighter(s32 index) {
    FightersFile *file = (FightersFile *)FILE_CACHE.load(FILE_FIGHTERS);
    FighterEntry *entries = (FighterEntry *)((u8 *)file + file->entries);
    u8 *partners = (u8 *)file + file->partners;
    u8 *enemies = (u8 *)file + file->enemies;
    FighterEntry *entry = &entries[index];
    FighterInfo *info;
    s32 i;
    FighterCache *cache = &FIGHTSTG_fighterCache;

    cache->id = entry->id;
    cache->index = i = entry->index;
    cache->kind = entry->kind;
    cache->isEnemy = entry->kind >= 0x3A;
    if (cache->isEnemy == 0) {
        info = (FighterInfo *)(partners + i * 0xC4);
    } else {
        info = (FighterInfo *)(enemies + i * 0x48);
    }
    cache->partnerInfo = info;
    cache->enemyInfo = info;
}

/* Fighter id's face parts (FaceRect), in the fighters file */
FaceRect *FIGHTSTG_getFighterFace(s32 id) {
    s32 *file = (s32 *)FILE_CACHE.load(FILE_FIGHTERS);

    return (FaceRect *)(FIGHTSTG_getFighterInfo(id)->face - file[0] + (s32)file);
}

/* The first and last entries of the fighters file that are enemies (enemy
   set) or partners */
void FIGHTSTG_getFighterRange(u32 enemy, s32 *min, s32 *max) {
    FightersFile *file = (FightersFile *)FILE_CACHE.load(FILE_FIGHTERS);
    FighterEntry *entry = (FighterEntry *)((u8 *)file + file->entries);
    s32 lo = 0xFF;
    s32 hi = 0;
    s32 i = 0;

    while (entry->id != 0) {
        if ((entry->kind >= 0x3A) == enemy) {
            if (i < lo) {
                lo = i;
            }
            if (hi < i) {
                hi = i;
            }
        }
        entry++;
        i++;
    }
    *min = lo;
    *max = hi;
}
