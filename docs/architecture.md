# How the game works

This is a guide to Digimon World 3 as a program: what runs when, and where
its code is. It says what the code shows; where the code doesn't tell, it
says so. The paths are the repository's. [binaries.md](binaries.md) lists
the binaries and the memory maps, [src/README.md](../src/README.md) the
source folders, and [CONTRIBUTING.md](../CONTRIBUTING.md#layout) the
executable's modules.

## Overview

The executable holds the engine: a set of modules, each a global struct of
state and methods (`GFX`, `HEAP`, `FILE_CACHE`, `PAD`, `SOUND`, `GAME`...).
Everything else is an overlay that the engine loads for the current game
mode, and every object of the game, from the field to a cursor, is a task.

```
main()                                    src/engine/system/main.c
  start the hardware, the libraries and the engine modules
  GAME.funcs.newGame(): the first mode
  every frame:
    no mode task?  free the mode's memory, commit the new mode,
                   ROOT_TASK = createModeTask()
    TASK_REGISTRY.funcs.run(ROOT_TASK)    the task tree, one update each
      updateModeTask                      src/engine/system/overlay.c
        loads the mode's overlay, calls MODE_ENTRY_POINTS[mode >> 8]()
        FIELDSTG_start, FIGHTSTG_start, CARDGAME_start, ...
          the overlay's tasks; FIELDSTG and FIGHTSTG load a sub-overlay
          (a stage WSTAG###, or WFIGHTMN / WFIGHTTS) and run its tasks
    GFX.funcs.drawFrame(ROOT_TASK)        the layers' ordering tables to the GPU
    PAD.update(), RANDOM.next(), FILE_CACHE.update(), SOUND.updateLoading()

RAM
  executable        .rodata .text .data .bss
  OVERLAY_VRAM      the mode's overlay: FIELDSTG, FIGHTSTG, CARDGAME, STITSHOP...
  STAGE_VRAM        a sub-overlay: WSTAG###, WFIGHTMN, WFIGHTTS
  HEAP_START        the heap, up to 0x801FF000
```

## Boot and the main loop

`main` in [main.c](../src/engine/system/main.c) sets the video mode, starts
the GPU (`GFX.funcs.reset`, `GsInitGraph`, `GsInit3D`), the sound library
and the GTE, and shows the boot image, a 320x480 TIM loaded with the
executable at `SUB_OVERLAY_ADDRESS`. It then starts the CD and the engine:
`HEAP.init`, `SOUND.init`, `RANDOM.seed(0)`, `MEMCARD_FUNCS.init`,
`PAD.init`, `GAME.funcs.newGame` and `FONT.load`. `newGame`
([state.c](../src/engine/game/state.c)) picks the first mode:
`MODE_OPENING` in the USA and Japanese versions, `MODE_COUNTRY_SELECT` in
the European one.

The loop runs one frame per iteration. When `ROOT_TASK` is `NULL` (a new
mode was asked for), it frees the primitive buffers, clears the task
registry, frees every heap block tagged `MEM_MODE`, calls
`GAME.funcs.commitMode` and creates the mode task again. Then it runs the
task tree, draws the frame (which waits for the vsync), reads the pads,
steps the random numbers and runs the file cache and the sound loading.

## Game modes and overlays

`GAME.mode` ([game_state.h](../include/engine/game_state.h), the `MODE_*`
constants) says what the game is doing. Its high byte picks the overlay:
`MODE_OVERLAY(mode)` is `mode & 0xFF00`, and the overlay reads the rest
itself (FIELDSTG looks its stage up by the whole mode; STDWTITL plays a
movie by it). Code
asks for a new mode with `GAME.funcs.requestMode(mode, arg)`;
`isModeChangePending` is then true until `commitMode` moves `nextMode` to
`mode` and the old one to `prevMode`.

[overlay.c](../src/engine/system/overlay.c) holds the two tables, indexed by
`mode >> 8`: `MODE_OVERLAY_FILES`, the overlay's file (the `FILE_*` numbers
of [overlay.h](../include/engine/overlay.h), per version), and
`MODE_ENTRY_POINTS`, its entry point. `updateModeTask`, the root task:

1. in `TASK_INIT`, calls `OVERLAY_LOADER.loadModeOverlay`, which reads the
   file through `FILE_CACHE.load` and copies it to `OVERLAY_ADDRESS` (only
   when the overlay changed), then calls the entry point, which returns the
   overlay's top task; that becomes its only child;
2. in `TASK_RUN`, kills itself once `isModeChangePending`, which ends the
   whole tree; `main` starts the next mode on the next frame.

FIELDSTG has two mode numbers (`0x2xx` and `0x3xx`); `MODE_ENTRY_POINTS`
has no overlay for `0x0`, `0x1` and `0x11`. An overlay's entry point is
`<PREFIX>_start` (STGDGLAB's is `STGDGLAB_createScene`), declared in
`overlay.h`, the only header the executable and every overlay share.

`loadSubOverlay(file)` copies a file to `SUB_OVERLAY_ADDRESS` the same way.
Two overlays use it:

- FIELDSTG loads a **stage**. `FIELDSTG_updateField`
  ([field.c](../src/field/field_mode/field.c)) calls `FIELDSTG_state.init`,
  which is `FIELDSTG_pickStage` ([state.c](../src/field/field_mode/state.c)):
  it looks the current mode up in `FIELDSTG_stages`
  ([data/fieldstg.c](../src/field/field_mode/data/fieldstg.c), `StageEntry`:
  mode, file, start function; the European and Japanese versions look in
  `FIELDSTG_extraStages` first during the extra chapter). The field then
  loads the stage's file and calls its start function,
  `WSTAG###_startStage` (`startStage` in
  [start_stage.inc.c](../src/field/stages/common/start_stage.inc.c)), which
  creates the stage's task and calls the stage's setup.
- FIGHTSTG's root task (`FIGHTSTG_start`,
  [start.c](../src/battle/battle_mode/start.c)) loads WFIGHTMN, the normal
  battle, or WFIGHTTS, the battle test, when the mode's argument is set, and
  starts it (`WFIGHTMN_start`, `WFIGHTTS_start`).

Where each overlay loads, per version, is in
[binaries.md](binaries.md#the-games-binaries): `OVERLAY_VRAM` is right after
the executable's `.bss`, `STAGE_VRAM` right after CARDGAME, the largest
overlay, and the heap starts above every overlay
([link_heap.py](../tools/link_heap.py)).

## Tasks

[task.h](../include/engine/task.h), [task.c](../src/engine/task/task.c),
[registry.c](../src/engine/task/registry.c).

A task is a heap block (`MEM_MODE`) that starts with `TASK_HEADER(Type)`:
an id and two keys, a state machine (`state`, `substate`, `step`,
`counter`), `paused`, an array of child tasks, and its methods
(`setState`, `nextState`, `nextSubstate`, `nextStep`, `tickCounter`...,
`update` and `destroy`). Each overlay's types embed the header
(`typedef struct X { TASK_HEADER(X); ... } X;`).

- **Create:** `createTask(update, size, childrenSize)` allocates a zeroed
  task with room for `childrenSize / 4` children and installs the default
  methods. `createTaskWithId` also registers it, so that other code can
  find it with `TASK_REGISTRY.funcs.find(id, key1, key2)` (-1 matches
  anything; `TASK_REGISTRY_SIZE` entries).
- **Update:** once per frame, `executeTask` calls `update(task, children)`
  with the stack in the scratchpad, then runs the children in order
  (`runChildTasks`). A child slot is just a pointer: a task creates its
  children by storing them in its `children` array, and a child that dies
  leaves `NULL`. `paused` in `TASK_RUN` skips the update and the children.
- **States:** `TASK_INIT` runs once (usually to set things up and call
  `nextState`), `TASK_RUN` is the normal state, `TASK_DONE` means nothing
  to the engine, and `TASK_KILL` ends it: its last update runs, then
  `destroy` (`destroyTask` kills the children, unregisters the task and
  frees it). `nextState` and `setState` reset the substate, step and
  counter; the levels below work the same.
- **Kill now:** `TASK_REGISTRY.funcs.kill(task)` sets `TASK_KILL` and runs
  that last frame at once.

The tree's root is `ROOT_TASK` in `main`. Tasks don't draw in a draw method:
they write primitives into a layer during their update, or add a draw
callback to a layer (next section).

## Memory

[heap.c](../src/engine/system/heap.c) keeps a linked list of `MemBlock`s
from `HEAP_START` to `HEAP_END`. Each block has a tag: `MEM_MODE` blocks
(tasks and most allocations) are freed whenever the mode ends,
`MEM_FILE_CACHE` blocks belong to the file cache, and `MEM_LOCKED` ones
(`HEAP.lock`) survive a mode change. `HEAP.alloc` is first fit and, when
nothing fits, evicts the file cache's oldest file and tries again;
`allocHigh` takes the block from the end (the GPU packet buffers).

## Rendering

[gfx.h](../include/engine/gfx.h), [display.c](../src/engine/gfx/display.c),
[layer.c](../src/engine/gfx/layer.c).

`GFX` holds the double-buffered display (`disp[2]`, `buffer`), the two GPU
packet buffers (`primBufs`) and up to `LAYER_COUNT` layers. A **layer**
(`Layer`) is a drawing environment with an ordering table per buffer
(`ot[2]`, its length from `otShift`), a view and light matrix, and a list
of draw callbacks. `GFX.funcs.createLayer(rect, otShift, id)` makes one;
most modes first create `SCREEN_LAYER`, the whole screen, then
`0x1001` and up.

To draw, a task takes its layer (`GFX.funcs.getLayer(id)`), an ordering
table entry for a depth (`layer->getOtEntry(layer, depth)`, or
`getOtEntryZ` for a Z), writes a primitive at `GFX.funcs.getPrim()`, links
it with `addPrim` and moves the pointer on with `GFX.funcs.setPrim`. Or it
adds a callback to the layer (`addCallback`, `addSortedCallback`).

`drawFrame` ends the frame: it runs every layer's callbacks, waits for the
GPU and for the vsync (`vsyncCallback` flips the display buffer), sends each
layer's ordering table (`DrawOTag`) in the order of `GFX.layers`
(`moveLayer` reorders them), swaps the buffers, advances the clocks
(`frameCount`, `time`, `frameTime`, in 1/256 frames) and the play time,
and clears the next buffer's tables.

The drawers are small objects with methods, bound once and then used:

| Drawer | File | What it draws |
|---|---|---|
| `SPRITE_DRAWER` | [sprite_drawer.c](../src/engine/gfx/sprite_drawer.c) | a frame of a sprite sheet (`SpritePart`s), scaled or rotated; the menu sheet is `FILE_MENU_SPRITES` |
| `CARD_DRAWER` | [card_drawer.c](../src/engine/gfx/card_drawer.c) | a card's 32x32 image, from `CARD_IMAGE_FILES` |
| `TIM_LOADER` | [tim_loader.c](../src/engine/gfx/tim_loader.c) | not a drawer: sends TIM images and archives of them to VRAM |
| `ScreenFade` | [screen_fade.c](../src/engine/gfx/screen_fade.c) | a task that fades the screen in or out with a subtractive quad |

The overlays have their own copies of the fader, from
[src/shared/](../src/shared/) (`draw_fader.inc.c`, `create_fader.inc.c`...).
FIELDSTG and FIGHTSTG also draw 3D models and maps with their own code;
see their sections.

## Files and the CD

[file.h](../include/engine/file.h), [src/engine/file/](../src/engine/file/).

The game reads its files by number, never by name. `FILE_TABLE`
([file_table.c](../src/engine/file/file_table.c)) gives a number's first
sector and its sector count (`FILE_SECTORS`, `FILE_SECTOR_COUNTS`); the
numbers differ between versions (`FILE_*` in the headers).

- `CD_READER` ([cd_reader.c](../src/engine/file/cd_reader.c)) reads a file,
  or part of one, through the CD callbacks.
- `FILE_CACHE` ([file_cache.c](../src/engine/file/file_cache.c)) keeps up to
  64 files in the heap. `request` queues a file and `update`, once a frame,
  reads them one at a time (`isLoading` tells when they're in); `load`
  waits for the file. A loaded file stays until it is freed or evicted (the
  least recently used first). Many files are archives:
  `FILE_CACHE.getEntry(file << 16 | index)` returns an entry.
- The `Decompressor` task ([decompressor.c](../src/engine/file/decompressor.c))
  unpacks the RLE data marked `RLEN`, at once or a chunk per frame.

The overlays are files like the others: `loadModeOverlay` and
`loadSubOverlay` read them through the cache and copy them into place.

## Text

[text.h](../include/engine/text.h), [src/engine/text/](../src/engine/text/).

The game's texts are string tables in the text files (`TEXT_*` in
`file.h`): `getString(table, index)` returns one. `TEXT_FILE(file)` gives the
file to read: the USA version reads the number as it is; the European disc
has each text file once per language in a row, and adds `LANGUAGE`, which
the country select sets; the Japanese version is the European code with
`LANGUAGE` 0, the Japanese copy.

- `createTextWindow` ([text_window.c](../src/engine/text/text_window.c))
  shows text, typed out or at once, with the `0x02` control codes of
  `TEXT_CODE_HANDLERS` (new line, wait for a button, the player's name...).
- `createMessageBox` ([message_box.c](../src/engine/text/message_box.c))
  and `createTalkBox` ([talk_box.c](../src/engine/text/talk_box.c)) are the
  game's boxes: a framed message, and a character's name and speech.
- `createCursor` ([cursor.c](../src/engine/text/cursor.c)) is the menus'
  pointer.
- `FONT` ([font.c](../src/engine/text/font.c)) loads the font sheet
  (`FILE_FONT`) and decodes characters. A text is either in font codes
  (the text files) or in Shift-JIS (the strings in the code, such as the
  debug menus); `FONT.decode` reads both, through the glyph maps of
  [text_tools.c](../src/engine/text/text_tools.c), and `convertText`
  converts between them. The glyph tables differ between the European
  version and the other two; what each version's font codes stand for is in
  the font file, which the code doesn't describe.

## Sound and music

[sound.h](../include/engine/sound.h), [sound.c](../src/engine/sound/sound.c).

`SOUND.playSound(id)` plays a sound whose id says everything: a VAB key-on
or a SEP sequence, whether it is exclusive (music, which stops the previous
`SOUND.music`), and its bank (`SOUND_*` for the system sounds, `MUSIC(bank,
n)` for a song). The banks (`SOUND_BANK_FILES`) load in the background into
three slots: slot 0 keeps bank 1, the system sounds, and the others
alternate; `SOUND.isLoading` tells when one is ready. A field takes its
music from its `FieldState` (`music`, `soundBank`), a battle from
`BATTLE_SETUP.music`.

## Pads

[pad.h](../include/engine/pad.h), [src/engine/pad/](../src/engine/pad/).

`PAD.update` reads both ports once a frame into `PadSlot`s: the buttons
`pressed`, `held` and `repeated` this frame (`PAD_PRESSED`, `PAD_HELD`,
`PAD_REPEATED` and the `PAD_*` bits); the analog stick also sets the
directions. Menus confirm with `PAD_CROSS` and cancel with `PAD_TRIANGLE`.
[port.c](../src/engine/pad/port.c) maps the pad's circle, cross and
triangle to their `PAD_*` bits in the USA version and for every European
language but Japanese, and keeps them as they are for Japanese. `setVibration` runs the motors.
[demo.c](../src/engine/pad/demo.c) plays recorded input in place of the pad
(recording is a stub).

## Memory card

[memcard.h](../include/engine/memcard.h),
[memcard.c](../src/engine/memcard/memcard.c), and the screen,
STGMCARD ([src/menus/memory_card/](../src/menus/memory_card/)).

`MEMCARD_FUNCS` are step functions: each call does a step and returns 0
while working, 1 when done, an error code + 1 on failure. A save file
(`setSaveFileName`: `BASLUS-01436DMW3-USA` and the European and Japanese
names) has a header and icon, an info section (`MemCardFile`: the three
saves' summaries) and three data sections, each a `GameSave`: the first
`GAME_SAVE_SIZE` bytes of `GAME` (the party, the items, the progress and the
saved flags).

## The game state

[game_state.h](../include/engine/game_state.h),
[src/engine/game/](../src/engine/game/).

`GAME` (`GameState`) is the saved game followed by the mode and the
methods (`GAME.funcs`): the party and partners
([party.c](../src/engine/game/party.c),
[partner.c](../src/engine/game/partner.c)), their stats
([stats.c](../src/engine/game/stats.c)), the Digimon and item tables
([digimon.c](../src/engine/game/digimon.c),
[items.c](../src/engine/game/items.c)), the play time, the mode
([state.c](../src/engine/game/state.c)), and the story's progress and flags
([events.c](../src/engine/game/events.c), next section).

## The field and its scripts

FIELDSTG, [src/field/field_mode/](../src/field/field_mode/) (each file
starts with what it does), [field_mode.h](../include/field/field_mode.h),
[field_map.h](../include/field/field_map.h); the stages,
[src/field/stages/](../src/field/stages/README.md),
[stage.h](../include/field/stage.h).

`FIELDSTG_start` ([start.c](../src/field/field_mode/start.c)) creates the
root task, which creates the field task (`FIELDSTG_updateField`,
[field.c](../src/field/field_mode/field.c)): it picks and loads the stage
(see [Game modes and overlays](#game-modes-and-overlays)), loads the map and
its files, runs the player, the partners and the other characters as actors
([actor.c](../src/field/field_mode/actor.c),
[actor_control.c](../src/field/field_mode/actor_control.c)), the camera,
the map's triggers ([trigger.c](../src/field/field_mode/trigger.c)) and the
random battles ([battle.c](../src/field/field_mode/battle.c)).

**A stage** (`wstag###.c`) is mostly data: `setupStage` fills
`FIELDSTG_state` (`FieldState`) with the stage's text file, map, objects,
music, characters (`FieldActorEntry`, each with the conditions under which
it appears and what it says, `FieldTalk`), its map slots (`StageSlot`) and
its events (`FieldEvent stageEvents[]`). Code the stages share is in
[common/](../src/field/stages/common/).

**Event scripts.** A `FieldEvent` has an id, a script (an `s16` array) and
the text file its talks use, or, without a script, a task to start.
`FIELDSTG_startEvent(id)` ([event.c](../src/field/field_mode/event.c))
finds it and starts `FIELDSTG_runEvent`, the script interpreter. A script
is a list of `SCRIPT_*` commands ([field_map.h](../include/field/field_map.h)):
a halfword `kind << 8 | variant` and fixed arguments. They place, pose and
walk characters, show talks, wait (frames, a box, a walk, an animation),
move the camera, leave the field (`SCRIPT_LEAVE`), or send a script command
(`SCRIPT_COMMAND`, the table `FIELDSTG_scriptCommands`, such as the field
commands of [commands.c](../src/field/field_mode/commands.c)). The
interpreter runs commands back to back until one waits, then goes on from
there the next frame; `SCRIPT_END` ends the event. The scripts have no
jumps or conditions.

**Conditions and actions.** The choices are made by lists of `(code,
value)` pairs ending with `CODES_END`, built with the macros of
[game_state.h](../include/engine/game_state.h): `FLAG(group, id)` (a story
flag), `PROGRESS(n)` (`GAME.progress` is n), `SPECIAL(id)` (an entry of
`SPECIAL_CONDITIONS`), and `PARTY_STAT`, `ITEM`, `CARD`, `WARP_ARG`.
`FLAGS_00.checkConditions` holds when all hold; `FLAGS_00.applyActions`
sets the flags and runs the actions, which can start a battle
(`EVENT_BATTLE`), a card battle (`CARD_BATTLE`), another event
(`START_EVENT`), give items or cards, or open a shop, the inn, the lab or
a gym. Both are in [events.c](../src/engine/game/events.c). The field reads
them for a character's appearance and talk, a map slot's two conditions and
the story events.

**Progress and flags.** `GAME.progress` is the story's chapter, a number.
The flags are bits in banks, `GAME.flags02` to `GAME.flags40`, saved with
the game (their sizes differ per version); group `0x00` is `FLAGS_00.bits`,
outside `GAME` and not saved, which the field clears when the player comes
from another mode (`GAME.clearTempFlags`). The values themselves are named
in the headers as they are found.

**Story events.** WSTAG260 ([wstag260.c](../src/field/stages/wstag260.c))
is only scripts. FIELDSTG's own events table (`FIELDSTG_events`) points to
them, and `FIELDSTG_runStoryEvents` ([story.c](../src/field/field_mode/story.c))
starts the first of `FIELDSTG_progressEvents` whose progress is
`GAME.progress`, whose flag is clear and whose condition holds, then the
script it chains to.

**Leaving the field.** `FIELDSTG_leaveField(mode, arg, x, y, dir)` ends the
field task, which then calls `requestMode` and keeps where the player was
(`GAME.fieldMode`, `fieldPos`, `fieldDir`), where a battle, a shop or a
menu returns to. A battle starts with `FIELDSTG_startEncounter`, which
fills `BATTLE_SETUP` from `FIELDSTG_encounters`. START opens the field menu
(`createFieldMenu`, [field_menu.c](../src/engine/menu/field_menu.c), in the
executable), whose choices switch to STSTATUS; the inn
([inn.c](../src/engine/menu/inn.c)) is also in the executable.

## The battle

FIGHTSTG, [src/battle/battle_mode/](../src/battle/battle_mode/) and
[include/battle/battle_mode/](../include/battle/battle_mode/); WFIGHTMN,
[src/battle/normal_battle/](../src/battle/normal_battle/); STFGTREP, the
report, [src/battle/report/](../src/battle/report/).

FIGHTSTG has the battle's machinery: the stage, lights, models and faces,
the cameras, the menus and windows, the event queue, the battle scripts and
the rolls. WFIGHTMN runs a battle with it:

1. **Setup.** `WFIGHTMN_start` ([menu.c](../src/battle/normal_battle/menu.c))
   creates the battle task, which creates the layers, plays
   `BATTLE_SETUP.music`, creates the player's turn, the camera, the stage,
   the models and the lights, sets the battle's kind, adds the fighters
   (`BATTLE_SETUP.enemies`, the party from `GAME`), rolls an ambush and
   queues the first turns.
2. **Turns.** The battle is a timed queue of events, not rounds:
   `FIGHTSTG_events` ([events.c](../src/battle/battle_mode/events.c)). An
   event (`EVENT_*` in [battle.h](../include/battle/battle_mode/battle.h))
   has a delay, from `FIGHTSTG_getEventDelay` and the fighter's stats;
   `FIGHTSTG_popEvent` takes the next one due. `WFIGHTMN_runTurn` runs it
   with the handler of `WFIGHTMN_states`, and queues both sides' turns
   again when the queue is empty.
3. **Actions.** On the player's turn the command menu
   ([command_menu.c](../src/battle/battle_mode/command_menu.c),
   `BATTLE_COMMAND_*`) picks an attack, a technique, a digivolution, a
   switch, an item or running away; `WFIGHTMN_runCommand` carries it out.
   The enemy picks from its entry of the battle table
   ([enemy_turn.c](../src/battle/battle_mode/enemy_turn.c)). A technique
   becomes `FIGHTSTG_action`, which `FIGHTSTG_startAction`
   ([tech_effects.c](../src/battle/battle_mode/tech_effects.c)) resolves
   with the rolls and formulas of `FIGHTSTG_battleFuncs`
   ([damage.c](../src/battle/battle_mode/damage.c),
   [rolls.c](../src/battle/battle_mode/rolls.c),
   [stats.c](../src/battle/battle_mode/stats.c)). Statuses are flags of
   the fighter, and their ends are queued events.
4. **Scripts.** What a technique shows is a battle script
   ([battle_script.c](../src/battle/battle_mode/battle_script.c)): a task
   that runs `s16` opcodes from the fighter's file, for hits, models,
   effects, the stage, the camera, fades, sounds and waits.
5. **Camera.** `FIGHTSTG_createBattleCamera`
   ([battle_camera.c](../src/battle/battle_mode/battle_camera.c),
   [camera.h](../include/battle/battle_mode/camera.h)) and the shot and
   fighter cameras.
6. **End.** `FIGHTSTG_endBattle(result)` queues the end; `WFIGHTMN_endBattle`
   writes the partners' HP and MP back to `GAME` and asks for the next
   mode: the field after running away, the report (`MODE_BATTLE_REPORT`,
   STFGTREP, which gives the rewards and raises the partners' stats) or the
   ending after a win, the title screen after a loss.

## The card game

CARDGAME, [src/cardgame/card_battle/](../src/cardgame/card_battle/) and
[include/cardgame/card_battle/](../include/cardgame/card_battle/).

The mode's argument is the opponent. `CARDGAME_createBattle` makes the
`CardBattle` task, and `CARDGAME_runBattle`
([battle.c](../src/cardgame/card_battle/battle.c)) runs it one frame at a
time in one of four ways (`CardRun`): a phase of the battle, a step of a
card's effect script (`CARDGAME_runEffectStep`,
[effect_script.c](../src/cardgame/card_battle/effect_script.c)), the
resolution of a card, or a menu. The phases (`CardPhase`) go: choose a
deck, toss for who picks first, deal, play cards before and after putting
out, end the round. The side with more HP wins a round, and two rounds win
the battle. The computer plays with
[computer.c](../src/cardgame/card_battle/computer.c). The deck editor
(STCRDDEK), the card packs (STCRDSHP) and the album (STCRDABM) are menus.

## The menus

[src/menus/](../src/menus/) and the copies in [src/shared/](../src/shared/).

The menu overlays have one shape. `scene.c` is the root task: it defines a
few `SCENE_*` macros and includes
[update_scene.inc.c](../src/shared/update_scene.inc.c), which resets the
graphics, creates a black `SCREEN_LAYER` and the overlay's main task;
[start.inc.c](../src/shared/start.inc.c) gives the entry point. A shared
function takes the overlay's prefix through `OVL_NAME(name)`, so each
overlay has its own copy (`STGMCARD_drawFader`). The main task then shows
screens, usually from a table (`STSTATUS_screens`, `STGDGLAB_screens`),
and ends with `requestMode`, mostly back to `GAME.fieldMode`. The name
entry keyboard ([name_entry.h](../include/shared/name_entry.h)) is shared by
STPLNMET, STDGNAME and STCRDDEK. [src/README.md](../src/README.md) says
what each overlay is.

## The debug overlays

[src/debug/](../src/debug/). STAGSLCT, the stage select
([stage_select.c](../src/debug/stage_select/stage_select.c)), is a list of
every scene (`STAGSLCT_entries`: a name, a mode and its argument). Its
entries reach the other tools: the battle test (`MODE_BATTLE` with argument
1, which loads WFIGHTTS), the sound test (SOUNDTST), the vibration test
(SHOCKTST), and the card battles with a nonzero low digit, which return to
it. How the released game reaches the stage select is unknown: no code
outside these tools asks for `MODE_STAGE_SELECT`.

## The versions

The same C builds the three versions; the rules for writing a difference
are in [CONTRIBUTING.md](../CONTRIBUTING.md#versions), and what each
version is in [binaries.md](binaries.md#how-the-versions-are-organised).
In the code, the differences are of these kinds:

- **Tests of the version:** `#if VERSION_US`, `#elif VERSION_EU`,
  `#if VERSION_US || VERSION_JP`..., from
  [version.h](../include/version.h). Most are in the stages and are data:
  file numbers, positions, the stages the European version
  adds (`WSTAG920` and up, which the Japanese version has too).
- **`PAL_VIDEO`** (the European version): the 50 Hz display and clocks
  (`VSYNC_STEP_PAL`), unless `NTSC_MODE`, and the display moved down
  (`SHIFT_PAL_SCREEN`), in [main.c](../src/engine/system/main.c),
  [display.c](../src/engine/gfx/display.c) and the card game's layouts.
- **Languages:** the European version's `LANGUAGE`
  ([eu_settings.c](../src/engine/data/eu_settings.c)), set by the country
  select ([country_select.c](../src/menus/country_select/country_select.c)),
  picks the text files (`TEXT_FILE`, `TEXT_ENTRY`, `EXTRA_TEXT`), the
  save's name and the buttons; the Japanese version has `LANGUAGE` 0.
- **File numbers:** `FILE_*` constants per version, in the headers that use
  them.

## Where to start reading

- One frame: `main` ([main.c](../src/engine/system/main.c)), then
  `executeTask` ([registry.c](../src/engine/task/registry.c)) and
  `drawFrame` ([display.c](../src/engine/gfx/display.c)).
- A small overlay from top to bottom: SOUNDTST
  ([sound_test.c](../src/debug/sound_test/sound_test.c)) or the item shop
  ([src/menus/item_shop/](../src/menus/item_shop/)).
- A stage: any `wstag###.c` in an area of
  [src/field/stages/](../src/field/stages/README.md), with `FieldState`
  ([field_map.h](../include/field/field_map.h)) and the script macros next
  to it.
- A battle: `WFIGHTMN_updateMenu` and `WFIGHTMN_runTurn`
  ([menu.c](../src/battle/normal_battle/menu.c)).
