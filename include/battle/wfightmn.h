#ifndef WFIGHTMN_H
#define WFIGHTMN_H

/* WFIGHTMN.PRO: the battle's sub-overlay. FIGHTSTG loads it (file 0x1FA)
   at STAGE_VRAM for a normal battle, and WFIGHTTS in its place for the
   battle test. */

#include "battle/fightstg.h"

/* The item a partner can equip that makes FIGHTSTG's FIGHTSTG_queueRecovery act on
   it at the start of the battle */
#define WFIGHTMN_ITEM 0x140

/* The battle menu (WFIGHTMN_start), registered as BATTLE_TASK_MENU */
typedef struct BattleMenu {
    TASK_HEADER(BattleMenu);
    /* 0x50 */ s32 args[8]; /* the message's arguments */
    /* 0x70 */ s32 confusionSound;
} BattleMenu;

/* The task that loads the battle menu's files (WFIGHTMN_createLoader) */
typedef struct BattleLoader {
    TASK_HEADER(BattleLoader);
    /* 0x50 */ s32 pad; /* nothing uses it */
} BattleLoader;

/* The battle menu's children */
typedef struct BattleMenuChildren {
    /* 0x00 */ BattleLoader *loader;
    /* 0x04 */ PlayerTurn *commands; /* the player's turn (FIGHTSTG_startPlayerTurn) */
    /* 0x08 */ BattleCamera *camera; /* FIGHTSTG_createBattleCamera */
    /* 0x0C */ Lights *lights;
    /* 0x10 */ FightStage *stage;
    /* 0x14 */ Models *models;
    /* 0x18 */ BattleChild cameraMove; /* the European version's shots, or the turn when the player loses */
    /* 0x1C */ BattleChild task; /* what the state waits for, NULL when done */
} BattleMenuChildren;

/* The screen its layers cover */
extern RECT WFIGHTMN_screen;
/* A technique's look by its effect and by its element, for WFIGHTMN_bringLastEnemy */
extern s32 WFIGHTMN_effectVisuals[][3];
extern s32 WFIGHTMN_elementVisuals[][4];
/* WFIGHTMN_startTech's effects */
extern s32 WFIGHTMN_actionEffects[][2];
/* The battle menu's states, by its substate */
extern void (*WFIGHTMN_states[])(BattleMenu *task, BattleMenuChildren *children);

BattleLoader *WFIGHTMN_createLoader(void);

/* setup.c */
void WFIGHTMN_createLayers(void);
void WFIGHTMN_initFighters(s32 digimon);
s32 WFIGHTMN_rollAmbush(void);
void WFIGHTMN_checkParty(void);
void WFIGHTMN_markFought(void);
void WFIGHTMN_markPicked(BattleMenu *task, BattleMenuChildren *children);

/* menu.c */
void WFIGHTMN_cancelBlast(void);
void WFIGHTMN_runTurn(BattleMenu *task);
/* The states in WFIGHTMN_states */
void WFIGHTMN_runCommand(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_digivolve(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_tag(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_pairTech(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_endBattle(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_runAway(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_endAutoRecover(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_recover(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_clearField(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_takeDamage(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_cureStatus(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_endBoost(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_runConfusedCommand(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_endRestriction(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_blast(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_endBlast(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_knockOut(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_endSpecial(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_digidevolve(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_showWon(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_bringLastEnemy(BattleMenu *task, BattleMenuChildren *children);
void WFIGHTMN_restoreEnemy(BattleMenu *task, BattleMenuChildren *children);

#endif /* WFIGHTMN_H */
