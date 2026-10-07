/* STITSHOP's scene: the mode's root task, and the screen fade */

#include "stitshop.h"

#define SCENE_TASK Task
#define SCENE_CHILD ItemShop
#define SCENE_CREATE OVL_NAME(createShop)
#define SCENE_PRIM_BUFFERS 0x14000
#define SCENE_OT_SHIFT 3
#include "../menu_common/update_scene.inc.c"
#include "../menu_common/start.inc.c"

#include "../menu_common/start_fader.inc.c"
#include "../menu_common/draw_fader.inc.c"
#include "../menu_common/update_fader.inc.c"
#define FADER_DEPTH 6
#include "../menu_common/create_fader.inc.c"
