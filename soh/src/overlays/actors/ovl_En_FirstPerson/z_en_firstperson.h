#ifndef Z_EN_FIRSTPERSON_H
#define Z_EN_FIRSTPERSON_H

#include <libultraship/libultra.h>
#include "global.h"

struct EnFirstPerson;

typedef void (*EnFirstPersonActionFunc)(struct EnFirstPerson*, PlayState*);

typedef struct EnFirstPerson {
    Player player;
    ColliderCylinder collider;
    u8 falling;
    f32 footstep_timer;
} EnFirstPerson;

#ifdef __cplusplus
extern "C" {
#endif
void EnFirstPerson_Init(Actor* thisx, PlayState* play);
void EnFirstPerson_Destroy(Actor* thisx, PlayState* play);
void EnFirstPerson_Update(Actor* thisx, PlayState* play);
void EnFirstPerson_Draw(Actor* thisx, PlayState* play);
#ifdef __cplusplus
}
#endif

#endif