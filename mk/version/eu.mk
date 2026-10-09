# Digimon World 2003, Europe (SLES-03936)
#
# Plain values: tools/version.py reads EXE_NAME and DISK_DIR from here too.

# the release, as the configs' headers name it
VERSION_NAME := Digimon World 2003, Europe (SLES-03936)

# the executable, as it is on the disc
EXE_NAME := SLES_039.36

# where the extracted disc is (tools/extract_disc.py): the executable and
# AAA/, whose PRO/ directory holds the overlays
DISK_DIR := disks/eu

# The overlays the build links and checks, AAA/PRO/<FILE>.PRO: each one has
# its splat config, config/<version>/<name>.yaml. The stage overlays are
# added from config/<version>/stages.txt: the USA version's and 55 more.
OVERLAYS := cardgame cnty_sel fieldstg fightstg shocktst soundtst stagslct \
	stcrdabm stcrddek stcrdshp stdgname stdwtitl stfgtrep stgdglab \
	stgmcard stgtrain stitshop stplnmet ststatus wfightmn wfightts

# where the executable loads (main.yaml)
EXE_VRAM := 0x80010000

# where the overlays load, after the executable's .bss, and where the stage
# overlays and WFIGHTMN/WFIGHTTS load, after CARDGAME, the largest
OVERLAY_VRAM := 0x80082CB0
STAGE_VRAM := 0x800A5DE0

# $gp, as crt0 sets it: main.yaml's gp_value, which tools/match_versions.py
# reads too (the overlays don't use $gp)
GP_VALUE := 0x8005CB50

# The C files this version builds: every module of the USA version, from the
# same C at this version's addresses (tools/version_symbols.py names what they
# use), and the stages only this version has. The executable and the overlays
# are split into the USA version's modules (tools/split_version.py), so that
# their asm lands at the same paths under asm/eu/ as under asm/us/; only the
# PsyQ libraries and the functions behind INCLUDE_ASM stay asm.
C_SRC := src/debug/soundtst/soundtst.c

# game: every module of the executable, and its data
C_SRC += $(shell find src/engine -name '*.c')

# menus
C_SRC += src/menus/stitshop/stitshop.c src/menus/stgdglab/stgdglab.c src/menus/ststatus/ststatus.c
# stitshop's modules, and its data
C_SRC += $(addprefix src/menus/stitshop/, trade.c item_list.c info.c shop.c equip.c data/stitshop.c)
# stgdglab's modules
C_SRC += $(addprefix src/menus/stgdglab/, recipe_screen.c entry_panel.c slot_screen.c menu.c scroll_bar.c)
C_SRC += $(addprefix src/menus/stgdglab/, party_screen.c skill_panel.c entry_list.c lab.c)
# ststatus's modules
C_SRC += $(addprefix src/menus/ststatus/, demo_screen.c equip_panel.c digivolve_panel.c status_screen.c item_screen.c item_list.c tech_screen.c sort_screen.c map_screen.c menu.c helpers.c)

# cardgame
C_SRC += src/cardgame/cardgame/cardgame.c
# cardgame's other objects and modules (cardgame.c is above), and the
# second and third objects' data
C_SRC += $(filter-out src/cardgame/cardgame/cardgame.c,$(wildcard src/cardgame/cardgame/*.c))
C_SRC += src/cardgame/cardgame/data/cardgame_2.c src/cardgame/cardgame/data/cardgame_3.c

# fightstg's other objects and modules (fightstg.c is with the overlays)
C_SRC += $(filter-out src/battle/fightstg/fightstg.c,$(wildcard src/battle/fightstg/*.c))

# small overlays
C_SRC += src/menus/stgmcard/stgmcard.c src/battle/stfgtrep/scene.c src/battle/stfgtrep/partner.c src/battle/stfgtrep/report.c src/battle/stfgtrep/fade.c src/battle/stfgtrep/growth.c src/battle/stfgtrep/data/stfgtrep.c src/battle/wfightmn/wfightmn.c src/battle/wfightmn/setup.c src/battle/wfightmn/menu.c src/battle/wfightmn/techs.c src/battle/wfightmn/data/wfightmn_2.c src/cardgame/stcrdshp/stcrdshp.c src/menus/stplnmet/stplnmet.c src/debug/wfightts/wfightts.c
# stcrdshp's modules
C_SRC += $(addprefix src/cardgame/stcrdshp/, pack_open.c fader.c card_grid.c buy.c shop.c)
# stgmcard's modules, and its data
C_SRC += $(addprefix src/menus/stgmcard/, info.c panel.c menu.c saves.c screen.c data/stgmcard.c)
# stplnmet's modules, and its data
C_SRC += $(addprefix src/menus/stplnmet/, backdrop.c welcome.c name_entry.c confirm.c choice.c screen.c data/stplnmet.c)

# overlays
C_SRC += src/debug/shocktst/shocktst.c src/menus/cnty_sel/cnty_sel.c src/cardgame/stcrdabm/stcrdabm.c
C_SRC += src/debug/stagslct/stagslct.c src/menus/stdgname/stdgname.c
# stdgname's modules, and its data
C_SRC += $(addprefix src/menus/stdgname/, name_entry.c menu.c screen.c data/stdgname.c)
C_SRC += src/menus/stdwtitl/stdwtitl.c
# stdwtitl's modules, and its data
C_SRC += $(addprefix src/menus/stdwtitl/, logo.c movie.c glint.c splash.c title_loader.c slides.c menu.c)
C_SRC += $(addprefix src/menus/stdwtitl/, edge_fade.c background.c title.c)
C_SRC += $(addprefix src/menus/stdwtitl/data/, stdwtitl.c title.c movie.c)
C_SRC += src/cardgame/stcrddek/stcrddek.c src/menus/stgtrain/stgtrain.c src/battle/fightstg/fightstg.c
# stcrddek's modules, and its data
C_SRC += $(addprefix src/cardgame/stcrddek/, deck_cards.c editor.c name_entry.c scroll_bar.c screen.c data/stcrddek.c)
# fieldstg's modules, and its data
C_SRC += $(wildcard src/field/fieldstg/*.c) src/field/fieldstg/data/fieldstg.c
# stgtrain's modules
C_SRC += $(addprefix src/menus/stgtrain/, sprite.c screen.c result.c session.c actor.c menu.c files.c)

# The stages: the USA version's, built from its C, and those it doesn't have,
# each in the folder of its area (tools/stage_areas.py), with WSTAG924's
# color in a file of its own before the stage's jump tables (wstag924_head.c,
# tools/stage_yaml.py)
C_SRC += $(sort $(shell find src/field/stages -name '*.c' ! -name '*.inc.c'))
