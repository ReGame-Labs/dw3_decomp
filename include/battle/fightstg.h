#ifndef FIGHTSTG_H
#define FIGHTSTG_H

/* FIGHTSTG.PRO: the battle. It loads WFIGHTMN (file 0x1FA) for a normal
   battle, or WFIGHTTS (file 0x1FB) for the battle test, at STAGE_VRAM.
   Its declarations are in include/battle/fightstg/, by module; this header
   includes them all. */

#include "battle/fightstg/types.h"
#include "battle/fightstg/model.h"
#include "battle/fightstg/stage.h"
#include "battle/fightstg/camera.h"
#include "battle/fightstg/effect.h"
#include "battle/fightstg/battle.h"
#include "battle/fightstg/action.h"
#include "battle/fightstg/menu.h"
#include "battle/fightstg/task.h"

/* The name of this overlay's copy of a function of src/shared/ */
#define OVL_NAME(name) FIGHTSTG_##name

/* The sub-overlays (FIGHTSTG_updateRoot) and their entry points */
#if VERSION_US
#define FILE_WFIGHTMN 0x1FA
#define FILE_WFIGHTTS 0x1FB
#elif VERSION_EU
#define FILE_WFIGHTMN 0x208
#define FILE_WFIGHTTS 0x209
#endif
Task *WFIGHTMN_start(void);
Task *WFIGHTTS_start(void);
/* WFIGHTMN's functions FIGHTSTG calls */
BattleScript *WFIGHTMN_startTech(u8 actor, s32 id);
void WFIGHTMN_checkEquip(s32 fighter);
void WFIGHTMN_chargeGauge(u8 side, s32 damage);
s32 WFIGHTMN_setIdleMotion(u8 id, s32 damage);
void WFIGHTMN_countHit(u8 side, s32 damage);
void WFIGHTMN_endWeakness(u8 side);
s32 WFIGHTMN_limitDamage(u8 side, s32 damage, s32 hits);

#endif /* FIGHTSTG_H */
