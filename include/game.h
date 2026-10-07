#ifndef GAME_H
#define GAME_H

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libcd.h>

#include "dw3/task.h"
#include "dw3/heap.h"
#include "dw3/graphics.h"
#include "dw3/files.h"
#include "dw3/pad.h"
#include "dw3/sound.h"
#include "dw3/overlay.h"
#include "dw3/text.h"
#include "dw3/game_state.h"
#include "dw3/memcard.h"
#include "dw3/menus.h"

/* SDK functions declared here rather than from their PsyQ headers: libmcrd.h
   takes the buffers as u_long * and MemCardSync's result as a long *, where
   the game passes u8 buffers and compares the result unsigned; strings.h
   and memory.h declare these without prototypes, strlen as unsigned */
void MemCardInit(long val);
void MemCardStart(void);
long MemCardSync(long mode, long *cmds, u_long *result);
long MemCardExist(long chan);
long MemCardAccept(long chan);
long MemCardCreateFile(long chan, char *file, long blocks);
long MemCardFormat(long chan);
long MemCardReadFile(long chan, char *file, void *adrs, long ofs, long bytes);
long MemCardWriteFile(long chan, char *file, void *adrs, long ofs, long bytes);
long MemCardUnformat(long chan);
long MemCardGetDirentry(long chan, char *name, CardDirEntry *dir, long *files, long ofs, long max);
int strlen(const char *);
char *strcpy(char *dst, const char *src);
char *strncpy(char *dst, const char *src, s32 n);
void *memcpy(void *dst, const void *src, int size);

#endif /* GAME_H */
