/*
 * The update of the stage's task (startStage) in the stages that only copy
 * the points of the place the player comes from (GAME.unk44 and unk46) to
 * their triggers (FIELDSTG_state.slots), before the task moves on
 */
void updateStage(StageTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        copyPlacePoints(FIELDSTG_state.slots, placePoints, GAME.unk44, GAME.unk46);
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}
