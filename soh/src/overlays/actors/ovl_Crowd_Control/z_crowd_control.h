#ifndef Z_CROWD_CONTROL_H
#define Z_CROWD_CONTROL_H

#include "ultra64.h"
#include "global.h"

struct CrowdControl;

typedef struct CrowdControl {
    Actor actor;
    uint16_t effectType;
    uint32_t effectValue;
} CrowdControl;

#endif