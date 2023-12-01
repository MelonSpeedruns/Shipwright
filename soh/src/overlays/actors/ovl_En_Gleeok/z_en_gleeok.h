#ifndef Z_EN_GLEEOK_H
#define Z_EN_GLEEOK_H

#include <libultraship/libultra.h>
#include "global.h"
#include <overlays/actors/ovl_En_Boom/z_en_boom.h>

struct EnGleeok;

typedef void (*EnGleeokActionFunc)(struct EnGleeok*, PlayState*);

typedef struct EnGleeok {
    Actor actor;
    SkelAnime skelAnime;
} EnGleeok;

#ifdef __cplusplus
extern "C" {
#endif
void EnGleeok_Init(Actor* thisx, PlayState* play);
void EnGleeok_Destroy(Actor* thisx, PlayState* play);
void EnGleeok_Update(Actor* thisx, PlayState* play);
void EnGleeok_Draw(Actor* thisx, PlayState* play);
#ifdef __cplusplus
}
#endif

#endif