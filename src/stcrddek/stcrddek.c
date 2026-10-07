/* STCRDDEK's scene: the mode's root task, and the screen fade */

#include "stcrddek.h"

#define SCENE_TASK Task
#define SCENE_CHILD DeckScreen
#define SCENE_CREATE OVL_NAME(createScreen)
#define SCENE_PRIM_BUFFERS 0xF000
#define SCENE_OT_SHIFT 3
#include "../menu_common/update_scene.inc.c"
#include "../menu_common/start.inc.c"

#include "../menu_common/start_fader.inc.c"
#include "../menu_common/draw_fader.inc.c"
#include "../menu_common/update_fader.inc.c"
#define FADER_DEPTH 0
#include "../menu_common/create_fader.inc.c"
