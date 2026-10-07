/* STGMCARD's scene: the mode's root task, and the screen fade */

#include "stgmcard.h"

#define SCENE_TASK MemCardScene
#define SCENE_CHILD MemCardScreen
#define SCENE_CREATE OVL_NAME(createScreen)
#define SCENE_PRIM_BUFFERS 0x5000
#define SCENE_OT_SHIFT 2
#include "../menu_common/update_scene.inc.c"
#include "../menu_common/start.inc.c"

#include "../menu_common/start_fader.inc.c"
#include "../menu_common/draw_fader.inc.c"
#include "../menu_common/update_fader.inc.c"
#define FADER_DEPTH 0
#include "../menu_common/create_fader.inc.c"
