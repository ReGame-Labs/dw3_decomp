/* What FIGHTSTG asks WFIGHTMN about techniques: the final battles' records,
   the gauge, the start of a technique and its idle motions, and the damage
   limits of the special battles. */

#include "wfightmn.h"

/* In BATTLE_KIND_FINAL, keeps the partner's technique ID in
   FIGHTSTG_battle.tech when its unk10 is not 5 or 12 and it has an effect
   (its kind is not 0-1, 9-10 or 12, or its unk7 is 2 or more);
   WFIGHTMN_bringLastEnemy makes technique 440 from it */
void WFIGHTMN_recordTech(u8 side, s32 id) {
    TechData *info = &TECHS[id - 1];
    s32 flag;
    u8 kind;

    if (side == 0 && FIGHTSTG_battle.kind == BATTLE_KIND_FINAL) {
        flag = 0;
        if (info->unk10 != 5 && info->unk10 != 12) {
            kind = info->effect;
            if (!(kind <= 1 || (kind >= 9 && kind <= 10) || kind == 12)) {
                flag = 1;
            }
            if (info->element >= ELEMENT_FIRST) {
                flag = 1;
            }
            if (flag) {
                FIGHTSTG_battle.tech = id;
            }
        }
    }
}

/* Adds what damage gives to the current partner's gauge
   (BATTLE_SETUP.gauges), up to 1000 */
void WFIGHTMN_chargeGauge(u8 side, s32 damage) {
    BattleFighter *unit = &FIGHTSTG_battle.fighters[0][FIGHTSTG_battle.active[0]];
    s32 member = GAME.funcs.getPartyMember(FIGHTSTG_battle.active[0]);

    if (side != 0 && damage != 0 && unit->hp != 0 && unit->temporary == 0) {
        BATTLE_SETUP.gauges[member] += FIGHTSTG_battleFuncs.getGaugeGain(damage);
        if (BATTLE_SETUP.gauges[member] >= 1000) {
            BATTLE_SETUP.gauges[member] = 1000;
            FIGHTSTG_queueBlast();
        }
    }
}

/* Starts the effect of actor's move id (FIGHTSTG's FIGHTSTG_createBattleScript): its kind
   and motions from TECHS, which hits land from FIGHTSTG_action, then sets
   the fighters' idle motions for the damage it does */
BattleScript *WFIGHTMN_startTech(u8 actor, s32 id) {
    TechData *info;
    s32 side;
    BattleStats *own;
    BattleStats *other;
    BattleScript *task;
    BattleFighter *units;
    s32 damage;
    s32 i;
    s32 j;

    side = actor != 0;
    info = &TECHS[id - 1];
    own = FIGHTSTG_battleFuncs.computeStats(actor, 1, FIGHTSTG_battle.active[side]);
    other = FIGHTSTG_battleFuncs.computeStats(SIDE_ENEMY - actor, 0, FIGHTSTG_battle.active[1 - side]);
    task = FIGHTSTG_createBattleScript();
    task->enemy = actor;
    if (actor == 0) {
        if (info->unk10 == 5) {
            if (own->tripleHit != 0) {
                task->index = 8;
                task->effect = info->unkE;
                task->sound = info->unkF;
            } else {
                for (i = 2; i < 13; i++) {
                    if (FIGHTSTG_action.effects[i] != 0) {
                        task->index = 6;
                        {
                            s32 (*table)[2] = WFIGHTMN_actionEffects; /* match depends on the pointer */

                            j = i - 2;
                            task->effect = table[j][0];
                            task->sound = table[j][1];
                        }
                        break;
                    }
                }
                if (task->index == 0) {
                    for (i = 0; i < 3; i++) {
                        if (own->weaponFamilies[i] >= FAMILY_FIRST && own->weaponFamilies[i] == other->family) {
                            task->index = 6;
                            task->effect = info->unkE;
                            task->sound = info->unkF;
                            break;
                        }
                    }
                    if (task->index == 0) {
                        task->index = info->unk10;
                        task->effect = info->unkE;
                        task->sound = info->unkF;
                    }
                }
            }
        } else {
            if (info->effect < TECH_EFFECT_FIRST && info->icon == TECH_PHYSICAL && info->unk10 == 6 && own->tripleHit != 0) {
                task->index = 8;
            } else {
                task->index = info->unk10;
            }
            task->effect = info->unkE;
            task->sound = info->unkF;
            if (info->element >= ELEMENT_FIRST || (info->family >= FAMILY_FIRST && info->family == other->family)) {
                task->stage = info->unkD;
            } else {
                task->stage = -1;
            }
        }
        if (task->stage <= 0) {
            if (own->element >= ELEMENT_FIRST) {
                s32 n;
                s32 m;

                if (info->element >= ELEMENT_FIRST) {
                    n = info->element - ELEMENT_FIRST;
                } else {
                    n = own->element - ELEMENT_FIRST;
                }
                m = n * 3 + 0x21;
                if (own->elementPower >= 0x40) {
                    task->stage = m + 1;
                } else {
                    task->stage = m;
                }
            } else if (info->family < FAMILY_FIRST) {
                for (i = 0; i < 3; i++) {
                    if (own->weaponFamilies[i] == 2 && other->family == 2) {
                        task->stage = 0x35;
                        break;
                    }
                    if (own->weaponFamilies[i] == 10 && other->family == 10) {
                        task->stage = 0x36;
                        break;
                    }
                }
            }
        }
    } else {
        task->index = info->unk10;
        task->effect = info->unkE;
        task->sound = info->unkF;
        if (info->element >= ELEMENT_FIRST || (info->family >= FAMILY_FIRST && info->family == other->family)) {
            task->stage = info->unkD;
        } else {
            task->stage = -1;
        }
    }
    units = FIGHTSTG_battle.fighters[1 - side];
    if (id == 0x1B5) {
        damage = 9999;
        task->hits[3] = 1;
    } else if (info->effect == TECH_EFFECT_DOUBLE_MAGIC) {
        if (FIGHTSTG_action.hitsLanded != 0) {
            damage = FIGHTSTG_action.hitDamage[0] + FIGHTSTG_action.hitDamage[1];
            if (units[FIGHTSTG_battle.active[1 - side]].hp - damage <= 0) {
                if (FIGHTSTG_action.hitsLanded == 1) {
                    task->hits[0] = 3;
                } else {
                    task->hits[0] = 0;
                }
                task->hits[3] = 2;
            } else {
                for (i = 0; i < 2; i++) {
                    if (FIGHTSTG_action.hits[i] != 0) {
                        task->hits[i * 3] = 0;
                    } else {
                        task->hits[i * 3] = 3;
                    }
                }
            }
        } else {
            damage = 0;
            task->hits[0] = 3;
            task->hits[3] = 3;
        }
    } else if (FIGHTSTG_action.effects[TECH_EFFECT_MULTI_HIT] != 0) {
        damage = FIGHTSTG_action.hitsLanded * FIGHTSTG_action.damage;
        if (units[FIGHTSTG_battle.active[1 - side]].hp - damage <= 0) {
            for (i = 0; i < FIGHTSTG_action.hitsLanded - 1; i++) {
                if (FIGHTSTG_action.hits[i] != 0) {
                    task->hits[i] = 0;
                } else {
                    task->hits[i] = 3;
                }
            }
            task->hits[3] = 2;
        } else {
            for (i = 0; i < FIGHTSTG_action.hitCount - 1; i++) {
                if (FIGHTSTG_action.hits[i] != 0) {
                    task->hits[i] = 0;
                } else {
                    task->hits[i] = 3;
                }
            }
            if (FIGHTSTG_action.hits[i] != 0) {
                task->hits[3] = 1;
            } else {
                task->hits[3] = 3;
            }
        }
    } else if (FIGHTSTG_action.effects[TECH_EFFECT_KNOCK_OUT] != 0) {
        task->hits[3] = 2;
        damage = 9999;
    } else if (info->effect == TECH_EFFECT_END_BATTLE && FIGHTSTG_action.effects[TECH_EFFECT_END_BATTLE] != 0) {
        task->hits[3] = 1;
        damage = FIGHTSTG_action.damage;
    } else if (info->icon == TECH_PHYSICAL || info->icon == TECH_MAGIC) {
        if (FIGHTSTG_action.hits[0] != 0) {
            if (units[FIGHTSTG_battle.active[1 - side]].hp - FIGHTSTG_action.damage <= 0) {
                task->hits[3] = 2;
            } else {
                task->hits[3] = 1;
            }
            damage = FIGHTSTG_action.damage;
        } else {
            task->hits[3] = 3;
            damage = 0;
        }
    } else {
        switch (id) {
        case 0x64:
        case 0x177:
            damage = -9999;
            break;
        case 0xB8:
        case 0xB9:
        case 0xBA:
        case 0xBB:
        case 0xBC:
        case 0x190:
            damage = -FIGHTSTG_battleFuncs.computeHeal(actor, id);
            break;
        default:
            damage = 0;
            break;
        }
    }
    if (info->icon == TECH_PHYSICAL || info->icon == TECH_MAGIC) {
        WFIGHTMN_recordTech(actor, id);
        WFIGHTMN_countHit(actor, damage);
        WFIGHTMN_setIdleMotion(SIDE_ENEMY - actor, damage);
        if (FIGHTSTG_action.effects[TECH_EFFECT_DRAIN] != 0) {
            WFIGHTMN_setIdleMotion(actor, -FIGHTSTG_action.drain);
        }
    } else {
        WFIGHTMN_endWeakness(actor);
        WFIGHTMN_setIdleMotion(actor, damage);
    }
    return task;
}

/* Sets the idle motion of side id >> 4's fighter: 1 (weak) if damage
   leaves it with a quarter of its HP or less; returns whether it did */
s32 WFIGHTMN_setIdleMotion(u8 id, s32 damage) {
    u32 side = id >> 4;
    BattleMenu *menu = TASK_REGISTRY.funcs.find(BATTLE_TASK_MENU, -1, -1);
    BattleMenuChildren *children = menu->children;
    BattleFighter *unit;

    if (id == 0x10 && FIGHTSTG_battle.kind == BATTLE_KIND_FINAL_LAST) {
        children->models->setIdleMotion(children->models, 0x10, FIGHTSTG_battle.weakened);
        return 1;
    }
    unit = &FIGHTSTG_battle.fighters[side][FIGHTSTG_battle.active[side]];
    if (unit->hp - damage <= unit->maxHp / 4) {
        children->models->setIdleMotion(children->models, id, 1);
        return 1;
    }
    children->models->setIdleMotion(children->models, id, 0);
    return 0;
}

/* In BATTLE_KIND_FINAL_LAST, the partner's third hit that does damage weakens
   the enemy (FIGHTSTG's FIGHTSTG_weakenEnemy) */
void WFIGHTMN_countHit(u8 side, s32 damage) {
    if (FIGHTSTG_battle.kind == BATTLE_KIND_FINAL_LAST && side == 0 && FIGHTSTG_battle.weakened == 0 && damage != 0) {
        if (++FIGHTSTG_battle.hitCount >= 3) {
            FIGHTSTG_weakenEnemy();
            WFIGHTMN_setIdleMotion(SIDE_ENEMY, damage);
        }
    }
}

/* In BATTLE_KIND_FINAL_LAST, anything the partner does but an attack ends
   the enemy's weakness (FIGHTSTG's FIGHTSTG_endEnemyWeakness) */
void WFIGHTMN_endWeakness(u8 side) {
    if (FIGHTSTG_battle.kind == BATTLE_KIND_FINAL_LAST && side == 0 && FIGHTSTG_battle.weakened != 0) {
        FIGHTSTG_endEnemyWeakness();
    }
}

/* In BATTLE_KIND_ESCAPE and BATTLE_KIND_UNK2, cuts the damage that the
   partner's hits do so that the enemy keeps at least an eleventh of its HP;
   in BATTLE_KIND_NO_DAMAGE the partner does none */
s32 WFIGHTMN_limitDamage(u8 side, s32 damage, s32 hits) {
    s32 other = side == 0;
    BattleFighter *unit = &FIGHTSTG_battle.fighters[other][FIGHTSTG_battle.active[other]];
    s32 limit;
    s32 total;

    switch (FIGHTSTG_battle.kind) {
    case BATTLE_KIND_ESCAPE:
    case BATTLE_KIND_UNK2:
        if (side == 0) {
            /* the s16 cast and total: the match depends on them, which
               narrow the limit and multiply before the branches */
            limit = (s16)(unit->maxHp / 11);
            if (hits != 0) {
                total = damage * hits;
                if (unit->hp > limit) {
                    if (unit->hp - total < limit) {
                        damage = (unit->hp - limit) / hits;
                    }
                } else {
                    damage = 0;
                }
            } else if (unit->hp > limit) {
                if (unit->hp - damage < limit) {
                    damage = unit->hp - limit;
                }
            } else {
                damage = 0;
            }
        }
        break;
    case BATTLE_KIND_NO_DAMAGE:
        if (side == 0) {
            damage = 0;
        }
        break;
    }
    return damage;
}
