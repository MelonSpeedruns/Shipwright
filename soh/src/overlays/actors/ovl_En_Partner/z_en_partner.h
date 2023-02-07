#ifndef Z_EN_PARTNER_H
#define Z_EN_PARTNER_H

#include <libultraship/libultra.h>
#include "global.h"

struct EnPartner;

typedef void (*EnPartnerActionFunc)(struct EnPartner*, PlayState*);

typedef struct EnPartner {
    Actor actor;
    SkelAnime skelAnime;
    Vec3s jointTable[15];
    Vec3s morphTable[15];
    ColliderCylinder collider;
    Color_RGBAf innerColor;
    Color_RGBAf outerColor;
    LightInfo lightInfoGlow;
    LightNode* lightNodeGlow;
    LightInfo lightInfoNoGlow;
    LightNode* lightNodeNoGlow;
    f32 yVelocity;
    u8 lastWasCutscene;
    u8 selectedItem;
    s8 maxItems;
    s8 nutTimer;
    u8 canMove;
    Actor* hookshotTarget;
} EnPartner;

#endif