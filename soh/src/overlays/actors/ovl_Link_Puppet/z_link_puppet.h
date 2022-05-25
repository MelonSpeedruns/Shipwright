#include "ultra64.h"
#include "global.h"

struct LinkPuppet;

typedef struct LinkPuppet {
    Actor actor;
    SkelAnime linkSkeleton;
    ColliderCylinder collider;
    OnlinePacket packet;
} LinkPuppet;