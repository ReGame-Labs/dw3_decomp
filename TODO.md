# TODO

The game is all C in both versions: the executable's game code and data,
the 21 overlays and the 293 European and 238 USA stages build byte for byte
from the same source (3,606 functions in the European version, 3,380 in the
USA one, code and data 100 %), with no fake matches. The PsyQ libraries,
Sony's code, stay splat's disassembly and out of the progress
([docs/status.md](docs/status.md)). What is left is making the C read well,
and the tooling around it. The counts below are from commit `ab85a3a6`.

## Names and types

- [ ] 197 struct fields in `include/` still have an `unk` name. The most are
  in `cardgame/screen.h` and `cardgame/battle.h` (18 each), `stgtrain.h`
  (17), `ststatus.h`, `stgmcard.h` and `dw3/game_state.h` (10 each). Nearly
  all are never read, or only written or copied, and their comments say so;
  name them when the code or the disc's data shows what they hold. The
  ones still read in `src/` (32 uses) are listed with what is known in
  their headers, for example `BATTLE_SETUP.unk3D`, which the enemy turn's
  condition 13 compares.
- [ ] 11 `D_` symbols are left, each with a comment on why:
  - `FIELDSTG`'s `D_80096983` and `D_8009AA3C`, never read;
  - `FIGHTSTG`'s `D_800A342C`, `D_800A3434` and `D_800A346C` in
    `fightstg.c`;
  - `WSTAG331`'s `D_800A5840`, `D_800A5AA4`, `D_800A5D2C` and `D_800A6F88`,
    the talk and condition lists that differ between the versions;
  - `WSTAG934`'s `D_800A6874` and `D_800A6878`, unused words that hold
    `startTween` and `updateTween`.
- [ ] Two functions keep splat's name: `WSTAG780`'s `func_800A7644`, an event
  end only the European version has (`endEvent1500` by the stage tools'
  rule, which name only the functions both versions have), and
  `func_80029DB8`, PsyQ's `GsSetRefView2`, which FIGHTSTG's cameras call.
- [ ] 184 pointer casts are left in `src/` (75 in FIGHTSTG, 33 in the
  executable, 14 in FIELDSTG, the rest a few per overlay). Each one says
  why it stays (another form changes the code) or is plain, like a byte
  offset or a `Task *`; replace one when a type that keeps the bytes turns
  up.
- [ ] Say what each stage is. They are in the folders of their areas
  ([src/stages/README.md](src/stages/README.md)); each stage's file should
  also say which map or event it is.

## Shared code

- [ ] Near duplicates are left as copies, because their code differs:
  - in the stages, `isFarFromHome`, `moveWanderer` / `moveWanderPair`, the
    `handleCommand*` sets, the `fadeOut*` pairs, `updateTileSix` /
    `updateTileSixW` and the list menus' event updates;
  - the `stepTileAnimationN` copies, whose recursive calls name each copy;
  - `WFIGHTMN_createLayers` and `WFIGHTTS_initLayers` (10 and 5 callbacks).
  Share one when a parameter or a macro can give each copy its difference
  with the bytes unchanged.

## Data

- [ ] 56 top-level `__asm__` statements in 34 stage files write the
  non-zero padding halfword that the original has between some of a stage's
  data (event scripts, battles, images, animation frames). Write it in C
  instead, as part of the data it follows.
- [ ] 11 tables in 9 stage files are still plain `u32` / `s32` words
  (`WSTAG210`, `212`, `375`, `740`, `741`, `780`, `924`, `935` and `949`):
  give them types as the code that reads them is understood.
- [ ] The stages' data repeats between stages, and between the versions as
  `#if VERSION_US` / `VERSION_EU` rows: write what is the same once, where
  the bytes allow it.
- [ ] `src/main/data/` still holds the executable's data that has no module
  of its own yet: `matrices.c`, `game_3.c` (other modules' small data,
  among them the usable items' effects) and `game_bss.c`. Move each part
  next to the code that uses it where the link order allows.

## Tooling and docs

- [ ] The README's status table and the overlay table in
  [docs/binaries.md](docs/binaries.md) are written by hand from `make
  report`. A script in `tools/` should write them and the CI should check
  them, as it does the hacks badge (`tools/hacks.py --check`).
- [ ] decomp.dev's data total counts the `.bss` (139,344 bytes in the
  European version): decide whether the report should leave it out.
- [ ] Pull requests from forks only run the `names` job (`check_names.py`
  and `hacks.py`): the builds need the private repository with the original
  files.
- [ ] `objdiff.json` holds one version at a time: the last one `make
  objdiff` was run for.
- [ ] `make PAD=0x10004 smoke` ([docs/shifting.md](docs/shifting.md)) boots a
  shifted build in DuckStation; run it again on the current code.
