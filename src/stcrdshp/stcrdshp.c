/* STCRDSHP's scene: the mode's root task */

#include "stcrdshp.h"

#define SCENE_TASK Task
#define SCENE_CHILD CardShop
#define SCENE_CREATE OVL_NAME(createShop)
#define SCENE_PRIM_BUFFERS 0xF000
#define SCENE_OT_SHIFT 3
#include "../menu_common/update_scene.inc.c"
#include "../menu_common/start.inc.c"
