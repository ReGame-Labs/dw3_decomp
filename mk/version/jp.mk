# Digimon World 3: Aratanaru Bouken no Tobira, Japan (SLPS-03446)
#
# Plain values: tools/version.py reads EXE_NAME and DISK_DIR from here too.

# the release, as the configs' headers name it
VERSION_NAME := Digimon World 3: Aratanaru Bouken no Tobira, Japan (SLPS-03446)

# the executable, as it is on the disc
EXE_NAME := SLPS_034.46

# where the extracted disc is (tools/extract_disc.py): the executable and
# AAA/, whose PRO/ directory holds the overlays
DISK_DIR := disks/jp

# The overlays the build links and checks, AAA/PRO/<FILE>.PRO: each one has
# its splat config, config/<version>/<name>.yaml. The stage overlays are
# added from config/<version>/stages.txt: the USA version's and the 55 more
# the European version has (WSTAG920-974).
OVERLAYS := cardgame cnty_sel fieldstg fightstg shocktst soundtst stagslct \
	stcrdabm stcrddek stcrdshp stdgname stdwtitl stfgtrep stgdglab \
	stgmcard stgtrain stitshop stplnmet ststatus wfightmn wfightts

# where the executable loads (main.yaml)
EXE_VRAM := 0x80010000

# where the overlays load, after the executable's .bss, and where the stage
# overlays and WFIGHTMN/WFIGHTTS load, after CARDGAME, the largest
OVERLAY_VRAM := 0x80082A60
STAGE_VRAM := 0x800A5770

# $gp, as crt0 sets it: main.yaml's gp_value, which tools/match_versions.py
# reads too (the overlays don't use $gp)
GP_VALUE := 0x8005C90C

# The C files this version builds: none yet. Every binary is splat's
# assembly, which builds the original byte for byte.
C_SRC :=
