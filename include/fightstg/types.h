#ifndef FIGHTSTG_TYPES_H
#define FIGHTSTG_TYPES_H

/* FIGHTSTG's shared declarations: the headers it builds on, the ids its
   tasks register with, and the types the other headers point to first. */

#include "game.h"
#include <libgs.h>
#include "dw3/menu.h"
#include "dw3/file.h"

/* The types that the headers point to before they are defined */
typedef struct BattleScript BattleScript;
typedef union BattleChild BattleChild;

/* The ids that the battle's tasks register with, for the others to find them
   (TASK_REGISTRY.funcs.find) */
#define BATTLE_TASK_MENU 0xC /* WFIGHTMN's battle menu */
#define BATTLE_TASK_PLAYER_TURN 0xE
#define BATTLE_TASK_MODEL 0x11 /* a model (FIGHTSTG_updateModel) */
#define BATTLE_TASK_CAMERA 0x12
#define BATTLE_TASK_LIGHTS 0x13
#define BATTLE_TASK_MODELS 0x14 /* the fighters' */
#define BATTLE_TASK_STAGE 0x15

#endif /* FIGHTSTG_TYPES_H */
