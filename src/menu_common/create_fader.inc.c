/* Creates the screen fade, idle until started, on the top layer (0x1000) at
   the including overlay's FADER_DEPTH */
ScreenFade *OVL_NAME(createFader)(void) {
    ScreenFade *task = createTask(OVL_NAME(updateFader), sizeof(ScreenFade), 0);

    task->start = OVL_NAME(startFader);
    task->layerId = 0x1000;
    task->depth = FADER_DEPTH;
    return task;
}
