/*
 * Events 9000 to 9015: the player stops, then each partner of the party (the
 * stage's partyActorIds) in turn gets a createSpritePair effect and is left
 * with 1 HP, 0x1E frames apart; the task then runs while the first effect is
 * in children->party[0]
 */
void updateEvent9015(StageTask *task, StagePartyChildren *children) {
    StageActor *player;
    StageActor *actor;
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        switch (task->substate) {
        case 0:
        default:
            switch (task->step) {
            case 0:
            default:
                player = TASK_REGISTRY.funcs.find(FIELD_TASK_ACTOR, -1, 0);
                player->setSubstate(player, 1);
                SOUND.playSound(SOUND_SWITCH02);
                task->nextStep(task);
            case 1:
                task->counter += GFX.funcs.getFrameTime();
                if (task->counter >= 0x1E) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 1:
        case 2:
        case 3:
            switch (task->step) {
            case 0:
            default:
                i = task->substate - 1;
                actor = TASK_REGISTRY.funcs.find(FIELD_TASK_ACTOR, -1, partyActorIds[i]);
                if (actor != NULL) {
                    children->party[i] = createSpritePair(actor->tileX, actor->tileY);
                    SOUND.playSound(SOUND_COMEX113);
                    actor->setSubstate(actor, 4);
                    GAME.partners[GAME.party[i]].info.stats[STAT_HP] = 1;
                    task->nextStep(task);
                } else {
                    task->nextSubstate(task);
                }
                break;
            case 1:
                task->counter += GFX.funcs.getFrameTime();
                if (task->counter >= 0x1E) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 4:
            task->nextState(task);
            break;
        }
        break;
    case TASK_RUN:
        if (children->party[0] == NULL) {
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}
