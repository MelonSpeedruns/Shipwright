#include "ultra64.h"
#include "global.h"

struct LinkPuppet;

typedef struct LinkPuppet {
    Actor actor;
    SkelAnime linkSkeleton;
    ColliderCylinder collider;
    OnlinePacketZ64 packet;
    ColliderQuad swordQuads[2];
    ColliderQuad shieldQuad;
    uint8_t damageTimer;
    uint8_t initialized;
} LinkPuppet;