#include "ultra64.h"
#include "global.h"

struct LinkPuppet;

typedef struct LinkPuppet {
    Actor actor;
    SkelAnime linkSkeleton1;
    SkelAnime linkSkeleton2;
    Vec3s jointTable[24];
    Vec3s morphTable[24];
    Vec3s blendTable[24];
    ColliderCylinder collider;
    Vec3f leftFootPos;
    Vec3f rightFootPos;
    OnlinePacket packet;
} LinkPuppet;