#ifndef DW3_STORY_H
#define DW3_STORY_H

/*
 * The story: the points of GAME.progress, and the event flags by name.
 * game_state.h includes it; FLAG(), PROGRESS() and the other condition
 * codes are defined there.
 */

/*
 * The points of the story (GAME.progress), each named after the event that
 * moves the story on to it, in the order the game plays them. The stages'
 * endEventN functions set them, and the scripts test them (PROGRESS(n), and
 * PROGRESS_RANGES for the SPECIAL conditions). Each comment gives the stage
 * and event that sets the point and what happens in it, and for some events
 * the title (translated) that STAGSLCT's list of scenes, the debug menu,
 * gives it ("DM0005" is event 5). Nothing sets 0x2A or 0x2C; PROGRESS_RANGES
 * ends two ranges at them.
 */
enum StoryProgress {
    /* a new game; WSTAG780's event 0, where Junior meets Ivy and Teddy at the
       Online Center in the real world, sets it again */
    STORY_START = 0x00,
    /* WSTAG785, event 1: the account is registered, and the clerk sends
       Junior to the Chamber Room */
    STORY_ACCOUNT_REGISTERED = 0x01,
    /* WSTAG225 (Login Room, Asuka City), event 5: the first login, where the
       account clerk explains Digimon Online (DM0005, "first step online") */
    STORY_LOGGED_IN = 0x02,
    /* WSTAG212, events 10 to 12: the Tamer Service downloads the starter
       pack's Digimon (DM0010-DM0012, "partner get") */
    STORY_PARTNERS_RECEIVED = 0x03,
    /* WSTAG200, event 52: after the first battle, won against Tamer Genji
       (event 50), the Digimon Navi gives its tips; the field menu opens from
       here on */
    STORY_GENJI_BEATEN = 0x04,
    /* WSTAG420, event 71: the Seiryu Leader is beaten (the Silver ID and the
       Seiryu Badge), and an earthquake stops the gondola */
    STORY_SEIRYU_BADGE = 0x05,
    /* WSTAG410 (East Station), event 90: the Blue Card the player was given
       turns out to be a fake */
    STORY_FAKE_BLUE_CARD = 0x06,
    /* WSTAG440 (South Station), event 152: a ghost's voice in the empty
       station */
    STORY_SOUTH_STATION_GHOST = 0x07,
    /* WSTAG480 (Jungle Grave), event 171: Sepikmon will say how to beat
       Zanbamon once the player finds his lost mask (DM0180, "a mask for
       Sepikmon", is the next event) */
    STORY_SEPIKMON_MASK_LOST = 0x08,
    /* WSTAG380 (Divermon's Lake), event 205: the Mischievous Mat, caught in
       his Etemon Suit, gives the player the Agumon Suits */
    STORY_AGUMON_SUITS = 0x09,
    /* WSTAG475 (Shaman House), event 230: the Smelly Herb drives Zanbamon off
       the way */
    STORY_ZANBAMON_DRIVEN_OFF = 0x0A,
    /* WSTAG520, event 261: the Suzaku Leader is beaten (the Suzaku Badge),
       and Kail says Teddy went to Asuka City's Admin Center */
    STORY_SUZAKU_BADGE = 0x0B,
    /* WSTAG212, event 273: Kail and the player will put on the Agumon Suits
       to look for Teddy */
    STORY_LOOKING_FOR_TEDDY = 0x0C,
    /* WSTAG237 (Underground Path), event 300: in the Agumon Suit; Kail goes
       on ahead alone */
    STORY_AGUMON_DISGUISE = 0x0D,
    /* WSTAG212, event 352: Teddy is found; MAGAMI is part of the A.o.A, and
       the player sets off to beat the Game Master */
    STORY_TEDDY_FOUND = 0x0E,
    /* WSTAG460 (Reliability Spot), event 370: the Qing Long Chief, asked for
       the Digi-Egg of Knowledge, fights the player (the DE Sincerity) */
    STORY_DE_SINCERITY = 0x0F,
    /* WSTAG685 (Underground Cave, Byakko City), event 413: the rock blocking
       the hole is Numemon */
    STORY_NUMEMON_FOUND = 0x10,
    /* WSTAG655 (Mirage Room), event 431: HiAndromon guards the way to
       Numemon (the Byakko Badge) */
    STORY_BYAKKO_BADGE = 0x11,
    /* WSTAG605 (Operation Room), event 511: the player saves Lisa from
       WaruMonzaemon (the Rusty Rifle) */
    STORY_LISA_SAVED = 0x12,
    /* WSTAG615 (Sewers), event 531: Lucky Mouse appears (DM0531, "Lucky Mouse
       appears") */
    STORY_LUCKY_MOUSE = 0x13,
    /* WSTAG620 (the rebels' hideout), event 534: the Byakko Leader takes the
       player for the A.o.A and fights */
    STORY_BYAKKO_LEADER_FOUGHT = 0x14,
    /* WSTAG620, event 551: Nick finds a Staff Pass for the player */
    STORY_STAFF_PASS = 0x15,
    /* WSTAG325 (Control Room, Asuka City), event 560: a Soldier guards the
       way */
    STORY_CONTROL_ROOM = 0x16,
    /* WSTAG305 (Master Room), event 661: the Game Master is caught, but
       Vemmon takes over the Optical Network; an emergency chamber is said to
       be in the North Sector */
    STORY_GAME_MASTER_CAUGHT = 0x17,
    /* WSTAG210 (Main Lobby, Asuka City), event 685: the A.o.A have
       reprogrammed Knightmon, which takes the player for a virus */
    STORY_KNIGHTMON_REPROGRAMMED = 0x18,
    /* WSTAG685, event 690: Leader Chuck says stopping Knightmon takes the
       four City Leaders' Code Passes */
    STORY_CODE_PASSES_NEEDED = 0x19,
    /* WSTAG520 (Suzaku Hall), event 695: another earthquake; Bulbmon digs
       the holes */
    STORY_BULBMON_FOUND = 0x1A,
    /* WSTAG545 (Bug Maze Pit), event 711: Patamon heard a weird sound from
       the jungle, where its leader went */
    STORY_JUNGLE_SOUND = 0x1B,
    /* WSTAG421 (Qing Long City), event 743: with the Blue ID Pass a Trooper
       takes the player for the Qing Long Chief, and Zhu Que City opens */
    STORY_BLUE_ID_PASS = 0x1C,
    /* WSTAG521 (Zhu Que Hall), event 751: Bulbmon is beaten (the Red ID Pass);
       its hole leads on to the Amaterasu server */
    STORY_BULBMON_BEATEN = 0x1D,
    /* WSTAG526 (Zhu Que UG Lake), event 760: the fight with Zanbamon (the DE
       Knowledge) */
    STORY_DE_KNOWLEDGE = 0x1E,
    /* WSTAG755 (Battle Gate), event 781: the Xuen Wu Chief, who holds the
       Black ID Pass, fights the player (the Genbu Badge) */
    STORY_GENBU_BADGE = 0x1F,
    /* WSTAG750 (the emergency Matrix Chamber), event 820: back in the real
       world, for 180 seconds */
    STORY_REAL_WORLD = 0x20,
    /* WSTAG750, event 886: the news say the Optical Network is offline */
    STORY_NETWORK_OFFLINE = 0x21,
    /* WSTAG305, events 893 and 895: the way into Amaterasu City, the A.o.A's
       headquarters, is still to be found */
    STORY_WAY_TO_AMATERASU = 0x22,
    /* WSTAG676 (Bai Hu Dome), event 901: the General says the A.o.A came on
       Bulbmon (the White ID Pass) */
    STORY_WHITE_ID_PASS = 0x23,
    /* WSTAG756 (Battle Gate), event 911: the Black ID Pass */
    STORY_BLACK_ID_PASS = 0x24,
    /* WSTAG206 (Amaterasu Bridge), event 922: an Attacker holds the bridge */
    STORY_AMATERASU_BRIDGE = 0x25,
    /* WSTAG226 (Login Room, Amaterasu City), event 935, after the President
       of MAGAMI gives himself up (WSTAG311's events 931 to 933) */
    STORY_PRESIDENT_ARRESTED = 0x26,
    /* WSTAG310 (A.o.A Headquarters, Asuka City), event 961 */
    STORY_ASUKA_HEADQUARTERS = 0x27,
    /* WSTAG311 (A.o.A Headquarters, Amaterasu City), event 982, after event
       981, where the A.o.A's Operation Sigma and the Gunslinger come out */
    STORY_OPERATION_SIGMA = 0x28,
    /* WSTAG810 (Gunslinger 1F), event 1035 */
    STORY_GUNSLINGER = 0x29,
    /* WSTAG820, event 1080, with Snatchmon: each encounter plays
       MODE_BATTLE_MOVIE first */
    STORY_MOVIE_BATTLES = 0x2B,
    /* WSTAG780, event 1500, in the European and Japanese versions: the extra
       chapter, whose stages are FIELDSTG_extraStages (WSTAG920 to WSTAG974) */
    STORY_EXTRA = 0x2D,
};

/*
 * The event flags, by group (FLAG(group, id), include/engine/game_state.h),
 * each named after what sets it, with where. The names come from the texts
 * of the talks and events that set and test them; the flags whose meaning
 * isn't clear stay numbers.
 */

/* FLAGS_00, the temporary flags (bits 0-0x17 clear when the field changes
   mode, GAME.clearTempFlags); the stages use bits 0-6 as their own, and
   those stay numbers */

/* set by updateModeFlags on the way back from a card battle: 1 if the
   player won it (FLAGS_00.cardBattleWon, which the card battle sets), else
   0 */
#define FLAG_CARD_BATTLE_WON FLAG(0, 0x10)
/* set by updateModeFlags on the way back from a card battle; the talks that
   follow one test it and clear it */
#define FLAG_CARD_BATTLE_ENDED FLAG(0, 0x11)

/* GAME.flags02: the chests and the things lying about, set when the player
   takes them, tested 0 to show them */

/* wstag320: chest that gives 300 BIT ("I got 300 BIT!"); its conditions
   test it 0 */
#define FLAG_ASUKA_SEWERS_300_BIT_FOUND FLAG(2, 0)
/* wstag330: chest that gives the Power Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_CENTRAL_PARK_POWER_CHARGE_FOUND FLAG(2, 1)
/* wstag350: chest that gives the Buckler, "I got" text; its conditions test
   it 0 */
#define FLAG_WEST_WIRE_FOREST_BUCKLER_FOUND FLAG(2, 2)
/* wstag380: chest that gives the Bandanna, "I got" text; its conditions
   test it 0 */
#define FLAG_DIVERMON_LAKE_BANDANNA_FOUND FLAG(2, 3)
/* wstag450: chest that gives the Tin Mail, "I got" text; its conditions
   test it 0 */
#define FLAG_BULK_BRIDGE_TIN_MAIL_FOUND FLAG(2, 4)
/* wstag530: chest that gives the Power Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_JUNGLE_SHRINE_POWER_CHARGE_FOUND FLAG(2, 5)
/* wstag205: chest that gives the Iron Glove, "I got" text; its conditions
   test it 0 */
#define FLAG_ASUKA_BRIDGE_IRON_GLOVE_FOUND FLAG(2, 6)
/* wstag320: chest that gives the Crimson Blade, "I got" text; its
   conditions test it 0 */
#define FLAG_ASUKA_SEWERS_CRIMSON_BLADE_FOUND FLAG(2, 7)
/* wstag525: chest that gives the Crossbow, "I got" text; its conditions
   test it 0 */
#define FLAG_SUZAKU_LAKE_CROSSBOW_FOUND FLAG(2, 8)
/* wstag565: chest that gives the Power Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_NORTH_BADLAND_W_POWER_CHARGE_FOUND FLAG(2, 9)
/* wstag565: chest that gives 100 BIT ("I got 100 BIT!"); its conditions
   test it 0 */
#define FLAG_NORTH_BADLAND_W_100_BIT_FOUND FLAG(2, 0xA)
/* wstag565: chest that gives the Energy Disk, "I got" text; its conditions
   test it 0 */
#define FLAG_NORTH_BADLAND_W_ENERGY_DISK_FOUND FLAG(2, 0xB)
/* wstag570: chest that gives 600 BIT ("I got 600 BIT!"); its conditions
   test it 0 */
#define FLAG_NORTH_BADLAND_E_600_BIT_FOUND FLAG(2, 0xC)
/* wstag585: chest that gives the HP Chip, "I got" text; its conditions test
   it 0; Dum Dum Factory (wstag580) tests it 1 to start event 0x1D6 */
#define FLAG_DUCT_ROOM_01_HP_CHIP_FOUND FLAG(2, 0xD)
/* wstag600: chest that gives the Mind Chip, "I got" text; its conditions
   test it 0; Dum Dum Factory (wstag580) tests it 1 to start event 0x1E0 */
#define FLAG_DUCT_ROOM_04_MIND_CHIP_FOUND FLAG(2, 0xE)
/* wstag590: chest that gives the MP Chip, "I got" text; its conditions test
   it 0; Dum Dum Factory (wstag580) tests it 1 to start event 0x1EA */
#define FLAG_DUCT_ROOM_02_MP_CHIP_FOUND FLAG(2, 0xF)
/* wstag595: chest that gives the Power Chip, "I got" text; its conditions
   test it 0; Dum Dum Factory (wstag580) tests it 1 to start event 0x1F4 */
#define FLAG_DUCT_ROOM_03_POWER_CHIP_FOUND FLAG(2, 0x10)
/* wstag315: chest that gives the Power Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_ASUKA_ADMIN_B1F_POWER_CHARGE_FOUND FLAG(2, 0x11)
/* wstag315: chest that gives 100 BIT ("I got 100 BIT!"); its conditions
   test it 0 */
#define FLAG_ASUKA_ADMIN_B1F_100_BIT_FOUND FLAG(2, 0x12)
/* wstag315: chest that gives the Life Disk, "I got" text; its conditions
   test it 0 */
#define FLAG_ASUKA_ADMIN_B1F_LIFE_DISK_FOUND FLAG(2, 0x13)
/* wstag300: chest that gives the Power Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_ASUKA_ADMIN_2F_POWER_CHARGE_FOUND FLAG(2, 0x14)
/* wstag285: chest that gives the Metal Horn, "I got" text; its conditions
   test it 0 */
#define FLAG_ASUKA_ADMIN_1F_METAL_HORN_FOUND FLAG(2, 0x15)
/* wstag218: chest that gives 1000 BIT ("I got 1000 BIT!"); its conditions
   test it 0 */
#define FLAG_ASUKA_CITY_1000_BIT_FOUND FLAG(2, 0x16)
/* wstag218: chest that gives the Power Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_ASUKA_CITY_POWER_CHARGE_FOUND FLAG(2, 0x17)
/* wstag540: chest that gives the Rubber Suit, "I got" text; its conditions
   test it 0 */
#define FLAG_BUG_MAZE_RUBBER_SUIT_FOUND FLAG(2, 0x18)
/* wstag540: chest that gives the Power Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_BUG_MAZE_POWER_CHARGE_FOUND FLAG(2, 0x19)
/* wstag540: chest that gives 1600 BIT ("I got 1600 BIT!"); its conditions
   test it 0 */
#define FLAG_BUG_MAZE_1600_BIT_FOUND FLAG(2, 0x1A)
/* wstag545: chest that gives the Digitama Mail, "I got" text; its
   conditions test it 0 */
#define FLAG_BUG_MAZE_PIT_DIGITAMA_MAIL_FOUND FLAG(2, 0x1B)
/* wstag381: chest that gives the Knight Shield, "I got" text; its
   conditions test it 0 */
#define FLAG_DIVERMON_LAKE_KNIGHT_SHIELD_FOUND FLAG(2, 0x1C)
/* wstag331: chest that gives the Super Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_CENTRAL_PARK_SUPER_CHARGE_FOUND FLAG(2, 0x1D)
/* wstag531: chest that gives the Power Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_AMATERASU_JUNGLE_SHRINE_POWER_CHARGE_FOUND FLAG(2, 0x1E)
/* wstag526: chest that gives the Evil Fang, "I got" text; its conditions
   test it 0 */
#define FLAG_ZHU_QUE_LAKE_EVIL_FANG_FOUND FLAG(2, 0x1F)
/* wstag690: chest that gives the Needle Glove, "I got" text; its conditions
   test it 0 */
#define FLAG_BOOT_MOUNTAIN_NEEDLE_GLOVE_FOUND FLAG(2, 0x20)
/* wstag690: chest that gives the Power Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_BOOT_MOUNTAIN_POWER_CHARGE_FOUND FLAG(2, 0x21)
/* wstag695: chest that gives 3000 BIT ("I got 3000 BIT!"); its conditions
   test it 0 */
#define FLAG_SNOW_MOUNTAIN_3000_BIT_FOUND FLAG(2, 0x22)
/* wstag695: chest that gives the Shamshir, "I got" text; its conditions
   test it 0 */
#define FLAG_SNOW_MOUNTAIN_SHAMSHIR_FOUND FLAG(2, 0x23)
/* wstag705: chest that gives the Power Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_FREEZE_MOUNTAIN_POWER_CHARGE_FOUND FLAG(2, 0x24)
/* wstag705: chest that gives the Knight Shield, "I got" text; its
   conditions test it 0 */
#define FLAG_FREEZE_MOUNTAIN_KNIGHT_SHIELD_FOUND FLAG(2, 0x25)
/* wstag760: chest that gives the Life Disk, "I got" text; its conditions
   test it 0 */
#define FLAG_GENBU_CITY_LIFE_DISK_FOUND FLAG(2, 0x26)
/* wstag395: chest that gives the Kulon Armor, "I got" text; its conditions
   test it 0 */
#define FLAG_WIND_PRAIRIE_KULON_ARMOR_FOUND FLAG(2, 0x27)
/* wstag400: chest that gives the Down Jacket, "I got" text; its conditions
   test it 0 */
#define FLAG_KICKING_FOREST_DOWN_JACKET_FOUND FLAG(2, 0x28)
/* wstag560: chest that gives the Charisma Chip, "I got" text; its
   conditions test it 0 */
#define FLAG_PELCHE_OASIS_CHARISMA_CHIP_FOUND FLAG(2, 0x29)
/* wstag396: chest that gives 1600 BIT ("I got 1600 BIT!"); its conditions
   test it 0 */
#define FLAG_WIND_PRAIRIE_1600_BIT_FOUND FLAG(2, 0x2A)
/* wstag401: chest that gives the Gold ID, "I got" text; its conditions test
   it 0 */
#define FLAG_KICKING_FOREST_GOLD_ID_FOUND FLAG(2, 0x2B)
/* wstag860: chest that gives the Charisma Chip, "I got" text; its
   conditions test it 0 */
#define FLAG_SEABED_CHARISMA_CHIP_FOUND FLAG(2, 0x2C)
/* wstag880: chest that gives the HP Chip, "I got" text; its conditions test
   it 0 */
#define FLAG_CIRCUIT_BOARD_HP_CHIP_FOUND FLAG(2, 0x2D)
/* wstag880: chest that gives the MP Chip, "I got" text; its conditions test
   it 0 */
#define FLAG_CIRCUIT_BOARD_MP_CHIP_FOUND FLAG(2, 0x2E)
/* wstag880: chest that gives the Power Chip, "I got" text; its conditions
   test it 0 */
#define FLAG_CIRCUIT_BOARD_POWER_CHIP_FOUND FLAG(2, 0x2F)
/* wstag880: chest that gives the Armor Chip, "I got" text; its conditions
   test it 0 */
#define FLAG_CIRCUIT_BOARD_ARMOR_CHIP_FOUND FLAG(2, 0x30)
/* wstag880: chest that gives the Mind Chip, "I got" text; its conditions
   test it 0 */
#define FLAG_CIRCUIT_BOARD_MIND_CHIP_FOUND FLAG(2, 0x31)
/* wstag880: chest that gives the Wisdom Chip, "I got" text; its conditions
   test it 0 */
#define FLAG_CIRCUIT_BOARD_WISDOM_CHIP_FOUND FLAG(2, 0x32)
/* wstag880: chest that gives the Boost Chip, "I got" text; its conditions
   test it 0 */
#define FLAG_CIRCUIT_BOARD_BOOST_CHIP_FOUND FLAG(2, 0x33)
/* wstag880: chest that gives the Fire Chip, "I got" text; its conditions
   test it 0 */
#define FLAG_CIRCUIT_BOARD_FIRE_CHIP_FOUND FLAG(2, 0x34)
/* wstag880: chest that gives the Water Chip, "I got" text; its conditions
   test it 0 */
#define FLAG_CIRCUIT_BOARD_WATER_CHIP_FOUND FLAG(2, 0x35)
/* wstag880: chest that gives the Ice Chip, "I got" text; its conditions
   test it 0 */
#define FLAG_CIRCUIT_BOARD_ICE_CHIP_FOUND FLAG(2, 0x36)
/* wstag880: chest that gives the Wind Chip, "I got" text; its conditions
   test it 0 */
#define FLAG_CIRCUIT_BOARD_WIND_CHIP_FOUND FLAG(2, 0x37)
/* wstag745: chest that gives 5000 BIT ("I got 5000 BIT!"); its conditions
   test it 0 */
#define FLAG_DARK_DUNGEON_5000_BIT_FOUND FLAG(2, 0x38)
/* wstag795: chest that gives the Trihorn, "I got" text; its conditions test
   it 0 */
#define FLAG_MAGASTA_B1F_TRIHORN_FOUND FLAG(2, 0x39)
/* wstag795: chest that gives the Power Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_MAGASTA_B1F_POWER_CHARGE_FOUND FLAG(2, 0x3B)
/* wstag795: chest that gives the Grey Sword, "I got" text; its conditions
   test it 0 */
#define FLAG_MAGASTA_B1F_GREY_SWORD_FOUND FLAG(2, 0x3E)
/* wstag795: chest that gives the Royal Spear, "I got" text; its conditions
   test it 0 */
#define FLAG_MAGASTA_B1F_ROYAL_SPEAR_FOUND FLAG(2, 0x3F)
/* wstag795: chest that gives the Super Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_MAGASTA_B1F_SUPER_CHARGE_FOUND FLAG(2, 0x41)
/* wstag795: chest that gives the Tenjinmaru, "I got" text; its conditions
   test it 0 (the US text says 300 BIT; the item code and JP text say
   otherwise) */
#define FLAG_MAGASTA_B1F_TENJINMARU_FOUND FLAG(2, 0x42)
/* wstag795: chest that gives the Venom Fang, "I got" text; its conditions
   test it 0 */
#define FLAG_MAGASTA_B1F_VENOM_FANG_FOUND FLAG(2, 0x43)
/* wstag795: chest that gives the High Security, "I got" text; its
   conditions test it 0 */
#define FLAG_MAGASTA_B1F_HIGH_SECURITY_FOUND FLAG(2, 0x44)
/* wstag800: chest that gives the Beret, "I got" text; its conditions test
   it 0 */
#define FLAG_MAGASTA_B2F_BERET_FOUND FLAG(2, 0x45)
/* wstag800: chest that gives the Royal Crown, "I got" text; its conditions
   test it 0 */
#define FLAG_MAGASTA_B2F_ROYAL_CROWN_FOUND FLAG(2, 0x46)
/* wstag800: chest that gives the Super Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_MAGASTA_B2F_SUPER_CHARGE_FOUND FLAG(2, 0x47)
/* wstag800: chest that gives the Misty Armor, "I got" text; its conditions
   test it 0 */
#define FLAG_MAGASTA_B2F_MISTY_ARMOR_FOUND FLAG(2, 0x49)
/* wstag566: chest that gives the Super Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_NORTH_BADLAND_W_SUPER_CHARGE_FOUND FLAG(2, 0x4A)
/* wstag566: chest that gives the Life Disk, "I got" text; its conditions
   test it 0 */
#define FLAG_NORTH_BADLAND_W_LIFE_DISK_FOUND FLAG(2, 0x4B)
/* wstag586: chest that gives the Armor Chip, "I got" text; its conditions
   test it 0 */
#define FLAG_DUCT_ROOM_01_ARMOR_CHIP_FOUND FLAG(2, 0x4C)
/* wstag591: chest that gives the Wisdom Chip, "I got" text; its conditions
   test it 0 (the US text says Mind Chip; the item code and JP text say
   otherwise) */
#define FLAG_DUCT_ROOM_02_WISDOM_CHIP_FOUND FLAG(2, 0x4D)
/* wstag596: chest that gives the Boost Chip, "I got" text; its conditions
   test it 0 */
#define FLAG_DUCT_ROOM_03_BOOST_CHIP_FOUND FLAG(2, 0x4E)
/* wstag601: chest that gives the Charisma Chip, "I got" text; its
   conditions test it 0 */
#define FLAG_DUCT_ROOM_04_CHARISMA_CHIP_FOUND FLAG(2, 0x4F)
/* wstag691: chest that gives the Super Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_BOOT_MOUNTAIN_SUPER_CHARGE_FOUND FLAG(2, 0x50)
/* wstag706: chest that gives 3000 BIT ("I got 3000 BIT!"); its conditions
   test it 0 */
#define FLAG_FREEZE_MOUNTAIN_3000_BIT_FOUND FLAG(2, 0x52)
/* wstag761: chest that gives the Kulon Shield, "I got" text; its conditions
   test it 0 */
#define FLAG_XUAN_WU_CITY_KULON_SHIELD_FOUND FLAG(2, 0x53)
/* wstag561: chest that gives the Charisma Chip, "I got" text; its
   conditions test it 0 */
#define FLAG_AMATERASU_PELCHE_OASIS_CHARISMA_CHIP_FOUND FLAG(2, 0x54)
/* wstag860: chest that gives the Train Chip 3, "I got" text; its conditions
   test it 0 */
#define FLAG_SEABED_TRAIN_CHIP_3_FOUND FLAG(2, 0x55)
/* wstag880: chest that gives the Thunder Chip, "I got" text; its conditions
   test it 0 */
#define FLAG_CIRCUIT_BOARD_THUNDER_CHIP_FOUND FLAG(2, 0x56)
/* wstag880: chest that gives the Metal Chip, "I got" text; its conditions
   test it 0 */
#define FLAG_CIRCUIT_BOARD_METAL_CHIP_FOUND FLAG(2, 0x57)
/* wstag880: chest that gives the Devil Chip, "I got" text; its conditions
   test it 0 */
#define FLAG_CIRCUIT_BOARD_DEVIL_CHIP_FOUND FLAG(2, 0x58)
/* wstag880: chest that gives the Wild Glove, "I got" text; its conditions
   test it 0 */
#define FLAG_CIRCUIT_BOARD_WILD_GLOVE_FOUND FLAG(2, 0x59)
/* wstag880: chest that gives the Yin Yang Ward, "I got" text; its
   conditions test it 0 */
#define FLAG_CIRCUIT_BOARD_YIN_YANG_WARD_FOUND FLAG(2, 0x5A)
/* wstag880: chest that gives the Ronin Shield, "I got" text; its conditions
   test it 0 */
#define FLAG_CIRCUIT_BOARD_RONIN_SHIELD_FOUND FLAG(2, 0x5B)
/* wstag880: chest that gives the Divine Robe, "I got" text; its conditions
   test it 0 */
#define FLAG_CIRCUIT_BOARD_DIVINE_ROBE_FOUND FLAG(2, 0x5C)
/* wstag746: chest that gives the Hazard Armor, "I got" text; its conditions
   test it 0 */
#define FLAG_DARK_DUNGEON_HAZARD_ARMOR_FOUND FLAG(2, 0x5D)
/* wstag206: chest that gives 100 BIT ("I got 100 BIT!"); its conditions
   test it 0 */
#define FLAG_AMATERASU_BRIDGE_100_BIT_FOUND FLAG(2, 0x5E)
/* wstag286: chest that gives the Ultra Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_AMATERASU_ADMIN_1F_ULTRA_CHARGE_FOUND FLAG(2, 0x5F)
/* wstag316: chest that gives 8500 BIT ("I got 8500 BIT!"); its conditions
   test it 0 */
#define FLAG_AMATERASU_ADMIN_B1F_8500_BIT_FOUND FLAG(2, 0x61)
/* wstag316: chest that gives the Ultra Charge, "I got" text; its conditions
   test it 0 */
#define FLAG_AMATERASU_ADMIN_B1F_ULTRA_CHARGE_FOUND FLAG(2, 0x62)
/* wstag321: chest that gives the High Security, "I got" text; its
   conditions test it 0 */
#define FLAG_AMATERASU_SEWER_HIGH_SECURITY_FOUND FLAG(2, 0x64)
/* wstag321: chest that gives 5000 BIT ("I got 5000 BIT!"); its conditions
   test it 0 */
#define FLAG_AMATERASU_SEWER_5000_BIT_FOUND FLAG(2, 0x65)
/* wstag922 (extra chapter): chest that gives the Boost Chip, "I got" text;
   its conditions test it 0 (EU text says Armor Chip; item code and JP say
   Boost) */
#define FLAG_AMATERASU_BRIDGE_BOOST_CHIP_FOUND FLAG(2, 0x66)
/* wstag938 (extra chapter): chest that gives the Fire Chip, "I got" text;
   its conditions test it 0 */
#define FLAG_AMATERASU_SEWER_FIRE_CHIP_FOUND FLAG(2, 0x67)
/* wstag938 (extra chapter): chest that gives the Water Chip, "I got" text;
   its conditions test it 0 */
#define FLAG_AMATERASU_SEWER_WATER_CHIP_FOUND FLAG(2, 0x68)
/* wstag940 (extra chapter): chest that gives the Armor Chip, "I got" text;
   its conditions test it 0 */
#define FLAG_CENTRAL_PARK_ARMOR_CHIP_FOUND FLAG(2, 0x69)
/* wstag944 (extra chapter): chest that gives the Ice Chip, "I got" text;
   its conditions test it 0 */
#define FLAG_WEST_WIRE_FOREST_ICE_CHIP_FOUND FLAG(2, 0x6A)
/* wstag950 (extra chapter): chest that gives the Mind Chip, "I got" text;
   its conditions test it 0 */
#define FLAG_DIVERMON_LAKE_MIND_CHIP_FOUND FLAG(2, 0x6B)
/* wstag952 (extra chapter): chest that gives the Wind Chip, "I got" text;
   its conditions test it 0 */
#define FLAG_WIND_PRAIRIE_WIND_CHIP_FOUND FLAG(2, 0x6C)
/* wstag953 (extra chapter): chest that gives the Thunder Chip, "I got"
   text; its conditions test it 0 */
#define FLAG_KICKING_FOREST_THUNDER_CHIP_FOUND FLAG(2, 0x6D)
/* wstag967 (extra chapter): chest that gives the Saber Fang, "I got" text;
   its conditions test it 0 */
#define FLAG_SEABED_SABER_FANG_FOUND FLAG(2, 0x6E)
/* wstag964 (extra chapter): chest that gives the Cluster Cannon, "I got"
   text; its conditions test it 0 */
#define FLAG_SEABED_CLUSTER_CANNON_FOUND FLAG(2, 0x6F)
/* wstag964 (extra chapter): chest that gives the Khakkhara, "I got" text;
   its conditions test it 0 */
#define FLAG_SEABED_KHAKKHARA_FOUND FLAG(2, 0x70)
/* wstag967 (extra chapter): chest that gives the Onimaru, "I got" text; its
   conditions test it 0 */
#define FLAG_SEABED_ONIMARU_FOUND FLAG(2, 0x71)
/* wstag967 (extra chapter): chest that gives the Kaiser Fist, "I got" text;
   its conditions test it 0 */
#define FLAG_SEABED_KAISER_FIST_FOUND FLAG(2, 0x72)
/* wstag964 (extra chapter): chest that gives the Wisdom Chip, "I got" text;
   its conditions test it 0 */
#define FLAG_SEABED_WISDOM_CHIP_FOUND FLAG(2, 0x73)
/* wstag973 (extra chapter): chest that gives the Venom Fang, "I got" text;
   its conditions test it 0 */
#define FLAG_CIRCUIT_BOARD_VENOM_FANG_FOUND FLAG(2, 0x74)
/* wstag973 (extra chapter): chest that gives the Laser Cannon, "I got"
   text; its conditions test it 0 */
#define FLAG_CIRCUIT_BOARD_LASER_CANNON_FOUND FLAG(2, 0x75)
/* wstag973 (extra chapter): chest that gives the Crystal Rod, "I got" text;
   its conditions test it 0 */
#define FLAG_CIRCUIT_BOARD_CRYSTAL_ROD_FOUND FLAG(2, 0x76)
/* wstag970 (extra chapter): chest that gives the Tenjinmaru, "I got" text;
   its conditions test it 0 */
#define FLAG_CIRCUIT_BOARD_TENJINMARU_FOUND FLAG(2, 0x77)
/* wstag972 (extra chapter): chest that gives the Tempest Arm, "I got" text;
   its conditions test it 0 */
#define FLAG_CIRCUIT_BOARD_TEMPEST_ARM_FOUND FLAG(2, 0x78)
/* wstag973 (extra chapter): chest that gives the Gold ID, "I got" text; its
   conditions test it 0 */
#define FLAG_CIRCUIT_BOARD_GOLD_ID_FOUND FLAG(2, 0x79)
/* wstag970 (extra chapter): chest that gives the Platinum ID, "I got" text;
   its conditions test it 0 */
#define FLAG_CIRCUIT_BOARD_PLATINUM_ID_FOUND FLAG(2, 0x7A)
/* wstag972 (extra chapter): chest that gives the Rusty Katana, "I got"
   text; its conditions test it 0 */
#define FLAG_CIRCUIT_BOARD_RUSTY_KATANA_FOUND FLAG(2, 0x7B)
/* wstag972 (extra chapter): chest that gives the Old Wand, "I got" text;
   its conditions test it 0 */
#define FLAG_CIRCUIT_BOARD_OLD_WAND_FOUND FLAG(2, 0x7C)

/* GAME.flags04: FIELDSTG_progressEvents' story events, Mr. Smith's
   auctions; field_stage.c's END_CHOICE(n) sets 0x400 + n on either answer */

/* Field story event at progress 5: Mr. Smith auctions the Divine Barrier;
   set by END_CHOICE(0) on either answer, tested 0 to start it */
#define FLAG_DIVINE_BARRIER_AUCTION_SEEN FLAG(4, 0)
/* Field story event at progress 8: Mr. Smith auctions the Hazard Shield;
   set by END_CHOICE(1) on either answer, tested 0 to start it */
#define FLAG_HAZARD_SHIELD_AUCTION_SEEN FLAG(4, 1)
/* Field story event at progress 12: Mr. Smith auctions the Sniper Guard;
   set by END_CHOICE(2) on either answer, tested 0 to start it */
#define FLAG_SNIPER_GUARD_AUCTION_SEEN FLAG(4, 2)
/* Field story event at progress 14: Mr. Smith auctions the Dramon Shield;
   set by END_CHOICE(3) on either answer, tested 0 to start it */
#define FLAG_DRAMON_SHIELD_AUCTION_SEEN FLAG(4, 3)
/* Field story event at progress 16: Mr. Smith auctions the Yin Yang Wand;
   set by END_CHOICE(4) on either answer, tested 0 to start it */
#define FLAG_YIN_YANG_WAND_AUCTION_SEEN FLAG(4, 4)
/* Field story event at progress 22: Mr. Smith auctions the Hazard Fang; set
   by END_CHOICE(5) on either answer, tested 0 to start it */
#define FLAG_HAZARD_FANG_AUCTION_SEEN FLAG(4, 5)
/* Field story event at progress 24: Mr. Smith auctions the Sniper Cannon;
   set by END_CHOICE(6) on either answer, tested 0 to start it */
#define FLAG_SNIPER_CANNON_AUCTION_SEEN FLAG(4, 6)
/* Field story event at progress 26: Mr. Smith auctions the Ronin Blade; set
   by END_CHOICE(7) on either answer, tested 0 to start it */
#define FLAG_RONIN_BLADE_AUCTION_SEEN FLAG(4, 7)
/* Field story event at progress 28: Mr. Smith auctions the Sniper Goggle;
   set by END_CHOICE(8) on either answer, tested 0 to start it */
#define FLAG_SNIPER_GOGGLE_AUCTION_SEEN FLAG(4, 8)
/* Field story event at progress 30: Mr. Smith auctions the Divine Crown;
   set by END_CHOICE(9) on either answer, tested 0 to start it */
#define FLAG_DIVINE_CROWN_AUCTION_SEEN FLAG(4, 9)
/* Field story event at progress 31: Mr. Smith auctions the Brave Helmet;
   set by END_CHOICE(10) on either answer, tested 0 to start it */
#define FLAG_BRAVE_HELMET_AUCTION_SEEN FLAG(4, 0xA)
/* Field story event at progress 34: Mr. Smith auctions the Ronin Helmet;
   set by END_CHOICE(11) on either answer, tested 0 to start it */
#define FLAG_RONIN_HELMET_AUCTION_SEEN FLAG(4, 0xB)
/* Field story event at progress 36: Mr. Smith auctions the Yin Yang Suit;
   set by END_CHOICE(12) on either answer, tested 0 to start it */
#define FLAG_YIN_YANG_SUIT_AUCTION_SEEN FLAG(4, 0xC)
/* Field story event at progress 37: Mr. Smith auctions the Ronin Armor; set
   by END_CHOICE(13) on either answer, tested 0 to start it */
#define FLAG_RONIN_ARMOR_AUCTION_SEEN FLAG(4, 0xD)
/* Field story event at progress 38: Mr. Smith auctions the Wild Suit; set
   by END_CHOICE(14) on either answer, tested 0 to start it */
#define FLAG_WILD_SUIT_AUCTION_SEEN FLAG(4, 0xE)
/* Field story event at progress 39: Mr. Smith auctions the Oioi Oink; set
   by END_CHOICE(15) on either answer, tested 0 to start it */
#define FLAG_OIOI_OINK_AUCTION_SEEN FLAG(4, 0xF)

/* GAME.flags06: the DRI agents' DDNA requests */

/* wstag405: DRI Johann asks the player to get Agumon's DDNA from
   MetalGreymon; tested in wstag445 with the DDNA not yet had */
#define FLAG_AGUMON_DDNA_REQUESTED FLAG(6, 0)
/* wstag420: DRI Jimmy asks the player to get Guilmon DDNA from WarGrowlmon;
   tested in wstag490 with the DDNA not yet had */
#define FLAG_GUILMON_DDNA_REQUESTED FLAG(6, 1)
/* wstag330: DRI Kazuki asks for Patamon's DDNA; tested at MagnaAngemon in
   wstag550 with the DDNA not yet had */
#define FLAG_PATAMON_DDNA_REQUESTED FLAG(6, 2)
/* wstag330: DRI Michael asks for Renamon's DDNA; tested at Taomon in
   wstag565 with the DDNA not yet had */
#define FLAG_RENAMON_DDNA_REQUESTED FLAG(6, 3)
/* wstag635: DRI Ken wants Kotemon DDNA from Kyukimon; tested at Kyukimon in
   wstag525 with the DDNA not yet had */
#define FLAG_KOTEMON_DDNA_REQUESTED FLAG(6, 4)
/* wstag635: DRI Yuji wants Kumamon DDNA from GrapLeomon; tested at
   GrapLeomon in wstag490 with the DDNA not yet had */
#define FLAG_KUMAMON_DDNA_REQUESTED FLAG(6, 5)
/* wstag635: DRI Yang asks for Monmon DDNA from Armormon; tested at Armormon
   in wstag385 with the DDNA not yet had */
#define FLAG_MONMON_DDNA_REQUESTED FLAG(6, 6)

/* GAME.flags0A: the battles with the named Digimon */

/* wstag375 Protocol Ruins: set when Pharaohmon's event 1260 starts ("I
   lose!", gives the Old Wand); later talks praise the win */
#define FLAG_PHARAOHMON_BEATEN FLAG(0xA, 0)
/* wstag405 Tyranno Valley: set with event 60, MasterTyranno lost and gives
   the Old Claw for the Seiryu Leader; never tested */
#define FLAG_MASTER_TYRANNO_BEATEN FLAG(0xA, 1)
/* wstag535/537 Catacomb: set with Zanbamon's event 1262/1455 ("I lost...",
   gives the Rusty Katana); tested 0 to offer the fight */
#define FLAG_ZANBAMON_BEATEN FLAG(0xA, 2)
/* wstag325 Asuka Control Room: set with event 375, Datamon gives the Rusty
   Gloves for winning; tested 1 for his later talks */
#define FLAG_DATAMON_BEATEN FLAG(0xA, 3)
/* wstag605 Operation Room: set with event 510, HiAndromon says "You pass!",
   opens the Secret Stairs and gives the Rusty Rifle */
#define FLAG_HIANDROMON_BEATEN FLAG(0xA, 4)
/* wstag376 Protocol Ruins: set with event 1283, BK MagnaGargomon lost and
   gives the Wild Helmet; later talks after the win */
#define FLAG_BK_MAGNAGARGOMON_BEATEN FLAG(0xA, 7)
/* wstag406 Tyranno Valley: set with event 1285, BK Imperialdramon says
   "Hey, I lost" and gives an item */
#define FLAG_BK_IMPERIALDRAMON_BEATEN FLAG(0xA, 9)
/* wstag538 Catacomb (Amaterasu server): set with event 1287, BK Seraphimon
   says the player passed and gives an item */
#define FLAG_BK_SERAPHIMON_BEATEN FLAG(0xA, 0xA)
/* wstag606 Operation Room: set with event 1289, BK WarGrowlmon lost and
   gives the Hazard Armor */
#define FLAG_BK_WARGROWLMON_BEATEN FLAG(0xA, 0xB)
/* wstag616 Sewers: set with event 1291, BK KingNumemon says "I, the King,
   lost" and gives an item */
#define FLAG_BK_KINGNUMEMON_BEATEN FLAG(0xA, 0xC)
/* wstag326 Amaterasu Control Room: set with event 1281, BK WarGreymon lost
   and gives the Platinum ID */
#define FLAG_BK_WARGREYMON_BEATEN FLAG(0xA, 0xD)
/* wstag973 Circuit Board (extra chapter): B-Sent Gargoylemon accepts the
   challenge and starts a battle; set with it */
#define FLAG_B_SENT_GARGOYLEMON_FOUGHT FLAG(0xA, 0xE)
/* wstag973 Circuit Board (extra chapter): B-IP Doramon ("you're still
   here!") starts a battle; set with it */
#define FLAG_B_IP_DORAMON_FOUGHT FLAG(0xA, 0xF)
/* wstag972 Circuit Board (extra chapter): B Seraphimon ("you must first
   defeat me") starts a battle; set with it */
#define FLAG_B_SERAPHIMON_FOUGHT FLAG(0xA, 0x10)
/* wstag973 Circuit Board (extra chapter): B MegaroGrowlmon ("You have the
   audacity to challenge me?") starts a battle; set with it */
#define FLAG_B_MEGAROGROWLMON_FOUGHT FLAG(0xA, 0x11)
/* wstag973 Circuit Board (extra chapter): B WarGreymon ("since you insist I
   will destroy you") starts a battle; set with it */
#define FLAG_B_WARGREYMON_FOUGHT FLAG(0xA, 0x12)
/* wstag972 Circuit Board (extra chapter): B King Numemon ("You still insist
   on fighting?") starts a battle; set with it */
#define FLAG_B_KING_NUMEMON_FOUGHT FLAG(0xA, 0x13)
/* wstag971 Circuit Board (extra chapter): MetalGreymon ("Alright, let's
   battle!") starts a battle, rewards an item; set with it */
#define FLAG_METALGREYMON_FOUGHT FLAG(0xA, 0x14)
/* wstag971 Circuit Board (extra chapter): MegaroGrowlmon, woken from his
   sleep, starts a battle; set with it */
#define FLAG_MEGAROGROWLMON_FOUGHT FLAG(0xA, 0x15)
/* wstag970 Circuit Board (extra chapter): Piledrimon ("If you win, I'll
   give you a valuable item") starts a battle; set with it */
#define FLAG_PILEDRIMON_FOUGHT FLAG(0xA, 0x16)
/* wstag971 Circuit Board (extra chapter): Taomon, disturbed while
   meditating, starts a battle; set with it */
#define FLAG_TAOMON_FOUGHT FLAG(0xA, 0x17)
/* wstag970 Circuit Board (extra chapter): HolyAngemon ("let's begin the
   battle") starts a battle; set with it */
#define FLAG_HOLYANGEMON_FOUGHT FLAG(0xA, 0x18)
/* wstag970 Circuit Board (extra chapter): Kyukimon ("If you fight well... a
   gift") starts a battle; set with it */
#define FLAG_KYUKIMON_FOUGHT FLAG(0xA, 0x19)
/* wstag971 Circuit Board (extra chapter): Armormon ("Are you up to a fight
   against me?") starts a battle; set with it */
#define FLAG_ARMORMON_FOUGHT FLAG(0xA, 0x1A)
/* wstag970 Circuit Board (extra chapter): GrapLeomon ("here I come!")
   starts a battle and gives an item after; set with it */
#define FLAG_GRAPLEOMON_FOUGHT FLAG(0xA, 0x1B)

/* GAME.flags0C: the A.o.A guards of the Admin Centers, set with the battle */

/* wstag285 Asuka Admin Center 1F (from progress 0x16): an A.o.A Trooper
   (char 0x132) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_ADMIN_1F_TROOPER_A_FOUGHT FLAG(0xC, 5)
/* wstag285 Asuka Admin Center 1F (from progress 0x16): an A.o.A Trooper
   (char 0x133) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_ADMIN_1F_TROOPER_B_FOUGHT FLAG(0xC, 6)
/* wstag285 Asuka Admin Center 1F (from progress 0x16): an A.o.A Trooper
   (char 0x134) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_ADMIN_1F_TROOPER_C_FOUGHT FLAG(0xC, 7)
/* wstag290 Asuka Basement Stairs (from progress 0x16): an A.o.A Trooper
   (char 0x132) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_BASEMENT_STAIRS_TROOPER_A_FOUGHT FLAG(0xC, 8)
/* wstag290 Asuka Basement Stairs (from progress 0x16): an A.o.A Trooper
   (char 0x133) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_BASEMENT_STAIRS_TROOPER_B_FOUGHT FLAG(0xC, 9)
/* wstag290 Asuka Basement Stairs (from progress 0x16): an A.o.A Trooper
   (char 0x134) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_BASEMENT_STAIRS_TROOPER_C_FOUGHT FLAG(0xC, 0xA)
/* wstag300 Asuka Admin Center 2F (from progress 0x16): an A.o.A Trooper
   (char 0x132) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_ADMIN_2F_TROOPER_A_FOUGHT FLAG(0xC, 0xB)
/* wstag300 Asuka Admin Center 2F (from progress 0x16): an A.o.A Trooper
   (char 0x133) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_ADMIN_2F_TROOPER_B_FOUGHT FLAG(0xC, 0xC)
/* wstag300 Asuka Admin Center 2F (from progress 0x16): an A.o.A Trooper
   (char 0x134) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_ADMIN_2F_TROOPER_C_FOUGHT FLAG(0xC, 0xD)
/* wstag300 Asuka Admin Center 2F (from progress 0x16): an A.o.A Trooper
   (char 0x135) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_ADMIN_2F_TROOPER_D_FOUGHT FLAG(0xC, 0xE)
/* wstag300 Asuka Admin Center 2F (from progress 0x16): an A.o.A Soldier
   (char 0x12B) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_ADMIN_2F_SOLDIER_A_FOUGHT FLAG(0xC, 0xF)
/* wstag300 Asuka Admin Center 2F (from progress 0x16): an A.o.A Soldier
   (char 0x12F) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_ADMIN_2F_SOLDIER_B_FOUGHT FLAG(0xC, 0x10)
/* wstag300 Asuka Admin Center 2F: the Soldier "not letting you pass" (char
   0x130); set with his battle, from his talk or the end of event 570 */
#define FLAG_ASUKA_ADMIN_2F_SOLDIER_C_FOUGHT FLAG(0xC, 0x11)
/* wstag310 A.o.A Headquarters (Asuka): set at the end of event 680
   (Operation Sigma announced) with the battle against Guards A, B and C */
#define FLAG_ASUKA_AOA_HQ_GUARDS_FOUGHT FLAG(0xC, 0x13)
/* wstag315 Asuka Admin Center B1F (from progress 0x16): an A.o.A Trooper
   (char 0x132) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_ADMIN_B1F_TROOPER_A_FOUGHT FLAG(0xC, 0x14)
/* wstag315 Asuka Admin Center B1F (from progress 0x16): an A.o.A Trooper
   (char 0x133) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_ADMIN_B1F_TROOPER_B_FOUGHT FLAG(0xC, 0x15)
/* wstag315 Asuka Admin Center B1F (from progress 0x16): an A.o.A Trooper
   (char 0x134) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_ADMIN_B1F_TROOPER_C_FOUGHT FLAG(0xC, 0x16)
/* wstag315 Asuka Admin Center B1F (from progress 0x16): an A.o.A Trooper
   (char 0x136) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_ADMIN_B1F_TROOPER_D_FOUGHT FLAG(0xC, 0x17)
/* wstag315 Asuka Admin Center B1F (from progress 0x16): an A.o.A Trooper
   (char 0x137) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_ASUKA_ADMIN_B1F_TROOPER_E_FOUGHT FLAG(0xC, 0x18)
/* wstag211 Amaterasu Main Lobby: set with the Attacker's battle, from his
   talk or the end of event 925; tested 0 so he appears */
#define FLAG_AMATERASU_LOBBY_ATTACKER_FOUGHT FLAG(0xC, 0x23)
/* wstag286 Amaterasu Admin Center 1F (from progress 0x25): an A.o.A Soldier
   (char 0x12F) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_AMATERASU_ADMIN_1F_SOLDIER_A_FOUGHT FLAG(0xC, 0x25)
/* wstag286 Amaterasu Admin Center 1F (from progress 0x25): an A.o.A Soldier
   (char 0x12B) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_AMATERASU_ADMIN_1F_SOLDIER_B_FOUGHT FLAG(0xC, 0x26)
/* wstag286 Amaterasu Admin Center 1F (from progress 0x25): an A.o.A
   Attacker (char 0x12D) starts a battle; set with it, tested 0 so he stands
   there */
#define FLAG_AMATERASU_ADMIN_1F_ATTACKER_A_FOUGHT FLAG(0xC, 0x27)
/* wstag291 Amaterasu Basement Stairs (from progress 0x25): an A.o.A Soldier
   (char 0x12B) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_AMATERASU_BASEMENT_STAIRS_SOLDIER_A_FOUGHT FLAG(0xC, 0x28)
/* wstag291 Amaterasu Basement Stairs (from progress 0x25): an A.o.A Soldier
   (char 0x12F) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_AMATERASU_BASEMENT_STAIRS_SOLDIER_B_FOUGHT FLAG(0xC, 0x29)
/* wstag291 Amaterasu Basement Stairs (from progress 0x25): an A.o.A
   Attacker (char 0x12D) starts a battle; set with it, tested 0 so he stands
   there */
#define FLAG_AMATERASU_BASEMENT_STAIRS_ATTACKER_A_FOUGHT FLAG(0xC, 0x2A)
/* wstag301 Amaterasu Admin Center 2F (from progress 0x25): an A.o.A Soldier
   (char 0x12B) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_AMATERASU_ADMIN_2F_SOLDIER_A_FOUGHT FLAG(0xC, 0x2B)
/* wstag301 Amaterasu Admin Center 2F (from progress 0x25): an A.o.A Soldier
   (char 0x12F) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_AMATERASU_ADMIN_2F_SOLDIER_B_FOUGHT FLAG(0xC, 0x2C)
/* wstag301 Amaterasu Admin Center 2F (from progress 0x25): an A.o.A Soldier
   (char 0x130) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_AMATERASU_ADMIN_2F_SOLDIER_C_FOUGHT FLAG(0xC, 0x2D)
/* wstag301 Amaterasu Admin Center 2F (from progress 0x25): an A.o.A Soldier
   (char 0x131) starts a battle; set with it, tested 0 so he stands there */
#define FLAG_AMATERASU_ADMIN_2F_SOLDIER_D_FOUGHT FLAG(0xC, 0x2E)
/* wstag301 Amaterasu Admin Center 2F (from progress 0x25): an A.o.A
   Attacker (char 0x12D) starts a battle; set with it, tested 0 so he stands
   there */
#define FLAG_AMATERASU_ADMIN_2F_ATTACKER_A_FOUGHT FLAG(0xC, 0x30)
/* wstag301 Amaterasu Admin Center 2F (from progress 0x25): an A.o.A
   Attacker (char 0x12E) starts a battle; set with it, tested 0 so he stands
   there */
#define FLAG_AMATERASU_ADMIN_2F_ATTACKER_B_FOUGHT FLAG(0xC, 0x31)
/* wstag311 A.o.A Headquarters (Amaterasu): set at the end of event 931 (the
   Chief Officer) with the battle against the Royal Guard (actors 4-6 shown
   while 0) */
#define FLAG_ROYAL_GUARDS_FOUGHT FLAG(0xC, 0x33)
/* wstag316 Amaterasu Admin Center B1F (from progress 0x25): an A.o.A
   Soldier (char 0x12B) starts a battle; set with it, tested 0 so he stands
   there */
#define FLAG_AMATERASU_ADMIN_B1F_SOLDIER_A_FOUGHT FLAG(0xC, 0x34)
/* wstag316 Amaterasu Admin Center B1F (from progress 0x25): an A.o.A
   Soldier (char 0x12F) starts a battle; set with it, tested 0 so he stands
   there */
#define FLAG_AMATERASU_ADMIN_B1F_SOLDIER_B_FOUGHT FLAG(0xC, 0x35)
/* wstag316 Amaterasu Admin Center B1F (from progress 0x25): an A.o.A
   Soldier (char 0x130) starts a battle; set with it, tested 0 so he stands
   there */
#define FLAG_AMATERASU_ADMIN_B1F_SOLDIER_C_FOUGHT FLAG(0xC, 0x36)
/* wstag316 Amaterasu Admin Center B1F (from progress 0x25): an A.o.A
   Attacker (char 0x12D) starts a battle; set with it, tested 0 so he stands
   there */
#define FLAG_AMATERASU_ADMIN_B1F_ATTACKER_A_FOUGHT FLAG(0xC, 0x38)
/* wstag316 Amaterasu Admin Center B1F (from progress 0x25): an A.o.A
   Attacker (char 0x12E) starts a battle; set with it, tested 0 so he stands
   there */
#define FLAG_AMATERASU_ADMIN_B1F_ATTACKER_B_FOUGHT FLAG(0xC, 0x39)

/* GAME.flags0E: the roaming tamers' and the troopers' battles, set with the
   battle */

/* wstag200 (Asuka City): Tamer Genji says "Let's see how well you've
   trained your Digimon." and starts a Digimon battle; set with the battle */
#define FLAG_GENJI_FOUGHT FLAG(0xE, 0)
/* wstag330 (Central Park): Tamer Natsumi says "Hey, let's Digimon Battle!"
   and starts a Digimon battle; set with the battle */
#define FLAG_NATSUMI_FOUGHT FLAG(0xE, 1)
/* wstag335 (Wire Forest Entrance): Tamer Mitch says "Hey you, let's Digimon
   Battle!" and starts a Digimon battle; set with the battle */
#define FLAG_MITCH_FOUGHT FLAG(0xE, 2)
/* wstag350 (West Wire Forest): Tamer Catherine says "Let's Digimon Battle
   now... but go easy on me." and starts a Digimon battle; set with the
   battle */
#define FLAG_CATHERINE_FOUGHT FLAG(0xE, 3)
/* wstag355 (East Wire Forest): Tamer Lucia says "I'm still a pro at Digimon
   Battle!" and starts a Digimon battle; set with the battle */
#define FLAG_LUCIA_FOUGHT FLAG(0xE, 4)
/* wstag355 (East Wire Forest): Tamer Robert says "I'm not doing anything,
   so I'll play with you in a Digimon B" and starts a Digimon battle; set
   with the battle */
#define FLAG_ROBERT_FOUGHT FLAG(0xE, 5)
/* wstag395 (Wind Prairie): Tamer Akiba says "All I need is to Digimon
   Battle now!" and starts a Digimon battle; set with the battle */
#define FLAG_AKIBA_FOUGHT FLAG(0xE, 6)
/* wstag400 (Kicking Forest): Tamer Bob says "I guess you must battle to get
   the answer." and starts a Digimon battle; set with the battle */
#define FLAG_BOB_FOUGHT FLAG(0xE, 7)
/* wstag410 (East Station): Tamer Tomomi says "I know, I'll decide with
   this!" and starts a Digimon battle; set with the battle */
#define FLAG_TOMOMI_FOUGHT FLAG(0xE, 8)
/* wstag420 (Seiryu City): Tamer Chris says "All right then! Digimon
   Battle!" and starts a Digimon battle; set with the battle */
#define FLAG_CHRIS_FOUGHT FLAG(0xE, 9)
/* wstag440 (South Station): Tamer Andy says "I'll prove it by showing you
   my powers." and starts a Digimon battle; set with the battle */
#define FLAG_ANDY_FOUGHT FLAG(0xE, 0xA)
/* wstag445 (Bulk Swamp): Tamer George says "I'll show who's the boss in
   Digimon Battle!" and starts a Digimon battle; set with the battle */
#define FLAG_GEORGE_FOUGHT FLAG(0xE, 0xB)
/* wstag450 (Bulk Bridge): Tamer Mei Lin says "Then let's Digimon Battle!"
   and starts a Digimon battle; set with the battle */
#define FLAG_MEI_LIN_FOUGHT FLAG(0xE, 0xC)
/* wstag465 (Tranquil Swamp): Tamer Jessica says "Well, shall we start this
   battle?" and starts a Digimon battle; set with the battle */
#define FLAG_JESSICA_FOUGHT FLAG(0xE, 0xD)
/* wstag495 (South Cape): Tamer Gordon says "Then let's Digimon Battle!" and
   starts a Digimon battle; set with the battle */
#define FLAG_GORDON_FOUGHT FLAG(0xE, 0xE)
/* wstag500 (Suzaku City): Tamer Alice says "...if it's... ...Digimon
   Battle..." and starts a Digimon battle; set with the battle */
#define FLAG_ALICE_FOUGHT FLAG(0xE, 0xF)
/* wstag650 (Mirage Hall): Tamer Nakano says "Oh - your Digimon look
   interesting." and starts a Digimon battle; set with the battle */
#define FLAG_NAKANO_FOUGHT FLAG(0xE, 0x10)
/* wstag690 (Boot Mountain): Tamer Haruka says "I can defeat your Digimon so
   easily!" and starts a Digimon battle; set with the battle */
#define FLAG_HARUKA_FOUGHT FLAG(0xE, 0x11)
/* wstag695 (Snow Mountain): Tamer Poemy says "Oh, great Hero!" and starts a
   Digimon battle; set with the battle */
#define FLAG_POEMY_FOUGHT FLAG(0xE, 0x12)
/* wstag705 (Freeze Mountain): Tamer Shingo says "So, first I'll defeat you
   in a battle!" and starts a Digimon battle; set with the battle */
#define FLAG_SHINGO_FOUGHT FLAG(0xE, 0x13)
/* wstag710 (Kulon Mine): Tamer Makoto says "So can you duel with me and
   throw the fight?" and starts a Digimon battle; set with the battle */
#define FLAG_MAKOTO_FOUGHT FLAG(0xE, 0x14)
/* wstag710 (Kulon Mine): Tamer Brown says "I'm still an active tamer
   though. Ho ho ho ho." and starts a Digimon battle; set with the battle */
#define FLAG_BROWN_FOUGHT FLAG(0xE, 0x15)
/* wstag720 (Legendary Gym): Tamer Pierre says "Monsieur, how great are your
   Digimon? Please show me." and starts a Digimon battle; set with the
   battle */
#define FLAG_PIERRE_FOUGHT FLAG(0xE, 0x16)
/* wstag725 (Kulon Pit): Tamer Mitaka says "Though I may perish, I will
   defeat you!" and starts a Digimon battle; set with the battle */
#define FLAG_MITAKA_FOUGHT FLAG(0xE, 0x17)
/* wstag331 (Central Park): a Trooper says "You're suspicious." and starts a
   battle; set with it */
#define FLAG_CENTRAL_PARK_TROOPER_FOUGHT FLAG(0xE, 0x1B)
/* wstag351 (West Wire Forest): a Trooper says "You're suspicious." and
   starts a battle; set with it */
#define FLAG_WEST_WIRE_FOREST_TROOPER_FOUGHT FLAG(0xE, 0x1C)
/* wstag396 (Wind Prairie): a Trooper says "You're suspicious." and starts a
   battle; set with it */
#define FLAG_WIND_PRAIRIE_TROOPER_FOUGHT FLAG(0xE, 0x1E)
/* wstag401 (Kicking Forest): a Trooper says "You're suspicious." and starts
   a battle; set with it */
#define FLAG_KICKING_FOREST_TROOPER_FOUGHT FLAG(0xE, 0x1F)
/* wstag446 (Bulk Swamp): a Trooper says "You're suspicious." and starts a
   battle; set with it */
#define FLAG_BULK_SWAMP_TROOPER_FOUGHT FLAG(0xE, 0x20)
/* wstag451 (Bulk Bridge): a Trooper says "You're suspicious." and starts a
   battle; set with it */
#define FLAG_BULK_BRIDGE_TROOPER_FOUGHT FLAG(0xE, 0x21)
/* wstag466 (Tranquil Swamp): a Trooper says "You're suspicious." and starts
   a battle; set with it */
#define FLAG_TRANQUIL_SWAMP_TROOPER_FOUGHT FLAG(0xE, 0x22)
/* wstag501 (Zhu Que City): a Trooper says "You're suspicious." and starts a
   battle; set with it */
#define FLAG_ZHU_QUE_CITY_TROOPER_FOUGHT FLAG(0xE, 0x23)
/* wstag551 (South Badland): a Trooper says "You're suspicious." and starts
   a battle; set with it */
#define FLAG_SOUTH_BADLAND_TROOPER_FOUGHT FLAG(0xE, 0x25)
/* wstag556 (Noise Desert): a Trooper says "You're suspicious." and starts a
   battle; set with it */
#define FLAG_NOISE_DESERT_TROOPER_FOUGHT FLAG(0xE, 0x26)
/* wstag566 (North Badland W): a Trooper says "You're suspicious." and
   starts a battle; set with it */
#define FLAG_NORTH_BADLAND_WEST_TROOPER_FOUGHT FLAG(0xE, 0x27)
/* wstag571 (North Badland E): a Trooper says "You're suspicious." and
   starts a battle; set with it */
#define FLAG_NORTH_BADLAND_EAST_TROOPER_FOUGHT FLAG(0xE, 0x28)
/* wstag631 (S Noise Desert): a Trooper says "You're suspicious." and starts
   a battle; set with it */
#define FLAG_SOUTH_NOISE_DESERT_TROOPER_FOUGHT FLAG(0xE, 0x29)
/* wstag646 (Mirage Tower): Tamer Heinrich says "Hey, since we're here, how
   about a battle?" and starts a Digimon battle; set with the battle */
#define FLAG_HEINRICH_FOUGHT FLAG(0xE, 0x2A)
/* wstag651 (Mirage Hall): Tamer Takuya says "Well, let's see how good you
   are in a battle." and starts a Digimon battle; set with the battle */
#define FLAG_TAKUYA_FOUGHT FLAG(0xE, 0x2B)
/* wstag651 (Mirage Hall): Tamer Murdock says "Worrying about it here won't
   make a difference." and starts a Digimon battle; set with the battle */
#define FLAG_MURDOCK_FOUGHT FLAG(0xE, 0x2C)
/* wstag651 (Mirage Hall): Guard Banch says "If you're not a spy defeat me
   in battle!" and starts a Digimon battle; set with the battle */
#define FLAG_BANCH_FOUGHT FLAG(0xE, 0x2D)
/* wstag691 (Boot Mountain): a Trooper says "You're suspicious." and starts
   a battle; set with it */
#define FLAG_BOOT_MOUNTAIN_TROOPER_FOUGHT FLAG(0xE, 0x2F)
/* wstag696 (Snow Mountain): a Trooper says "You're suspicious." and starts
   a battle; set with it */
#define FLAG_SNOW_MOUNTAIN_TROOPER_FOUGHT FLAG(0xE, 0x31)
/* wstag706 (Freeze Mountain): a Trooper says "Hey, you wanna Digimon Battle
   with me?" and starts a battle; set with it */
#define FLAG_FREEZE_MOUNTAIN_TROOPER_FOUGHT FLAG(0xE, 0x32)
/* wstag721 (Legendary Gym): Tamer Mai says "It's safe here. You can battle
   here." and starts a Digimon battle; set with the battle */
#define FLAG_MAI_FOUGHT FLAG(0xE, 0x34)
/* wstag721 (Legendary Gym): Tamer Gon says "...I guess I'll fight as well!"
   and starts a Digimon battle; set with the battle */
#define FLAG_GON_FOUGHT FLAG(0xE, 0x35)
/* wstag761 (Xuan Wu City): a Trooper says "Oh, you're that tamer! Let's
   battle!" and starts a battle; set with it */
#define FLAG_XUAN_WU_CITY_TROOPER_FOUGHT FLAG(0xE, 0x3B)

/* GAME.flags10: the extra chapter's (European and Japanese versions) */

/* wstag927 (extra chapter) event 1608: the player beat Kurt and is the new
   strongest tamer; set at its end, tested to start it */
#define FLAG_KURT_ARENA_WIN_SEEN FLAG(0x10, 0xC)
/* wstag956 (extra chapter): the Chinron Leader sees the 5 strongest Epic
   Items and starts a battle; set with the battle */
#define FLAG_CHINRON_LEADER_FOUGHT FLAG(0x10, 0xD)
/* wstag949 (extra chapter): the Zhu Que Leader sees the 5 strongest Epic
   Items and starts a battle; set with the battle */
#define FLAG_ZHU_QUE_LEADER_FOUGHT FLAG(0x10, 0xE)
/* wstag949 (extra chapter): the Bai Hu Leader sees the 5 strongest Epic
   Items and starts a battle; set with the battle */
#define FLAG_BAI_HU_LEADER_FOUGHT FLAG(0x10, 0xF)
/* wstag954 (extra chapter): the Xuan Wu Leader sees the 5 Epic Items and
   starts a battle; set with the battle */
#define FLAG_XUAN_WU_LEADER_FOUGHT FLAG(0x10, 0x10)
/* wstag951 Duel Island (extra chapter): Keith loses the card battle and
   gives the KoC Trophy, "proof that you beat the Card King" */
#define FLAG_CARD_KING_KEITH_BEATEN FLAG(0x10, 0x11)
/* wstag951 Duel Island (extra chapter): Tamer Alice loses the card battle
   ("I...lose") and lets the player pass */
#define FLAG_DUEL_ISLAND_ALICE_BEATEN FLAG(0x10, 0x12)
/* wstag951 Duel Island (extra chapter): Tamer Bomujii loses the card battle
   and lets the player proceed */
#define FLAG_DUEL_ISLAND_BOMUJII_BEATEN FLAG(0x10, 0x13)
/* wstag951 Duel Island (extra chapter): Tamer Pierre is "defeated soundly"
   at cards and lets the player pass */
#define FLAG_DUEL_ISLAND_PIERRE_BEATEN FLAG(0x10, 0x14)
/* wstag951 Duel Island (extra chapter): Tamer Poemy loses the card battle
   and lets the "Hero" go on */
#define FLAG_DUEL_ISLAND_POEMY_BEATEN FLAG(0x10, 0x15)
/* wstag951 Duel Island (extra chapter): Tamer Haruka loses the card battle
   ("once in awhile one does have to let others win") */
#define FLAG_DUEL_ISLAND_HARUKA_BEATEN FLAG(0x10, 0x16)

/* GAME.flags18: the extra chapter's (European and Japanese versions) */

/* wstag928 Amaterasu Inn 1F (extra chapter): "Hey! There's something here!
   I got 8500 BIT!!"; afterwards "nothing here" */
#define FLAG_AMATERASU_INN_BIT_FOUND FLAG(0x18, 5)
/* wstag936 Water Tunnel (extra chapter): the player finds a Platinum
   Members Card in a crack (item 0x25 given) */
#define FLAG_PLATINUM_CARD_FOUND FLAG(0x18, 6)

/* GAME.flags1A: what the characters have said and done */

/* wstag210 Main Lobby: the Tamer Service / Guide at the Digimon Online Help
   Counter introduce the hints once; set there, later talks differ */
#define FLAG_HELP_COUNTER_TALKED FLAG(0x1A, 0)
/* wstag485 Phoenix Bay: Nami saw a Crest behind the Bios Swamp shrine; then
   the player recognises the Symbol of Sincerity there */
#define FLAG_NAMI_SWAMP_CREST_TALKED FLAG(0x1A, 2)
/* wstag220 Digimon Lab: Dr. Kadomatsu introduces himself and the lab once;
   set there, later talks differ */
#define FLAG_KADOMATSU_TALKED FLAG(0x1A, 4)
/* wstag280 El Dorado: Ponchomon welcomes the player to the Item Maniac's El
   Dorado once; set there, later talks differ */
#define FLAG_PONCHOMON_TALKED FLAG(0x1A, 5)
/* wstag220 Digimon Lab: the Digivolve Navi explains its desk once; set
   there, later talks differ */
#define FLAG_DIGIVOLVE_NAVI_TALKED FLAG(0x1A, 6)
/* wstag220 Digimon Lab: the Digimon Navi explains its desk once; set there,
   later talks differ */
#define FLAG_DIGIMON_NAVI_TALKED FLAG(0x1A, 7)
/* Inns (wstag235/360/425/470): Gatomon says they manage the Inn once; set
   there, later talks differ */
#define FLAG_INN_GATOMON_TALKED FLAG(0x1A, 8)
/* Inns (wstag235/360/430/470): Save Officer Guardromon introduces saving
   once; set there, later talks differ */
#define FLAG_SAVE_GUARDROMON_TALKED FLAG(0x1A, 9)
/* wstag435 Gale Tower: Airdramon spins the windmill and turns everyone back
   from Oinkmon; tested in 62 stages (talks "back to normal") */
#define FLAG_OINKMON_CITIZENS_RESTORED FLAG(0x1A, 0xA)
/* wstag255 Lamb Chop: Master John says lost Digimon may enter the Admin
   Center; Kail's talk then picks up that idea */
#define FLAG_MASTER_JOHN_LOST_DIGIMON_TALKED FLAG(0x1A, 0xC)
/* wstag245/425: Gargomon says the Armory is run by them once; set there,
   later talks differ */
#define FLAG_ARMORY_GARGOMON_TALKED FLAG(0x1A, 0xE)
/* wstag245/425: Wizardmon says they run the Item Shop once; set there,
   later talks differ */
#define FLAG_ITEM_SHOP_WIZARDMON_TALKED FLAG(0x1A, 0xF)
/* wstag245 Smith's Shop: Gomamon introduces the Pawn Shop once; set there,
   later talks differ */
#define FLAG_PAWN_SHOP_GOMAMON_TALKED FLAG(0x1A, 0x10)
/* wstag245 Smith's Shop: Mr. Smith introduces himself as the manager once;
   set there, later talks differ */
#define FLAG_MR_SMITH_TALKED FLAG(0x1A, 0x11)
/* wstag250 Junk Shop: Gargomon introduces the Heavy Armory once; set there,
   later talks differ */
#define FLAG_HEAVY_ARMORY_GARGOMON_TALKED FLAG(0x1A, 0x12)
/* wstag250 Junk Shop: Wizardmon introduces the Black Market once; set
   there, later talks differ */
#define FLAG_BLACK_MARKET_WIZARDMON_TALKED FLAG(0x1A, 0x13)
/* wstag202: Jake and Grandma Beth show their Digimon suits from Etemon;
   then a man replaces Etemon in the Asuka Sewers */
#define FLAG_SUIT_COUPLE_TALKED FLAG(0x1A, 0x14)
/* wstag320 Asuka Sewers: Mischievous Mat says no Etemon was there; Kail
   then reacts to "a man instead of Etemon" */
#define FLAG_MISCHIEVOUS_MAT_TALKED FLAG(0x1A, 0x15)
/* wstag210 Main Lobby: Kail explains the man used an Etemon Suit and sends
   the player to ask about Digimon suits */
#define FLAG_KAIL_ETEMON_SUIT_TALKED FLAG(0x1A, 0x16)
/* wstag475 Shaman House event 180: the player meets maskless Sepikmon ("A
   monster!"), who asks for his mask; keeps it from playing again */
#define FLAG_SEPIKMON_LOST_MASK_SEEN FLAG(0x1A, 0x17)
/* wstag375 Protocol Ruins: Baronmon says Sepikmon had his mask and was last
   seen in Asuka City; Asuka talks of his pranks follow */
#define FLAG_BARONMON_SEPIKMON_TALKED FLAG(0x1A, 0x18)
/* wstag205 Asuka Bridge: a "Sepikmon" boasts he found his mask and won't
   help; then Etemon says Sepikmon ran to Divermon Lake */
#define FLAG_BRIDGE_SEPIKMON_TALKED FLAG(0x1A, 0x19)
/* wstag202: Etemon says Sepikmon ran towards the Divermon Lake; set there,
   tested at Divermon's Lake */
#define FLAG_ETEMON_DIVERMON_LAKE_TALKED FLAG(0x1A, 0x1A)
/* wstag270/425: Divermon says they handle Booster Packs once (also set
   after event 1415 with the Folder Bag); later talks differ */
#define FLAG_BOOSTER_DIVERMON_TALKED FLAG(0x1A, 0x1C)
/* wstag330 Central Park: DRI Kazuki introduces himself as the MagnaAngemon
   researcher once; set there, later talks differ */
#define FLAG_DRI_KAZUKI_TALKED FLAG(0x1A, 0x1F)
/* wstag330 Central Park: DRI Michael (Mike) introduces himself and asks for
   his Taomon once; set there, later talks differ */
#define FLAG_DRI_MICHAEL_TALKED FLAG(0x1A, 0x20)
/* wstag340 Shell Beach: Tai Kong Wang offers to make a fishing pole from a
   pole, string and hook; tested at Divermon's Lake */
#define FLAG_TAI_KONG_WANG_POLE_TALKED FLAG(0x1A, 0x21)
/* wstag235 Asuka Inn 1F: "Oh! It's Gabumon card! So that's where it was!"
   (card 0xB7 given); afterwards "nothing left" */
#define FLAG_HIDE_GABUMON_CARD_FOUND FLAG(0x1A, 0x23)
/* wstag345 Plug Cape: Soccer Kid Hide gets his Gabumon card back and tells
   about the Tree Boots and Veemon */
#define FLAG_HIDE_GABUMON_CARD_GIVEN FLAG(0x1A, 0x24)
/* wstag255 Lamb Chop: Waitress Debbie saw Veemon looking for something at
   Wind Prairie; makes Veemon appear there, cleared when his game starts */
#define FLAG_DEBBIE_VEEMON_TALKED FLAG(0x1A, 0x25)
/* wstag395 Wind Prairie: set when Veemon asks "You want to play?"; Kicking
   Forest hiders appear; cleared on finding him or giving up */
#define FLAG_VEEMON_HIDE_AND_SEEK_ACTIVE FLAG(0x1A, 0x26)
/* wstag395 Wind Prairie event 1305: Veemon gives the player the Tree Boots;
   set at its end, keeps it from playing again */
#define FLAG_VEEMON_TREE_BOOTS_SEEN FLAG(0x1A, 0x28)
/* wstag375 Protocol Ruins: DRI Bob introduces himself once ("I'll tell you
   a secret"); set there, later talks differ */
#define FLAG_DRI_BOB_TALKED FLAG(0x1A, 0x29)
/* wstag455 Bios Swamp: "There it is! The Symbol of Sincerity!" behind a
   wall; then Sepikmon advises asking Baronmon about bombs */
#define FLAG_SINCERITY_SYMBOL_FOUND FLAG(0x1A, 0x2A)
/* wstag475 Shaman House: Sepikmon says to ask his friend Baronmon about
   bombs; Baronmon then talks about the TNT Chip */
#define FLAG_SEPIKMON_BOMB_HINT_TALKED FLAG(0x1A, 0x2B)
/* wstag380 Divermon's Lake: the player frees a Red Snapper stuck in
   Divermon's throat and gets it (item 7); later talks differ */
#define FLAG_DIVERMON_RED_SNAPPER_TAKEN FLAG(0x1A, 0x2C)
/* wstag405 Tyranno Valley: DRI Johann introduces himself as the Agumon
   researcher once; set there, later talks differ */
#define FLAG_DRI_JOHANN_TALKED FLAG(0x1A, 0x2D)
/* wstag420 Seiryu City: DRI Jimmy introduces himself as a DRI researcher
   once; set there, later talks differ */
#define FLAG_DRI_JIMMY_TALKED FLAG(0x1A, 0x2E)
/* wstag635 Mobius Desert: DRI Ken introduces himself as an athletic
   researcher once; set there, later talks differ */
#define FLAG_DRI_KEN_TALKED FLAG(0x1A, 0x2F)
/* wstag635 Mobius Desert: DRI Yuji introduces himself once; set there,
   later talks differ */
#define FLAG_DRI_YUJI_TALKED FLAG(0x1A, 0x30)
/* wstag635 Mobius Desert: DRI Yang, with a twisted ankle, introduces
   himself once; set there, later talks differ */
#define FLAG_DRI_YANG_TALKED FLAG(0x1A, 0x31)
/* wstag430 Seiryu Tower: Piximon says it handles Digimon data (switching)
   once; set there, later talks differ */
#define FLAG_SEIRYU_PIXIMON_TALKED FLAG(0x1A, 0x33)
/* wstag656 Mirage Room: Leader Chuck recognises the player and an event
   starts; Lisa (Master Room) then asks "Did you find someone?" */
#define FLAG_RESISTANCE_CHUCK_MET FLAG(0x1A, 0x34)
/* wstag340 Shell Beach: Fisherman Tai Kong Wang introduces himself once;
   set there, later talks differ */
#define FLAG_TAI_KONG_WANG_TALKED FLAG(0x1A, 0x36)
/* wstag386 Duel Island: MetalEtemon loses the card battle ("...I lost!");
   cleared when KingEtemon loses */
#define FLAG_DUEL_ISLAND_METALETEMON_BEATEN FLAG(0x1A, 0x40)

/* GAME.flags1C: the story's states, puzzles and talks */

/* wstag750 Chamber Room: Chamber Clark checks the 4 Leader Badges and the
   player goes to the Real World; afterwards "the Matrix Chamber cannot be
   used" */
#define FLAG_MATRIX_CHAMBER_USED FLAG(0x1C, 2)
/* wstag285 Admin Center 1F event 340: Kail suddenly leaves and the player
   sets off for West Sector after Lucky Mouse; keeps it from playing again */
#define FLAG_KAIL_LEAVES_SEEN FLAG(0x1C, 0xC)
/* wstag305 Master Room event 350: the Game Master finds the player and Kail
   looking for Teddy; set at its end, tested in 4 stages */
#define FLAG_GAME_MASTER_MEETING_SEEN FLAG(0x1C, 0xD)
/* wstag430 Seiryu Tower: Repeating Tom says the Seiryu Leader trains at the
   Protocol Ruins; the Leader is named there afterwards */
#define FLAG_TOM_SEIRYU_LEADER_TALKED FLAG(0x1C, 0xF)
/* wstag375 Protocol Ruins: the Seiryu Leader won't fight until
   MasterTyranno is beaten; MasterTyranno then accepts a challenge */
#define FLAG_SEIRYU_LEADER_REFUSED FLAG(0x1C, 0x10)
/* wstag445 Bulk Swamp: set when talking to MetalGreymon starts his Agumon
   DDNA challenge event; later he says to use the DNA well */
#define FLAG_METALGREYMON_DDNA_FOUGHT FLAG(0x1C, 0x12)
/* wstag490 Ether Jungle: set when talking to WarGrowlmon starts his Guilmon
   DDNA challenge event; later "That battle was great!" */
#define FLAG_WARGROWLMON_DDNA_FOUGHT FLAG(0x1C, 0x13)
/* wstag550 South Badland: set when talking to MagnaAngemon starts his
   Patamon DDNA challenge event; later talks differ */
#define FLAG_MAGNAANGEMON_DDNA_FOUGHT FLAG(0x1C, 0x14)
/* wstag565 North Badland W: set when talking to Taomon starts her Renamon
   DDNA challenge event; later talks differ */
#define FLAG_TAOMON_DDNA_FOUGHT FLAG(0x1C, 0x15)
/* wstag525 Suzaku UG Lake: set when talking to Kyukimon starts his Kotemon
   DDNA challenge event; later talks differ */
#define FLAG_KYUKIMON_DDNA_FOUGHT FLAG(0x1C, 0x16)
/* wstag385 Duel Island: set when talking to Armormon starts his Monmon DDNA
   challenge event; later "I lost to you..." */
#define FLAG_ARMORMON_DDNA_FOUGHT FLAG(0x1C, 0x17)
/* wstag490 Ether Jungle: set when talking to GrapLeomon starts his Kumamon
   DDNA challenge event; later talks differ */
#define FLAG_GRAPLEOMON_DDNA_FOUGHT FLAG(0x1C, 0x18)
/* wstag450 Bulk Bridge: set when talking to Paildramon starts his Veemon
   DDNA challenge event; later talks differ */
#define FLAG_PAILDRAMON_DDNA_FOUGHT FLAG(0x1C, 0x19)
/* wstag325 Control Room: Datamon will open the basement gate only for a DO
   Staff Pass holder; set by that talk, later talks differ */
#define FLAG_DATAMON_STAFF_PASS_TALKED FLAG(0x1C, 0x1B)
/* wstag620 Secret Room: set after event 540; then Lisa says "Find Keith and
   Nick" and people in 10 stages answer about them */
#define FLAG_KEITH_NICK_SEARCH_STARTED FLAG(0x1C, 0x1C)
/* wstag245 Smith's Shop: with the El Dorado ID, talking to the staff starts
   the event where Smith Junior lets the player pass through */
#define FLAG_SMITH_EL_DORADO_ID_SHOWN FLAG(0x1C, 0x1E)
/* wstag305 Master Room: the player touches the "M" letter sensor of
   MONSTER; all sensor flags are cleared once every letter is touched */
#define FLAG_MASTER_ROOM_SENSOR_M_TOUCHED FLAG(0x1C, 0x27)
/* wstag305 Master Room: the player touches the "O" letter sensor of
   MONSTER; all sensor flags are cleared once every letter is touched */
#define FLAG_MASTER_ROOM_SENSOR_O_TOUCHED FLAG(0x1C, 0x28)
/* wstag305 Master Room: the player touches the "N" letter sensor of
   MONSTER; all sensor flags are cleared once every letter is touched */
#define FLAG_MASTER_ROOM_SENSOR_N_TOUCHED FLAG(0x1C, 0x29)
/* wstag305 Master Room: the player touches the "S" letter sensor of
   MONSTER; all sensor flags are cleared once every letter is touched */
#define FLAG_MASTER_ROOM_SENSOR_S_TOUCHED FLAG(0x1C, 0x2A)
/* wstag305 Master Room: the player touches the "T" letter sensor of
   MONSTER; all sensor flags are cleared once every letter is touched */
#define FLAG_MASTER_ROOM_SENSOR_T_TOUCHED FLAG(0x1C, 0x2B)
/* wstag305 Master Room: the player touches the "E" letter sensor of
   MONSTER; all sensor flags are cleared once every letter is touched */
#define FLAG_MASTER_ROOM_SENSOR_E_TOUCHED FLAG(0x1C, 0x2C)
/* wstag305 Master Room: the player touches the "R" letter sensor of
   MONSTER; all sensor flags are cleared once every letter is touched */
#define FLAG_MASTER_ROOM_SENSOR_R_TOUCHED FLAG(0x1C, 0x2D)
/* wstag305 Master Room: set when the "M" sensor is touched right after the
   previous letters of MONSTER in order; cleared with the others */
#define FLAG_MASTER_ROOM_SENSOR_M_IN_ORDER FLAG(0x1C, 0x2E)
/* wstag305 Master Room: set when the "O" sensor is touched right after the
   previous letters of MONSTER in order; cleared with the others */
#define FLAG_MASTER_ROOM_SENSOR_O_IN_ORDER FLAG(0x1C, 0x2F)
/* wstag305 Master Room: set when the "N" sensor is touched right after the
   previous letters of MONSTER in order; cleared with the others */
#define FLAG_MASTER_ROOM_SENSOR_N_IN_ORDER FLAG(0x1C, 0x30)
/* wstag305 Master Room: set when the "S" sensor is touched right after the
   previous letters of MONSTER in order; cleared with the others */
#define FLAG_MASTER_ROOM_SENSOR_S_IN_ORDER FLAG(0x1C, 0x31)
/* wstag305 Master Room: set when the "T" sensor is touched right after the
   previous letters of MONSTER in order; cleared with the others */
#define FLAG_MASTER_ROOM_SENSOR_T_IN_ORDER FLAG(0x1C, 0x32)
/* wstag305 Master Room: set when the "E" sensor is touched right after the
   previous letters of MONSTER in order; cleared with the others */
#define FLAG_MASTER_ROOM_SENSOR_E_IN_ORDER FLAG(0x1C, 0x33)
/* wstag235 Asuka Inn 1F: "Hey! Someone hid money here! I got 300 BIT!";
   afterwards "There's nothing left" */
#define FLAG_ASUKA_INN_BIT_FOUND FLAG(0x1C, 0x34)
/* wstag475 Shaman House: Baronmon announces his "Change Account" art for
   renaming Digimon once; later talks differ */
#define FLAG_BARONMON_CHANGE_ACCOUNT_TALKED FLAG(0x1C, 0x35)
/* wstag305 Master Room: "OK, I touched all the sensors, so now what?"
   (letter flags cleared, event starts); cleared after event 660 */
#define FLAG_MASTER_ROOM_SENSORS_ALL_TOUCHED FLAG(0x1C, 0x36)
/* wstag305 Master Room event 894: the player tells Lisa he met the
   Resistance; set at its end, tested to start it */
#define FLAG_LISA_RESISTANCE_REPORT_SEEN FLAG(0x1C, 0x39)
/* lift.c / wstag261 Cargo Tower: "There's a switch here! Let's push it."
   sets it, "let's go downstairs" clears it; the lift is raised while set */
#define FLAG_LIFT_RAISED FLAG(0x1C, 0x3D)
/* wstag875 Circuit Board: BK Agumon loses ("What?! I lost!") and says the
   Black Kingz leader has Etemon's Mic; the leader then appears */
#define FLAG_BK_AGUMON_BEATEN FLAG(0x1C, 0x3F)
/* wstag875 Circuit Board: the BKZ Leader loses and hands over Etemon's Mic
   (item 0x18D given) */
#define FLAG_BKZ_LEADER_BEATEN FLAG(0x1C, 0x40)
/* wstag386 Duel Island: Etemon says Black Agumon took his mic; makes BK
   Agumon appear in the Circuit Board */
#define FLAG_ETEMON_MIC_STOLEN_TALKED FLAG(0x1C, 0x42)
/* wstag470 Swamp Inn: Gatomon says Sepikmon of the Shaman House could stop
   Zanbamon but is missing; lets the Shaman House event start */
#define FLAG_SWAMP_INN_SEPIKMON_HINT_TALKED FLAG(0x1C, 0x43)
/* wstag240 Asuka Inn 2F: Guilmon says his cousin has the Blue Card
   (gondola) and went to Seiryu City; a Guilmon then shows at Forest Inn */
#define FLAG_ASUKA_INN_GUILMON_TALKED FLAG(0x1C, 0x44)
/* wstag360 Forest Inn: Guilmon says another Guilmon has the Blue Card and
   went to Seiryu City; Tricky Guilmon then shows at Zephyr Tower */
#define FLAG_FOREST_INN_GUILMON_TALKED FLAG(0x1C, 0x45)
/* wstag420 Seiryu City: a Guilmon says the card is a fake by Trickster
   Guilmon, hiding underground; then he is found in Forest Inn BF */
#define FLAG_FAKE_BLUE_CARD_TALKED FLAG(0x1C, 0x47)
/* wstag386 Duel Island: Etemon gets his mic back ("Let's battle!") and
   starts a card battle; set with it, later he offers rematches */
#define FLAG_DUEL_ISLAND_ETEMON_FOUGHT FLAG(0x1C, 0x4A)
/* wstag375 Protocol Ruins: Baronmon can make the TNT Chip but needs a TNT
   Ball; then he says Triceramon has it */
#define FLAG_BARONMON_TNT_BALL_TALKED FLAG(0x1C, 0x4F)
/* wstag410 East Station: the player tries the fake Blue Card ("this time it
   should work"); afterwards the monitor says he has no Blue Card */
#define FLAG_FAKE_BLUE_CARD_TRIED FLAG(0x1C, 0x50)
/* wstag385 Duel Island: KingDivermon loses ("I lost... I must train
   more..."), gives item 0x12 and resets the five Divermon duelists */
#define FLAG_KING_DIVERMON_BEATEN FLAG(0x1C, 0x53)
/* wstag386 Duel Island: KingEtemon loses and gives the Sun Trophy (item
   0x14); resets the Etemon duelists */
#define FLAG_KING_ETEMON_BEATEN FLAG(0x1C, 0x54)
/* wstag385 Duel Island: after the trophy, KingDivermon's "ultimate folder"
   rematch is won ("You defeated my ultimate folder...") */
#define FLAG_KING_DIVERMON_REMATCH_BEATEN FLAG(0x1C, 0x55)
/* wstag386 Duel Island: KingEtemon loses the rematch ("Why did I lose?!");
   afterwards he won't battle "jinxes like you" */
#define FLAG_KING_ETEMON_REMATCH_BEATEN FLAG(0x1C, 0x56)

/* GAME.flags40: the events seen, set at an event's end and tested to start
   it (or the next one) once */

/* wstag755 event 780: "I won against Genbu Leader too!", he gives a reward;
   set at its end, tested 0 to start it and 1 to start event 781 */
#define FLAG_GENBU_LEADER_WIN_SEEN FLAG(0x40, 1)
/* wstag520 event 260: Suzaku Leader lost and gives the Suzaku Badge; set at
   its end, tested 1 to start event 261 with Kail */
#define FLAG_SUZAKU_LEADER_WIN_SEEN FLAG(0x40, 2)
/* wstag525 event 550: Suzaku Leader shows the security hole behind the
   earthquake; set at its end, tested 1 to start event 551 in wstag620 */
#define FLAG_SECURITY_HOLE_SEEN FLAG(0x40, 3)
/* wstag212 event 271: the DO Guard lets only authorized personnel pass; set
   at its end, tested 0 to start it, 1 to start event 273 */
#define FLAG_DO_GUARD_BLOCK_SEEN FLAG(0x40, 4)
/* wstag205 event 100: the player beats Keith on Asuka Bridge; set at its
   end, tested 0 to start it and 1 to start event 101 with Etemon */
#define FLAG_KEITH_BRIDGE_WIN_SEEN FLAG(0x40, 6)
/* wstag455 event 360: "I got the Digi-Egg of Sincerity!"; set at its end,
   tested 0 to show actor 0 in Bios Swamp */
#define FLAG_SINCERITY_EGG_FOUND FLAG(0x40, 7)
/* wstag325 event 375: Datamon loses and gives the Rusty Gloves; set at its
   end, tested 1 to start event 376 */
#define FLAG_DATAMON_WIN_SEEN FLAG(0x40, 8)
/* wstag325 event 376: Datamon sees the Staff Pass and opens the gate; set
   at its end, tested 0 to start it */
#define FLAG_DATAMON_OPENS_GATE_SEEN FLAG(0x40, 9)
/* wstag537 event 700: "I won against Zhu Que Chief!", the player gets the
   Red ID Pass; set at its end, swaps Suzaku Leader actors 22/25 */
#define FLAG_ZHU_QUE_CHIEF_WIN_SEEN FLAG(0x40, 0xB)
/* wstag200 event 50: after the first battle, Tamer Genji tells the player
   to learn more; set at its end, tested 0 to start it */
#define FLAG_GENJI_FIRST_BATTLE_SEEN FLAG(0x40, 0xD)
/* wstag735 event 790: Ice Witch admits defeat and lets the player go on;
   set at its end, tested 0 to start it and 1 to start event 791 */
#define FLAG_ICE_WITCH_WIN_SEEN FLAG(0x40, 0xE)
/* wstag405 event 60: MasterTyranno loses and gives the Old Claw for Seiryu
   Leader; set at its end, tested 1 to start event 61 */
#define FLAG_MASTERTYRANNO_WIN_SEEN FLAG(0x40, 0xF)
/* wstag405 event 61: the player shows the Old Claw and Seiryu Leader
   accepts the battle; set at its end, tested 0 to start it */
#define FLAG_SEIRYU_LEADER_CHALLENGE_SEEN FLAG(0x40, 0x10)
/* wstag395 event 80: the player meets Nick ("I'm only 21!") in Wind
   Prairie; set at its end, tested 0 to start it */
#define FLAG_NICK_FIRST_MEETING_SEEN FLAG(0x40, 0x11)
/* wstag420 event 70: Seiryu Leader loses and gives the player his badge;
   set at its end, tested 1 to start event 71 (the earthquake) */
#define FLAG_SEIRYU_LEADER_WIN_SEEN FLAG(0x40, 0x12)
/* wstag205 event 101: the player asks Etemon about Sepikmon's mask and he
   runs; set at its end, tested 0 to start it */
#define FLAG_ETEMON_MASK_QUESTION_SEEN FLAG(0x40, 0x16)
/* wstag675 event 390: Byakko citizens say they waited and send the player
   to their leader; set at its end, swaps actors 42/43 */
#define FLAG_BYAKKO_DOME_WELCOME_SEEN FLAG(0x40, 0x17)
/* wstag735 event 791: Fire Knight, bored, challenges the player; set at its
   end (gives the Yin Yang Hat), tested 0 to start it */
#define FLAG_FIRE_KNIGHT_BATTLE_SEEN FLAG(0x40, 0x19)
/* wstag366 event 720: Teddy catches up before Amaterasu City and the player
   gets the Crony ID; set at its end, tested 0 to start it */
#define FLAG_TEDDY_FOREST_INN_SEEN FLAG(0x40, 0x1D)
/* wstag675 event 410: Byakko Leader loses and sends the player to the badge
   room; set at its end, tested 1 to start event 411 */
#define FLAG_BYAKKO_LEADER_WIN_SEEN FLAG(0x40, 0x1E)
/* wstag580 event 450: "OK, I found you!", the player corners Numemon in the
   Dum Dum Factory; set at its end, tested 0 to start it */
#define FLAG_NUMEMON_FACTORY_FOUND_SEEN FLAG(0x40, 0x21)
/* wstag445 event 1265: MetalGreymon loses and gives the Agumon DDNA; set at
   its end, tested 1 to start event 1266 */
#define FLAG_METALGREYMON_WIN_SEEN FLAG(0x40, 0x23)
/* wstag445 event 1266: the player asks WarGrowlmon for the Guilmon DDNA and
   he wants a battle; set at its end, tested 0 to start it */
#define FLAG_WARGROWLMON_DDNA_REQUEST_SEEN FLAG(0x40, 0x24)
/* wstag490 event 1267: WarGrowlmon loses and gives the Guilmon DDNA; set at
   its end, tested 1 to start event 1268 */
#define FLAG_WARGROWLMON_WIN_SEEN FLAG(0x40, 0x25)
/* wstag490 event 1268: the player asks GrapLeomon for the Kumamon DDNA and
   he wants a battle; set at its end, tested 0 to start it */
#define FLAG_GRAPLEOMON_DDNA_REQUEST_SEEN FLAG(0x40, 0x26)
/* wstag550 event 1269: MagnaAngemon loses and gives the Patamon DDNA; set
   at its end, tested 1 to start event 1270 */
#define FLAG_MAGNAANGEMON_WIN_SEEN FLAG(0x40, 0x27)
/* wstag550 event 1270: the player asks Taomon for the Renamon DDNA and she
   wants a battle; set at its end, tested 0 to start it */
#define FLAG_TAOMON_DDNA_REQUEST_SEEN FLAG(0x40, 0x28)
/* wstag565 event 1271: Taomon loses and gives the Renamon DDNA; set at its
   end, tested 1 to start event 1272 */
#define FLAG_TAOMON_WIN_SEEN FLAG(0x40, 0x29)
/* wstag565 event 1272: the player asks Kyukimon for the Kotemon DDNA and he
   wants a battle; set at its end, tested 0 to start it */
#define FLAG_KYUKIMON_DDNA_REQUEST_SEEN FLAG(0x40, 0x2A)
/* wstag525 event 1273: Kyukimon loses and gives the Kotemon DDNA; set at
   its end, tested 1 to start event 1274 */
#define FLAG_KYUKIMON_WIN_SEEN FLAG(0x40, 0x2B)
/* wstag525 event 1274: BK Seraphimon says the player must fight him; set at
   its end, tested 0 to start it */
#define FLAG_BK_SERAPHIMON_CHALLENGE_SEEN FLAG(0x40, 0x2C)
/* wstag385 event 1275: Armormon loses and gives the Monmon DDNA; set at its
   end, tested 1 to start event 1276 */
#define FLAG_ARMORMON_WIN_SEEN FLAG(0x40, 0x2D)
/* wstag385 event 1276: the player accepts BK WarGreymon's battle; set at
   its end, tested 0 to start it */
#define FLAG_BK_WARGREYMON_CHALLENGE_SEEN FLAG(0x40, 0x2E)
/* wstag490 event 1277: GrapLeomon loses and gives the Kumamon DDNA; set at
   its end, tested 1 to start event 1278 */
#define FLAG_GRAPLEOMON_WIN_SEEN FLAG(0x40, 0x2F)
/* wstag490 event 1278: the player asks Paildramon for the Veemon DDNA and
   he wants a battle; set at its end, tested 0 to start it */
#define FLAG_PAILDRAMON_DDNA_REQUEST_SEEN FLAG(0x40, 0x30)
/* wstag450 event 1279: Paildramon loses and gives the Veemon DDNA; set at
   its end, tested 1 to start event 1280 */
#define FLAG_PAILDRAMON_WIN_SEEN FLAG(0x40, 0x31)
/* wstag450 event 1280: the player accepts BK Imperialdramon's battle; set
   at its end, tested 0 to start it */
#define FLAG_BK_IMPERIALDRAMON_CHALLENGE_SEEN FLAG(0x40, 0x32)
/* wstag580 event 520: the player finds Nick and Keith arguing in the Dum
   Dum Factory; set at its end, tested 0 to start it */
#define FLAG_NICK_KEITH_FACTORY_SEEN FLAG(0x40, 0x38)
/* wstag620 event 540: Lisa sets Nick and Keith to look for a pass code in
   the computer; set at its end, tested 0 to start it */
#define FLAG_PASS_CODE_SEARCH_SEEN FLAG(0x40, 0x3A)
/* wstag580 event 440: "Numemon isn't here.", in the Dum Dum Factory; set at
   its end, tested 0 to start it */
#define FLAG_NUMEMON_MISSING_SEEN FLAG(0x40, 0x3C)
/* wstag655 event 430: Byakko Leader apologizes for mistaking the player for
   the A.o.A; set at its end, tested 1 to start event 431 */
#define FLAG_BYAKKO_LEADER_APOLOGY_SEEN FLAG(0x40, 0x3E)
/* wstag740 event 800: "Man, I lost!", Fire Knight warns of the Dark Dungeon
   ahead; set at its end, tested 0 to start it */
#define FLAG_FIRE_KNIGHT_WIN_SEEN FLAG(0x40, 0x3F)
/* wstag740 event 801: Dark Knight, the Dark Dungeon's strongest boss,
   blocks the player; set at its end (gives the Divine Rod), tested 0 to
   start it */
#define FLAG_DARK_KNIGHT_CHALLENGE_SEEN FLAG(0x40, 0x40)
/* wstag745 event 810: Dark Knight, beaten, says the player will make a
   great tamer; set at its end, tested 1 to start event 811 */
#define FLAG_DARK_KNIGHT_WIN_SEEN FLAG(0x40, 0x41)
/* wstag745 event 811: the player asks Genbu Leader for his badge and he
   won't give it for free; set at its end, tested 0 to start it */
#define FLAG_GENBU_LEADER_CHALLENGE_SEEN FLAG(0x40, 0x42)
/* wstag795 event 830: the player pushes a button on a control panel in
   Magasta B1F; set at its end, tested there and in wstag800 */
#define FLAG_MAGASTA_BUTTON_PRESSED FLAG(0x40, 0x43)
/* wstag800 event 870: the player wins and finds the Dramon Guard in Magasta
   B2F; set at its end, tested 1 to start event 871 */
#define FLAG_MECH_SOLDIER_WIN_SEEN FLAG(0x40, 0x44)
/* wstag800 event 871: the player tells the Royal Guard to stop the launch;
   set at its end, tested 0 to start it */
#define FLAG_ROYAL_GUARD_CHALLENGE_SEEN FLAG(0x40, 0x45)
/* wstag805 event 880: the player wins but the field is gone and the
   Juggernaut launches; set at its end, tested in wstag750/805 */
#define FLAG_JUGGERNAUT_LAUNCH_SEEN FLAG(0x40, 0x46)
/* wstag750 event 883: "...they took the Juggernaut...", in the Chamber
   Room; set at its end, tested 0 to start it */
#define FLAG_JUGGERNAUT_TAKEN_SEEN FLAG(0x40, 0x47)
/* wstag750 event 860: the realize transfer limit is reached and the player
   is forced back to digital; set at its end, tested in wstag750/805 */
#define FLAG_FORCED_DIGITIZATION_SEEN FLAG(0x40, 0x48)
/* wstag300 event 570: "GUBIIIII!", a Digimon the player has never seen
   appears in Admin Center 2F; set at its end, tested 0 to start it */
#define FLAG_STRANGE_DIGIMON_SEEN FLAG(0x40, 0x4A)
/* wstag300 event 572: the player spots the Game Master and three guards
   block the way; set at its end, tested 0 to start it */
#define FLAG_GAME_MASTER_GUARDS_SEEN FLAG(0x40, 0x4C)
/* wstag310 event 680: the fusion experiment succeeds and the A.o.A commence
   Operation Sigma; set at its end, tested to start events there */
#define FLAG_OPERATION_SIGMA_SEEN FLAG(0x40, 0x4E)
/* wstag310 event 681: the Game Master's Persiamon loses and Lisa, Teddy and
   Nick arrive to arrest her; set at its end */
#define FLAG_GAME_MASTER_WIN_SEEN FLAG(0x40, 0x4F)
/* wstag545 event 710: the player asks Zhu Que Chief where the Digi-Egg of
   Knowledge is; set at its end, tested to start it */
#define FLAG_ZHU_QUE_CHIEF_CHALLENGE_SEEN FLAG(0x40, 0x51)
/* wstag521 event 750: "I got the Digi-Egg of Knowledge!"; set at its end,
   tested 0 to show Zhu Que Chief (actor 16) */
#define FLAG_KNOWLEDGE_EGG_FOUND FLAG(0x40, 0x52)
/* wstag375 event 1260: Pharaohmon loses and gives the Old Wand; set at its
   end, tested 1 to start event 1261 */
#define FLAG_PHARAOHMON_WIN_SEEN FLAG(0x40, 0x53)
/* wstag535 event 1262: Zanbamon loses and gives the Rusty Katana; set at
   its end, tested 1 to start event 1263 */
#define FLAG_ZANBAMON_WIN_SEEN FLAG(0x40, 0x55)
/* wstag535 event 1263: the player asks MagnaAngemon for the Patamon DDNA
   and he wants a battle; set at its end, tested 0 to start it */
#define FLAG_MAGNAANGEMON_DDNA_REQUEST_SEEN FLAG(0x40, 0x56)
/* wstag305 event 890: Lisa and Nick plan how to get into Amaterasu City
   past the Knightmon Guard System; set at its end */
#define FLAG_AMATERASU_PLAN_SEEN FLAG(0x40, 0x57)
/* wstag295 event 891: the Game Master reveals Destromon, born from Vemmon
   and the Juggernaut; set at its end, tested to start it */
#define FLAG_DESTROMON_REVEAL_SEEN FLAG(0x40, 0x58)
/* wstag676 event 900: the player wins and gets the White ID Pass; set at
   its end, tested 11 times in Bai Hu Dome (troopers' talks) */
#define FLAG_BAI_HU_CHIEF_WIN_SEEN FLAG(0x40, 0x5A)
/* wstag756 event 910: "I won against Xuen Wu Chief!" and the Black ID Pass;
   set at its end, tested 0 to show Xuen Wu Chief */
#define FLAG_XUEN_WU_CHIEF_WIN_SEEN FLAG(0x40, 0x5B)
/* wstag331 event 920: the player finds Central Park empty and guesses the
   secret door's code; set at its end, tested 0 to start it */
#define FLAG_CENTRAL_PARK_SECRET_DOOR_SEEN FLAG(0x40, 0x5C)
/* wstag311 event 931: the MAGAMI President asks to be called Chief Officer;
   set at its end, tested 0 to start it */
#define FLAG_CHIEF_OFFICER_MEETING_SEEN FLAG(0x40, 0x5E)
/* wstag311 event 934: looking for the Matrix System, the player finds
   Vemmon there; set at its end, tested 1 in the Login Room (wstag226) */
#define FLAG_VEMMON_AT_HQ_SEEN FLAG(0x40, 0x60)
/* wstag800 event 850: a Mech Soldier sounds the intruder alert at the
   Juggernaut launch; set at its end, tested 0 to start it */
#define FLAG_MECH_SOLDIER_ALERT_SEEN FLAG(0x40, 0x61)
/* wstag311 event 932: the Chief Officer turns himself in and Nick arrests
   him; set at its end, tested 0 to start it */
#define FLAG_CHIEF_OFFICER_ARREST_SEEN FLAG(0x40, 0x67)
/* wstag311 event 981: the real goal was Gunslinger, the Digitize Wave will
   launch from Ragnarok; set at its end, tested 0 to start it */
#define FLAG_DIGITIZE_WAVE_PLAN_SEEN FLAG(0x40, 0x6C)
/* wstag810 event 1010: a Metal Soldier sounds the intruder alert in
   Gunslinger 1F; set at its end, tested 0 to start it */
#define FLAG_GUNSLINGER_1F_SOLDIER_SEEN FLAG(0x40, 0x6F)
/* wstag815 event 1020: a Metal Soldier sounds the intruder alert in
   Gunslinger 2F; set at its end, tested 0 to start it */
#define FLAG_GUNSLINGER_2F_SOLDIER_SEEN FLAG(0x40, 0x70)
/* wstag815 event 1030: Lord Megadeath taunts the player from beyond the
   Warp Gate; set at its end, tested 0 to start it */
#define FLAG_MEGADEATH_TAUNT_SEEN FLAG(0x40, 0x71)
/* wstag815 event 1050: Lord Megadeath, a life form born in the network,
   meets the player; set at its end, tested 0 to start it */
#define FLAG_MEGADEATH_MEETING_SEEN FLAG(0x40, 0x73)
/* wstag820 event 1060: beaten, Lord Megadeath calls it a test and brings
   out Snatchmon; set at its end, tested to start events there */
#define FLAG_MEGADEATH_WIN_SEEN FLAG(0x40, 0x74)
/* wstag820 event 1070: Snatchmon appears and questions Lord Megadeath's
   orders; set at its end, tested 0 to start it */
#define FLAG_SNATCHMON_APPEARS_SEEN FLAG(0x40, 0x75)
/* wstag326 event 1281: BK WarGreymon loses and gives the Platinum ID; set
   at its end, tested 1 to start event 1282 */
#define FLAG_BK_WARGREYMON_WIN_SEEN FLAG(0x40, 0x76)
/* wstag326 event 1282: the player accepts the battle of BK MegaGargomon,
   bored since no one comes; set at its end, tested 0 to start it */
#define FLAG_BK_MEGAGARGOMON_CHALLENGE_SEEN FLAG(0x40, 0x77)
/* wstag376 event 1283: BK MegaGargomon loses and gives the Wild Helmet; set
   at its end, tested 1 to start event 1284 */
#define FLAG_BK_MEGAGARGOMON_WIN_SEEN FLAG(0x40, 0x78)
/* wstag406 event 1285: BK Imperialdramon loses and gives the player a
   reward; set at its end, tested 1 to start event 1286 */
#define FLAG_BK_IMPERIALDRAMON_WIN_SEEN FLAG(0x40, 0x7A)
/* wstag538 event 1287: BK Seraphimon says the player has passed his test of
   courage; set at its end, tested 1 to start event 1288 */
#define FLAG_BK_SERAPHIMON_WIN_SEEN FLAG(0x40, 0x7C)
/* wstag606 event 1289: BK WarGrowlmon loses and gives the Hazard Armor; set
   at its end, tested 1 to start event 1290 */
#define FLAG_BK_WARGROWLMON_WIN_SEEN FLAG(0x40, 0x7E)
/* wstag606 event 1290: BK KingNumemon claims to be far superior to other
   Numemon; set at its end, tested 0 to start it */
#define FLAG_BK_KINGNUMEMON_CHALLENGE_SEEN FLAG(0x40, 0x7F)
/* wstag616 event 1291: BK KingNumemon loses and gives the player a reward;
   set at its end, tested 1 to start event 1292 */
#define FLAG_BK_KINGNUMEMON_WIN_SEEN FLAG(0x40, 0x80)
/* wstag741 event 1295: Fire Master loses and gives the Mind Chip; set at
   its end, tested 0 to start it */
#define FLAG_FIRE_MASTER_WIN_SEEN FLAG(0x40, 0x84)
/* wstag741 event 1296: the player challenges Dark Master; set at its end
   (gives the Mind Chip), tested 0 to show Fire Master */
#define FLAG_DARK_MASTER_CHALLENGE_SEEN FLAG(0x40, 0x85)
/* wstag746 event 1297: Dark Master loses and gives the EXP Adaptor; set at
   its end, tested 0 to start it */
#define FLAG_DARK_MASTER_WIN_SEEN FLAG(0x40, 0x86)
/* wstag575 event 422: the player finds Numemon in Bullet Valley, who has
   nothing to tell; set at its end, tested 0 to start it */
#define FLAG_NUMEMON_BULLET_VALLEY_SEEN FLAG(0x40, 0xA2)
/* wstag421 event 740: "Yeah, I beat Qing Long Chief!"; set at its end,
   tested 0 to show Qing Long Chief (actor 21) */
#define FLAG_QING_LONG_CHIEF_WIN_SEEN FLAG(0x40, 0xA3)
/* wstag605 event 510: HiAndromon lets the player pass, unlocks the Secret
   Stairs and gives the Rusty Rifle; set at its end */
#define FLAG_HIANDROMON_WIN_SEEN FLAG(0x40, 0xA6)
/* wstag740 event 9000: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9000_SPRUNG FLAG(0x40, 0xAA)
/* wstag740 event 9001: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9001_SPRUNG FLAG(0x40, 0xAB)
/* wstag740 event 9002: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9002_SPRUNG FLAG(0x40, 0xAC)
/* wstag740 event 9003: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9003_SPRUNG FLAG(0x40, 0xAD)
/* wstag740 event 9004: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9004_SPRUNG FLAG(0x40, 0xAE)
/* wstag740 event 9005: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9005_SPRUNG FLAG(0x40, 0xAF)
/* wstag740 event 9006: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9006_SPRUNG FLAG(0x40, 0xB0)
/* wstag740 event 9007: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9007_SPRUNG FLAG(0x40, 0xB1)
/* wstag740 event 9008: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9008_SPRUNG FLAG(0x40, 0xB2)
/* wstag740 event 9009: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9009_SPRUNG FLAG(0x40, 0xB3)
/* wstag740 event 9010: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9010_SPRUNG FLAG(0x40, 0xB4)
/* wstag740 event 9011: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9011_SPRUNG FLAG(0x40, 0xB5)
/* wstag740 event 9012: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9012_SPRUNG FLAG(0x40, 0xB6)
/* wstag740 event 9013: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9013_SPRUNG FLAG(0x40, 0xB7)
/* wstag740 event 9014: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9014_SPRUNG FLAG(0x40, 0xB8)
/* wstag740 event 9015: a Fire Dungeon trap (Asuka server) leaves the party
   at 1 HP; set at its end, tested 0 to start it */
#define FLAG_ASUKA_FIRE_TRAP_9015_SPRUNG FLAG(0x40, 0xB9)
/* wstag741 event 9000: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9000_SPRUNG FLAG(0x40, 0xBA)
/* wstag741 event 9001: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9001_SPRUNG FLAG(0x40, 0xBB)
/* wstag741 event 9002: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9002_SPRUNG FLAG(0x40, 0xBC)
/* wstag741 event 9003: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9003_SPRUNG FLAG(0x40, 0xBD)
/* wstag741 event 9004: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9004_SPRUNG FLAG(0x40, 0xBE)
/* wstag741 event 9005: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9005_SPRUNG FLAG(0x40, 0xBF)
/* wstag741 event 9006: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9006_SPRUNG FLAG(0x40, 0xC0)
/* wstag741 event 9007: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9007_SPRUNG FLAG(0x40, 0xC1)
/* wstag741 event 9008: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9008_SPRUNG FLAG(0x40, 0xC2)
/* wstag741 event 9009: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9009_SPRUNG FLAG(0x40, 0xC3)
/* wstag741 event 9010: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9010_SPRUNG FLAG(0x40, 0xC4)
/* wstag741 event 9011: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9011_SPRUNG FLAG(0x40, 0xC5)
/* wstag741 event 9012: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9012_SPRUNG FLAG(0x40, 0xC6)
/* wstag741 event 9013: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9013_SPRUNG FLAG(0x40, 0xC7)
/* wstag741 event 9014: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9014_SPRUNG FLAG(0x40, 0xC8)
/* wstag741 event 9015: a Fire Dungeon trap (Amaterasu server) leaves the
   party at 1 HP; set at its end, tested 0 to start it */
#define FLAG_AMATERASU_FIRE_TRAP_9015_SPRUNG FLAG(0x40, 0xC9)

/*
 * The SPECIAL conditions (SPECIAL(id), checkSpecialCondition), named after
 * what the check function of their SPECIAL_CONDITIONS entry tests with its
 * argument (src/engine/game/events.c). A condition list tests one against 1
 * or 0; an action list runs it, and the ones that give or take something
 * are only actions.
 */

/* checkItemSet: whether the player has a set of items */

/* the player has a Red Snapper, a Spider Web and a Bamboo Spear (items 7, 0x59
   and 0xA7, checkItemSet 0): what Tai Kong Wong asks for to make the Fishing
   Pole (wstag340) */
#define SPECIAL_HAS_FISHING_POLE_PARTS SPECIAL(0x3A)
/* the European and Japanese versions: the player has the Muramasa, Super Nova,
   Punishment, Eternally and Invincible (items 0x69, 0x77, 0x83, 0x90 and 0x9C,
   checkItemSet 1), the "5 strongest Epic Items" the extra chapter's leaders
   ask for (wstag949) */
#define SPECIAL_HAS_FIVE_EPIC_ITEMS SPECIAL(0x96)

/* checkPartner: the starter pack, the partners and the party; partner i
   is DIGNAM's string i + 1 (Kotemon, Kumamon, Monmon, Agumon, Veemon,
   Guilmon, Renamon, Patamon) */

/* the player chose the Balanced Pack at registration (GAME.partySet 0,
   STARTER_PARTIES[0]; NAMEET's string 10) */
#define SPECIAL_BALANCED_PACK_CHOSEN SPECIAL(0)
/* the player chose the Powerful Pack at registration (GAME.partySet 1,
   STARTER_PARTIES[1]; NAMEET's string 11) */
#define SPECIAL_POWERFUL_PACK_CHOSEN SPECIAL(1)
/* the player chose the Maniac Pack at registration (GAME.partySet 2,
   STARTER_PARTIES[2]; NAMEET's string 12) */
#define SPECIAL_MANIAC_PACK_CHOSEN SPECIAL(2)
/* Kotemon (partner 0) is unlocked */
#define SPECIAL_KOTEMON_UNLOCKED SPECIAL(0x10)
/* Kumamon (partner 1) is unlocked */
#define SPECIAL_KUMAMON_UNLOCKED SPECIAL(0x12)
/* Monmon (partner 2) is unlocked */
#define SPECIAL_MONMON_UNLOCKED SPECIAL(0x11)
/* Agumon (partner 3) is unlocked */
#define SPECIAL_AGUMON_UNLOCKED SPECIAL(0xB)
/* Veemon (partner 4) is unlocked */
#define SPECIAL_VEEMON_UNLOCKED SPECIAL(0xD)
/* Guilmon (partner 5) is unlocked */
#define SPECIAL_GUILMON_UNLOCKED SPECIAL(0xC)
/* Renamon (partner 6) is unlocked */
#define SPECIAL_RENAMON_UNLOCKED SPECIAL(0xF)
/* Patamon (partner 7) is unlocked */
#define SPECIAL_PATAMON_UNLOCKED SPECIAL(0xE)
/* Kotemon (partner 0) is in the party */
#define SPECIAL_KOTEMON_IN_PARTY SPECIAL(0x42)
/* Kumamon (partner 1) is in the party */
#define SPECIAL_KUMAMON_IN_PARTY SPECIAL(0x44)
/* Monmon (partner 2) is in the party */
#define SPECIAL_MONMON_IN_PARTY SPECIAL(0x43)
/* Agumon (partner 3) is in the party */
#define SPECIAL_AGUMON_IN_PARTY SPECIAL(0x47)
/* Veemon (partner 4) is in the party */
#define SPECIAL_VEEMON_IN_PARTY SPECIAL(0x46)
/* Guilmon (partner 5) is in the party */
#define SPECIAL_GUILMON_IN_PARTY SPECIAL(0x45)
/* Renamon (partner 6) is in the party */
#define SPECIAL_RENAMON_IN_PARTY SPECIAL(0x49)
/* Patamon (partner 7) is in the party */
#define SPECIAL_PATAMON_IN_PARTY SPECIAL(0x48)
/* an action: unlocks Kotemon (partner 0); the talks that take or give its DDNA
   apply it */
#define SPECIAL_UNLOCK_KOTEMON SPECIAL(0x37)
/* an action: unlocks Kumamon (partner 1); the talks that take or give its DDNA
   apply it */
#define SPECIAL_UNLOCK_KUMAMON SPECIAL(0x39)
/* an action: unlocks Monmon (partner 2); the talks that take or give its DDNA
   apply it */
#define SPECIAL_UNLOCK_MONMON SPECIAL(0x38)
/* an action: unlocks Agumon (partner 3); the talks that take or give its DDNA
   apply it */
#define SPECIAL_UNLOCK_AGUMON SPECIAL(0x31)
/* an action: unlocks Veemon (partner 4); the talks that take or give its DDNA
   apply it */
#define SPECIAL_UNLOCK_VEEMON SPECIAL(0x32)
/* an action: unlocks Guilmon (partner 5); the talks that take or give its DDNA
   apply it */
#define SPECIAL_UNLOCK_GUILMON SPECIAL(0x33)
/* an action: unlocks Renamon (partner 6); the talks that take or give its DDNA
   apply it */
#define SPECIAL_UNLOCK_RENAMON SPECIAL(0x35)
/* an action: unlocks Patamon (partner 7); the talks that take or give its DDNA
   apply it */
#define SPECIAL_UNLOCK_PATAMON SPECIAL(0x34)
/* Kotemon (partner 0) is unlocked and at level 45 or more */
#define SPECIAL_KOTEMON_LEVEL_45 SPECIAL(0x4A)
/* Kumamon (partner 1) is unlocked and at level 45 or more */
#define SPECIAL_KUMAMON_LEVEL_45 SPECIAL(0x4C)
/* Monmon (partner 2) is unlocked and at level 45 or more */
#define SPECIAL_MONMON_LEVEL_45 SPECIAL(0x4B)
/* Agumon (partner 3) is unlocked and at level 45 or more */
#define SPECIAL_AGUMON_LEVEL_45 SPECIAL(0x4F)
/* Veemon (partner 4) is unlocked and at level 45 or more */
#define SPECIAL_VEEMON_LEVEL_45 SPECIAL(0x4E)
/* Guilmon (partner 5) is unlocked and at level 45 or more */
#define SPECIAL_GUILMON_LEVEL_45 SPECIAL(0x4D)
/* Renamon (partner 6) is unlocked and at level 45 or more */
#define SPECIAL_RENAMON_LEVEL_45 SPECIAL(0x51)
/* Patamon (partner 7) is unlocked and at level 45 or more */
#define SPECIAL_PATAMON_LEVEL_45 SPECIAL(0x50)
/* the party's levels add up to 30 or more (0 * 15 + 30) */
#define SPECIAL_PARTY_LEVEL_TOTAL_30 SPECIAL(0x25)
/* the party's levels add up to 45 or more (1 * 15 + 30) */
#define SPECIAL_PARTY_LEVEL_TOTAL_45 SPECIAL(0x26)
/* the party's levels add up to 60 or more (2 * 15 + 30) */
#define SPECIAL_PARTY_LEVEL_TOTAL_60 SPECIAL(0x27)
/* the party's levels add up to 75 or more (3 * 15 + 30) */
#define SPECIAL_PARTY_LEVEL_TOTAL_75 SPECIAL(0x28)
/* the party's levels add up to 90 or more (4 * 15 + 30) */
#define SPECIAL_PARTY_LEVEL_TOTAL_90 SPECIAL(0x29)
/* Kotemon (partner 0) is still locked */
#define SPECIAL_KOTEMON_LOCKED SPECIAL(0x2E)
/* Kumamon (partner 1) is still locked */
#define SPECIAL_KUMAMON_LOCKED SPECIAL(0x30)
/* Monmon (partner 2) is still locked */
#define SPECIAL_MONMON_LOCKED SPECIAL(0x2F)
/* Agumon (partner 3) is still locked */
#define SPECIAL_AGUMON_LOCKED SPECIAL(0x2A)
/* Veemon (partner 4) is still locked */
#define SPECIAL_VEEMON_LOCKED SPECIAL(0x2B)
/* Guilmon (partner 5) is still locked */
#define SPECIAL_GUILMON_LOCKED SPECIAL(0x2C)
/* Renamon (partner 6) is still locked */
#define SPECIAL_RENAMON_LOCKED SPECIAL(0x36)
/* Patamon (partner 7) is still locked */
#define SPECIAL_PATAMON_LOCKED SPECIAL(0x2D)
/* the European and Japanese versions: every unlocked partner is at level 45 or
   more */
#define SPECIAL_ALL_PARTNERS_LEVEL_45 SPECIAL(0x95)
/* the European and Japanese versions, an action: restores the party's HP and
   MP */
#define SPECIAL_HEAL_PARTY SPECIAL(0x53)
/* the European and Japanese versions: all eight partners are unlocked */
#define SPECIAL_ALL_PARTNERS_UNLOCKED SPECIAL(0x55)

/* checkMoney: whether the player has an amount, or gives or takes one */

/* the player has 800 BIT or more (MONEY_REQUIRED[0]) */
#define SPECIAL_HAS_800_BIT SPECIAL(0x74)
/* the player has 1600 BIT or more (MONEY_REQUIRED[1]) */
#define SPECIAL_HAS_1600_BIT SPECIAL(0x75)
/* the player has 2700 BIT or more (MONEY_REQUIRED[2]) */
#define SPECIAL_HAS_2700_BIT SPECIAL(0x76)
/* the player has 4000 BIT or more (MONEY_REQUIRED[3]) */
#define SPECIAL_HAS_4000_BIT SPECIAL(0x77)
/* the player has 6000 BIT or more (MONEY_REQUIRED[4]) */
#define SPECIAL_HAS_6000_BIT SPECIAL(0x78)
/* the player has 8700 BIT or more (MONEY_REQUIRED[5]) */
#define SPECIAL_HAS_8700_BIT SPECIAL(0x79)
/* the player has 11500 BIT or more (MONEY_REQUIRED[6]) */
#define SPECIAL_HAS_11500_BIT SPECIAL(0x7A)
/* the player has 17500 BIT or more (MONEY_REQUIRED[7]) */
#define SPECIAL_HAS_17500_BIT SPECIAL(0x7B)
/* the player has 24000 BIT or more (MONEY_REQUIRED[8]) */
#define SPECIAL_HAS_24000_BIT SPECIAL(0x7C)
/* the player has 32000 BIT or more (MONEY_REQUIRED[9]) */
#define SPECIAL_HAS_32000_BIT SPECIAL(0x7D)
/* an action: gives the player 100 BIT (MONEY_GAINS[0]) */
#define SPECIAL_GAIN_100_BIT SPECIAL(0x8B)
/* an action: gives the player 300 BIT (MONEY_GAINS[1]) */
#define SPECIAL_GAIN_300_BIT SPECIAL(0x8C)
/* an action: gives the player 600 BIT (MONEY_GAINS[2]) */
#define SPECIAL_GAIN_600_BIT SPECIAL(0x8D)
/* an action: gives the player 1000 BIT (MONEY_GAINS[3]) */
#define SPECIAL_GAIN_1000_BIT SPECIAL(0x8E)
/* an action: gives the player 1600 BIT (MONEY_GAINS[4]) */
#define SPECIAL_GAIN_1600_BIT SPECIAL(0x8F)
/* an action: gives the player 3000 BIT (MONEY_GAINS[5]) */
#define SPECIAL_GAIN_3000_BIT SPECIAL(0x90)
/* an action: gives the player 5000 BIT (MONEY_GAINS[6]) */
#define SPECIAL_GAIN_5000_BIT SPECIAL(0x91)
/* an action: gives the player 8500 BIT (MONEY_GAINS[7]) */
#define SPECIAL_GAIN_8500_BIT SPECIAL(0x92)
/* an action: takes 800 BIT (MONEY_LOSSES[0]) */
#define SPECIAL_LOSE_800_BIT SPECIAL(0x7E)
/* an action: takes 1600 BIT (MONEY_LOSSES[1]) */
#define SPECIAL_LOSE_1600_BIT SPECIAL(0x7F)
/* an action: takes 2700 BIT (MONEY_LOSSES[2]) */
#define SPECIAL_LOSE_2700_BIT SPECIAL(0x80)
/* an action: takes 4000 BIT (MONEY_LOSSES[3]) */
#define SPECIAL_LOSE_4000_BIT SPECIAL(0x81)
/* an action: takes 6000 BIT (MONEY_LOSSES[4]) */
#define SPECIAL_LOSE_6000_BIT SPECIAL(0x82)
/* an action: takes 8700 BIT (MONEY_LOSSES[5]) */
#define SPECIAL_LOSE_8700_BIT SPECIAL(0x83)
/* an action: takes 11500 BIT (MONEY_LOSSES[6]) */
#define SPECIAL_LOSE_11500_BIT SPECIAL(0x84)
/* an action: takes 17500 BIT (MONEY_LOSSES[7]) */
#define SPECIAL_LOSE_17500_BIT SPECIAL(0x85)
/* an action: takes 24000 BIT (MONEY_LOSSES[8]) */
#define SPECIAL_LOSE_24000_BIT SPECIAL(0x86)
/* an action: takes 32000 BIT (MONEY_LOSSES[9]) */
#define SPECIAL_LOSE_32000_BIT SPECIAL(0x87)

/* checkProgressRange: whether GAME.progress is within a range of
   PROGRESS_RANGES */

/* GAME.progress is from STORY_LOGGED_IN to STORY_LISA_SAVED
   (PROGRESS_RANGES[0]) */
#define SPECIAL_STORY_LOGGED_IN_TO_LISA_SAVED SPECIAL(6)
/* GAME.progress is from STORY_GENJI_BEATEN to STORY_GAME_MASTER_CAUGHT
   (PROGRESS_RANGES[1]) */
#define SPECIAL_STORY_GENJI_BEATEN_TO_GAME_MASTER_CAUGHT SPECIAL(3)
/* GAME.progress is from STORY_GENJI_BEATEN to 0x2C (PROGRESS_RANGES[2]);
   nothing sets 0x2C, so to STORY_MOVIE_BATTLES */
#define SPECIAL_STORY_GENJI_BEATEN_TO_MOVIE_BATTLES SPECIAL(0xA)
/* GAME.progress is from STORY_BYAKKO_LEADER_FOUGHT to STORY_GAME_MASTER_CAUGHT
   (PROGRESS_RANGES[3]) */
#define SPECIAL_STORY_BYAKKO_LEADER_FOUGHT_TO_GAME_MASTER_CAUGHT SPECIAL(7)
/* GAME.progress is from STORY_KNIGHTMON_REPROGRAMMED to STORY_AMATERASU_BRIDGE
   (PROGRESS_RANGES[4]) */
#define SPECIAL_STORY_KNIGHTMON_REPROGRAMMED_TO_AMATERASU_BRIDGE SPECIAL(4)
/* GAME.progress is from STORY_ASUKA_HEADQUARTERS to 0x2A (PROGRESS_RANGES[5]);
   nothing sets 0x2A, so to STORY_GUNSLINGER */
#define SPECIAL_STORY_ASUKA_HEADQUARTERS_TO_GUNSLINGER SPECIAL(5)
/* GAME.progress is STORY_GENJI_BEATEN or later (PROGRESS_RANGES[6], to 0x63)
   */
#define SPECIAL_STORY_SINCE_GENJI_BEATEN SPECIAL(9)
/* GAME.progress is STORY_SOUTH_STATION_GHOST or later (PROGRESS_RANGES[7], to
   0x63) */
#define SPECIAL_STORY_SINCE_SOUTH_STATION_GHOST SPECIAL(0x14)
/* GAME.progress is STORY_KNIGHTMON_REPROGRAMMED or later (PROGRESS_RANGES[8],
   to 0x63) */
#define SPECIAL_STORY_SINCE_KNIGHTMON_REPROGRAMMED SPECIAL(8)
/* GAME.progress is from STORY_CONTROL_ROOM to 0x2A (PROGRESS_RANGES[9]);
   nothing sets 0x2A, so to STORY_GUNSLINGER */
#define SPECIAL_STORY_CONTROL_ROOM_TO_GUNSLINGER SPECIAL(0x3F)
/* GAME.progress is STORY_LISA_SAVED or later (PROGRESS_RANGES[0xA], to 0x63)
   */
#define SPECIAL_STORY_SINCE_LISA_SAVED SPECIAL(0x40)
/* GAME.progress is STORY_BYAKKO_LEADER_FOUGHT or later (PROGRESS_RANGES[0xB],
   to 0x63) */
#define SPECIAL_STORY_SINCE_BYAKKO_LEADER_FOUGHT SPECIAL(0x41)
/* GAME.progress is STORY_DE_SINCERITY or later (PROGRESS_RANGES[0xC], to 0x63)
   */
#define SPECIAL_STORY_SINCE_DE_SINCERITY SPECIAL(0x93)
/* GAME.progress is STORY_DE_KNOWLEDGE or later (PROGRESS_RANGES[0xD], to 0x63)
   */
#define SPECIAL_STORY_SINCE_DE_KNOWLEDGE SPECIAL(0x94)
/* GAME.progress is from STORY_SEIRYU_BADGE to STORY_ZANBAMON_DRIVEN_OFF
   (PROGRESS_RANGES[0xE]) */
#define SPECIAL_STORY_SEIRYU_BADGE_TO_ZANBAMON_DRIVEN_OFF SPECIAL(0x15)
/* GAME.progress is from STORY_DE_SINCERITY to STORY_LISA_SAVED
   (PROGRESS_RANGES[0xF]) */
#define SPECIAL_STORY_DE_SINCERITY_TO_LISA_SAVED SPECIAL(0x16)
/* GAME.progress is from STORY_BYAKKO_LEADER_FOUGHT to STORY_CONTROL_ROOM
   (PROGRESS_RANGES[0x10]) */
#define SPECIAL_STORY_BYAKKO_LEADER_FOUGHT_TO_CONTROL_ROOM SPECIAL(0x17)
/* GAME.progress is from STORY_KNIGHTMON_REPROGRAMMED to STORY_BULBMON_FOUND
   (PROGRESS_RANGES[0x11]) */
#define SPECIAL_STORY_KNIGHTMON_REPROGRAMMED_TO_BULBMON_FOUND SPECIAL(0x18)
/* GAME.progress is from STORY_JUNGLE_SOUND to STORY_AMATERASU_BRIDGE
   (PROGRESS_RANGES[0x12]) */
#define SPECIAL_STORY_JUNGLE_SOUND_TO_AMATERASU_BRIDGE SPECIAL(0x19)
/* GAME.progress is from STORY_ASUKA_HEADQUARTERS to STORY_OPERATION_SIGMA
   (PROGRESS_RANGES[0x13]) */
#define SPECIAL_STORY_ASUKA_HEADQUARTERS_TO_OPERATION_SIGMA SPECIAL(0x1A)
/* GAME.progress is from STORY_AMATERASU_BRIDGE to STORY_PRESIDENT_ARRESTED
   (PROGRESS_RANGES[0x14]) */
#define SPECIAL_STORY_AMATERASU_BRIDGE_TO_PRESIDENT_ARRESTED SPECIAL(0x1C)
/* GAME.progress is from STORY_JUNGLE_SOUND to STORY_BLACK_ID_PASS
   (PROGRESS_RANGES[0x15]) */
#define SPECIAL_STORY_JUNGLE_SOUND_TO_BLACK_ID_PASS SPECIAL(0x1D)
/* GAME.progress is from STORY_WAY_TO_AMATERASU to STORY_PRESIDENT_ARRESTED
   (PROGRESS_RANGES[0x16]) */
#define SPECIAL_STORY_WAY_TO_AMATERASU_TO_PRESIDENT_ARRESTED SPECIAL(0x21)
/* GAME.progress is from STORY_JUNGLE_SOUND to STORY_PRESIDENT_ARRESTED
   (PROGRESS_RANGES[0x17]) */
#define SPECIAL_STORY_JUNGLE_SOUND_TO_PRESIDENT_ARRESTED SPECIAL(0x1E)
/* GAME.progress is from STORY_BLUE_ID_PASS to STORY_AMATERASU_BRIDGE
   (PROGRESS_RANGES[0x18]) */
#define SPECIAL_STORY_BLUE_ID_PASS_TO_AMATERASU_BRIDGE SPECIAL(0x1F)
/* GAME.progress is from STORY_JUNGLE_SOUND to STORY_NETWORK_OFFLINE
   (PROGRESS_RANGES[0x19]) */
#define SPECIAL_STORY_JUNGLE_SOUND_TO_NETWORK_OFFLINE SPECIAL(0x20)
/* GAME.progress is from STORY_GENJI_BEATEN to STORY_PRESIDENT_ARRESTED
   (PROGRESS_RANGES[0x1A]) */
#define SPECIAL_STORY_GENJI_BEATEN_TO_PRESIDENT_ARRESTED SPECIAL(0x22)
/* GAME.progress is from STORY_GENJI_BEATEN to STORY_STAFF_PASS
   (PROGRESS_RANGES[0x1B]) */
#define SPECIAL_STORY_GENJI_BEATEN_TO_STAFF_PASS SPECIAL(0x23)
/* GAME.progress is from STORY_TEDDY_FOUND to STORY_PRESIDENT_ARRESTED
   (PROGRESS_RANGES[0x1C]) */
#define SPECIAL_STORY_TEDDY_FOUND_TO_PRESIDENT_ARRESTED SPECIAL(0x24)
/* GAME.progress is from STORY_BYAKKO_BADGE to STORY_PRESIDENT_ARRESTED
   (PROGRESS_RANGES[0x1D]) */
#define SPECIAL_STORY_BYAKKO_BADGE_TO_PRESIDENT_ARRESTED SPECIAL(0x3B)
/* GAME.progress is from STORY_ZANBAMON_DRIVEN_OFF to STORY_AGUMON_DISGUISE
   (PROGRESS_RANGES[0x1E]) */
#define SPECIAL_STORY_ZANBAMON_DRIVEN_OFF_TO_AGUMON_DISGUISE SPECIAL(0x3C)
/* GAME.progress is from STORY_BULBMON_BEATEN to STORY_PRESIDENT_ARRESTED
   (PROGRESS_RANGES[0x1F]) */
#define SPECIAL_STORY_BULBMON_BEATEN_TO_PRESIDENT_ARRESTED SPECIAL(0x3D)
/* GAME.progress is from STORY_LOOKING_FOR_TEDDY to STORY_CONTROL_ROOM
   (PROGRESS_RANGES[0x20]) */
#define SPECIAL_STORY_LOOKING_FOR_TEDDY_TO_CONTROL_ROOM SPECIAL(0x3E)

/* checkFlagCount: the Master Room's sensors (wstag305), the letters M, O,
   N, S, T, E and R (FLAG_MASTER_ROOM_SENSOR_M_TOUCHED to _R_, GAME.flags1C
   0x27-0x2D), and the four leaders. Entry 0x72 (mode 3) is never true,
   and nothing uses it */

/* one of the Master Room's sensors or more is touched */
#define SPECIAL_MASTER_ROOM_SENSOR_TOUCHED SPECIAL(0x71)
/* two of the Master Room's sensors or more are still untouched */
#define SPECIAL_MASTER_ROOM_SENSORS_LEFT SPECIAL(0x70)
/* exactly one of the Master Room's sensors is untouched */
#define SPECIAL_MASTER_ROOM_LAST_SENSOR_LEFT SPECIAL(0x73)
/* the European and Japanese versions: FLAG_CHINRON_LEADER_FOUGHT,
   FLAG_ZHU_QUE_LEADER_FOUGHT, FLAG_BAI_HU_LEADER_FOUGHT and
   FLAG_XUAN_WU_LEADER_FOUGHT are all set, as the extra chapter's arena asks
   (wstag926) */
#define SPECIAL_FOUR_LEADERS_FOUGHT SPECIAL(0x54)

/* showActorIcon */

/* an action: the player's icon plays its animation 3 with SOUND_ITEM_GET
   (FIELD_COMMAND_ICON3); the talks that give an item or a partner apply it */
#define SPECIAL_SHOW_ITEM_GET_ICON SPECIAL(0x13)

#endif
