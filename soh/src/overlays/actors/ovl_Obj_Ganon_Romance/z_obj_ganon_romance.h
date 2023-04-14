#ifndef Z_OBJ_GANON_ROMANCE_H
#define Z_OBJ_GANON_ROMANCE_H

#include <libultraship/libultra.h>
#include "global.h"

struct ObjGanonRomance;

typedef struct ObjGanonRomance {
    Actor actor;

    SkelAnime skelAnime;
    Vec3s jointTable[24];
    Vec3s morphTable[24];
    s8 animObjBankIndex;
} ObjGanonRomance; // size = 0x017C

#endif
