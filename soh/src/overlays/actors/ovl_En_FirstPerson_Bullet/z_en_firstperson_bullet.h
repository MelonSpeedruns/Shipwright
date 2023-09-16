#ifndef Z_EN_FIRSTPERSON_BULLET_H
#define Z_EN_FIRSTPERSON_BULLET_H

#include <libultraship/libultra.h>
#include "global.h"

struct EnFirstPersonBullet;

typedef void (*EnFirstPersonBulletActionFunc)(struct EnFirstPersonBullet*, PlayState*);

typedef struct EnFirstPersonBullet {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ ColliderQuad collider;
    /* 0x0210 */ Vec3f unk_210;
    /* 0x021C */ Vec3f unk_21C;
    /* 0x0228 */ s32 effectIndex;
    /* 0x022C */ WeaponInfo weaponInfo;
    /* 0x0248 */ u8 timer; // used for dissapearing when flying or hitting a wall
    /* 0x0249 */ u8 hitFlags;
    /* 0x024A */ u8 touchedPoly;
    /* 0x024B */ u8 isCsNut;
    /* 0x024C */ Actor* hitActor;
    /* 0x0250 */ Vec3f unk_250;
    /* 0x025C */ EnFirstPersonBulletActionFunc actionFunc;
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
