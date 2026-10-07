/* The shop's helpers: a shop's stock, and who can equip an item, in which slot */

#include "stitshop.h"

/* The items a shop sells (up to 0), noting how many in STITSHOP_funcs.count;
   NULL for none */
s16 *STITSHOP_getShopItems(s32 shop) {
    if (shop < 0 || STITSHOP_shops[shop].items == NULL) {
        return NULL;
    }
    STITSHOP_funcs.count = STITSHOP_shops[shop].count;
    return STITSHOP_shops[shop].items;
}

/* 1 when a partner can equip an item: the partner's bit in byte 4 of the item's
   data */
s32 STITSHOP_canEquip(s32 partner, s32 item) {
    return (GET_ITEM[0](item)->data[4] >> partner) & 1;
}

/* Which equipment slot a bought item would go in: 2 or 3 for the weapons (the
   one with the weaker item when both are taken), 4 or 5 for the accessories
   (the one with the same group, else the weaker one); -1 when it can't */
s32 STITSHOP_compareEquip(s32 partner, s32 item) {
    ItemData *data = SHOP_ITEM_DATA(GET_ITEM[0](item));
    PartnerStats *stats;
    ItemInfo *info;
    ItemData *first;
    ItemData *second;
    s32 equipped[2];
    ItemData *datas[2];
    s32 i;

    switch (data->weapon.kind) {
    case 3:
        stats = GAME.funcs.getPartnerStats(partner);
        if (stats->equip[2] > 0) {
            equipped[0] = stats->equip[2];
            if (stats->equip[3] > 0) {
                equipped[1] = stats->equip[3];
                first = SHOP_ITEM_DATA(GET_ITEM[0](equipped[0]));
                info = GET_ITEM[0](equipped[1]);
                second = SHOP_ITEM_DATA(info);
                if (first->weapon.kind == 7 || info->type == 0x14) {
                    return 2;
                }
                for (i = 0; i < 2; i++) {
                    info = GET_ITEM[0](equipped[i]);
                    if (info->type < 2 || info->type > 14) {
                        return -1;
                    }
                }
                /* the game compares the attacks unsigned */
                if ((u16)first->weapon.atk < (u16)second->weapon.atk) {
                    return 2;
                }
            }
            return 3;
        }
        return 2;
    case 2:
        return 3;
    case 4:
        return 0;
    case 5:
        return 1;
    case 6:
        stats = GAME.funcs.getPartnerStats(partner);
        if (stats->equip[4] > 0) {
            equipped[0] = stats->equip[4];
            if (stats->equip[5] > 0) {
                equipped[1] = stats->equip[5];
                datas[0] = SHOP_ITEM_DATA(GET_ITEM[0](equipped[0]));
                datas[1] = SHOP_ITEM_DATA(GET_ITEM[0](equipped[1]));
                /* and the accessories' bonuses signed */
                if ((s16)datas[0]->acc.amount < (s16)datas[1]->acc.amount) {
                    return 4;
                }
            }
            return 5;
        }
        return 4;
    case 1:
    case 7:
        return 2;
    case 8:
        stats = GAME.funcs.getPartnerStats(partner);
        if (stats->equip[4] > 0) {
            equipped[0] = stats->equip[4];
            if (stats->equip[5] <= 0) {
                return 5;
            }
            equipped[1] = stats->equip[5];
            datas[0] = SHOP_ITEM_DATA(GET_ITEM[0](equipped[0]));
            if (datas[0]->acc.kind == 8 && datas[0]->acc.group == data->acc.group) {
                return 4;
            }
            datas[1] = SHOP_ITEM_DATA(GET_ITEM[0](equipped[1]));
            if (datas[1]->acc.kind == 8 && datas[1]->acc.group == data->acc.group) {
                return 5;
            }
            break;
        }
        return 4;
    case 0:
    default:
        return -1;
    }
    if ((s16)datas[0]->acc.amount < (s16)datas[1]->acc.amount) {
        return 4;
    }
    return 5;
}

/* Puts an item in a partner's equipment slot like STSTATUS_equip, moving the
   counts between GAME.items and GAME.equippedItems only when fromBag is set */
void STITSHOP_equip(s32 partner, s32 slot, s32 item, s32 fromBag) {
    PartnerStats *stats = GAME.funcs.getPartnerStats(partner);
    s16 *equip;
    s16 *pair;
    ItemData *data;
    s32 group;
    s32 old;
    s32 i;
    s32 id = item; /* the match depends on this copy, as in STSTATUS_equip */

    old = *(stats->equip + slot);
    if (old != 0) {
        if (fromBag) {
            GAME.equippedItems[old]--;
            GAME.items[old]++;
        }
        data = SHOP_ITEM_DATA(GET_ITEM[0](old));
        if (data->weapon.kind == 7) {
            stats->equip[2] = 0;
            stats->equip[3] = 0;
        } else {
            *(stats->equip + slot) = 0;
        }
    }
    if (id > 0) {
        data = SHOP_ITEM_DATA(GET_ITEM[0](id));
        if (data->weapon.kind == 7) {
            pair = &stats->equip[2];
            if (stats->equip[2] == 0) {
                pair = NULL;
                if (stats->equip[3] != 0) {
                    pair = &stats->equip[3];
                }
            }
            if (pair != NULL) {
                if (fromBag) {
                    GAME.equippedItems[*pair]--;
                    GAME.items[*pair]++;
                }
                *pair = 0;
            }
        } else if (data->acc.kind == 8) {
            group = data->acc.group;
            for (i = 0; i < 2; i++) {
                equip = &stats->equip[i + 4];
                if (*equip != 0) {
                    data = SHOP_ITEM_DATA(GET_ITEM[0](*equip));
                    if (data->acc.group == group) {
                        if (fromBag) {
                            GAME.equippedItems[*equip]--;
                            GAME.items[*equip]++;
                        }
                        *equip = 0;
                    }
                }
            }
        }
        if (fromBag) {
            GAME.equippedItems[id]++;
            GAME.items[id]--;
        }
        data = SHOP_ITEM_DATA(GET_ITEM[0](id));
        if (data->weapon.kind == 7) {
            stats->equip[2] = id;
            stats->equip[3] = id;
        } else {
            *(stats->equip + slot) = id;
        }
    }
}
