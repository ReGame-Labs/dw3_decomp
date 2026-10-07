/* Creates a scroll bar on the top layer (0x1000) at the including overlay's
   SCROLL_BAR_DEPTH; it shows once its range and count are set */
ScrollBar *OVL_NAME(createScrollBar)(void) {
    ScrollBar *bar = createTask(OVL_NAME(updateScrollBar), sizeof(ScrollBar), 0);

    bar->setX = OVL_NAME(setScrollBarX);
    bar->setRange = OVL_NAME(setScrollBarRange);
    bar->setCount = OVL_NAME(setScrollBarCount);
    bar->setPos = OVL_NAME(setScrollBarPos);
    bar->layer = 0x1000;
    bar->depth = SCROLL_BAR_DEPTH;
    return bar;
}
