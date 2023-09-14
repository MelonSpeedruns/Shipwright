#ifndef Z_EN_FIRSTPERSON_BULLET_H
#define Z_EN_FIRSTPERSON_BULLET_H

#include <libultraship/libultra.h>
#include "global.h"
#include "src/overlays/actors/ovl_En_Arrow/z_en_arrow.h"

struct EnFirstPersonBullet;

typedef void (*EnFirstPersonBulletActionFunc)(struct EnFirstPersonBullet*, PlayState*);

typedef struct EnFirstPersonBullet {
    Actor actor;
    ColliderQuad collider;
    s32 effectIndex;
    WeaponInfo bulletInfo;
    u8 deadTimer;
    u8 hitWall;
} EnFirstPersonBullet; // size = 0x0260

#ifdef __cplusplus
extern "C" {
#endif
void EnFirstPersonBullet_Init(Actor* thisx, PlayState* play);
void EnFirstPersonBullet_Destroy(Actor* thisx, PlayState* play);
void EnFirstPersonBullet_Update(Actor* thisx, PlayState* play);
void EnFirstPersonBullet_Draw(Actor* thisx, PlayState* play);
#ifdef __cplusplus
}
#endif

#endif
