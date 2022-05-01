#ifndef Z_ITEM_SHIELD_H
#define Z_ITEM_SHIELD_H

#include "ultra64.h"
#include "global.h"

struct LinkPuppet;

typedef struct LinkPuppet {
    Actor actor;
    SkelAnime linkSkeleton;
} LinkPuppet; // size = 0x020C

#endif
