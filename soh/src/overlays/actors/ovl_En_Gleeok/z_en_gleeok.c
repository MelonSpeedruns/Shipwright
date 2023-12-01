/*
 * File: z_en_gleeok.c
 * Overlay: ovl_En_Gleeok
 * Description: Gleeok Boss
 */

#include "z_en_gleeok.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_gleeok/object_gleeok.h"
#include <overlays/actors/ovl_En_Honotrap/z_en_honotrap.h>

#define FLAGS (ACTOR_FLAG_UPDATE_WHILE_CULLED | ACTOR_FLAG_DRAW_WHILE_CULLED | ACTOR_FLAG_DRAGGED_BY_HOOKSHOT | ACTOR_FLAG_CAN_PRESS_SWITCH)

void EnGleeok_Init(Actor* thisx, PlayState* play);
void EnGleeok_Destroy(Actor* thisx, PlayState* play);
void EnGleeok_Update(Actor* thisx, PlayState* play);
void EnGleeok_Draw(Actor* thisx, PlayState* play);

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 8, ICHAIN_STOP),
};

void EnGleeok_Init(Actor* thisx, PlayState* play) {
    EnGleeok* this = (EnGleeok*)thisx;
    SkelAnime_Init(play, &this->skelAnime, &gGleeokBodyDL, NULL, NULL, NULL, 0);
}

void EnGleeok_Destroy(Actor* thisx, PlayState* play) {
    EnGleeok* this = (EnGleeok*)thisx;
}

void EnGleeok_Update(Actor* thisx, PlayState* play) {
    EnGleeok* this = (EnGleeok*)thisx;
}

float lerp(float a, float b, float f) {
    return a * (1.0f - f) + (b * f);
}

float EaseIn(float t) {
    return t * t;
}

float EaseInOut(float t) {
    return lerp(EaseIn(t), EaseOut(t), t);
}

float EaseOut(float t) {
    return Flip(sqrt(Flip(t)));
}

float Flip(float x) {
    return 1 - x;
}

void normalize(Vec3f p) {
    float w = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
    p.x /= w;
    p.y /= w;
    p.z /= w;
}

Vec3f GetRandomPoint() {
    Vec3f randomPoint;

    randomPoint.x = 0.0f;
    randomPoint.y = abs(Rand_CenteredFloat(100.0f));
    randomPoint.z = abs(Rand_CenteredFloat(100.0f));

    normalize(randomPoint);

    return randomPoint;
}

Vec3f prevHeadPos[3];
Vec3f nextHeadPos[3];
float lerpSpeed[3];
f32 timesBeforeShoot[3];
u8 nextHeadPosTimer[3];
float HeadSpeed = 15.0f;

void EnGleeok_Draw(Actor* thisx, PlayState* play) {
    EnGleeok* this = (EnGleeok*)thisx;

    SkelAnime_DrawSkeletonOpa(play, &this->skelAnime, 0, 0, this);

    for (int g = 0; g < 3; g++) {
        u8 spawnFlame = 0;

        if (nextHeadPosTimer[g] <= 0) {
            prevHeadPos[g].x = nextHeadPos[g].x;
            prevHeadPos[g].y = nextHeadPos[g].y;
            prevHeadPos[g].z = nextHeadPos[g].z;
            nextHeadPos[g] = GetRandomPoint();
            nextHeadPos[g].x = (g - 1) * 50.0f;
            lerpSpeed[g] = Rand_ZeroFloat(HeadSpeed) + 15.0f;
            nextHeadPosTimer[g] = lerpSpeed[g];

            timesBeforeShoot[g] -= 1.0f;

            if (timesBeforeShoot[g] < 0.0f) {
                timesBeforeShoot[g] = Rand_ZeroFloat(10.0f);

                spawnFlame = 1;
            }
        } else {
            nextHeadPosTimer[g] -= 1.0f;
        }

        float xValueFinal = this->actor.world.pos.x + nextHeadPos[g].x;
        float yValueFinal = this->actor.world.pos.y + nextHeadPos[g].y;
        float zValueFinal = this->actor.world.pos.z + nextHeadPos[g].z;

        if (spawnFlame == 1) {
            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_HONOTRAP,
                               this->actor.world.pos.x + prevHeadPos[g].x,
                               this->actor.world.pos.y + prevHeadPos[g].y - 40.0f,
                               this->actor.world.pos.z + prevHeadPos[g].z, 0, 0, 0, HONOTRAP_FLAME_MOVE);
        }

        for (int i = 0; i < 7; i++) {
            OPEN_DISPS(play->state.gfxCtx);

            float newXValue = lerp(lerp(this->actor.world.pos.x, xValueFinal, i / 6.0f),
                                   lerp(this->actor.world.pos.x, this->actor.world.pos.x + prevHeadPos[g].x, i / 6.0f),
                                   EaseIn(nextHeadPosTimer[g] / lerpSpeed[g]));

            float newYValue =
                lerp(lerp(this->actor.world.pos.y, yValueFinal, EaseIn(i / 6.0f)),
                     lerp(this->actor.world.pos.y, this->actor.world.pos.y + prevHeadPos[g].y, EaseIn(i / 6.0f)),
                     EaseIn(nextHeadPosTimer[g] / lerpSpeed[g]));

            float newZValue = lerp(lerp(this->actor.world.pos.z, zValueFinal, i / 6.0f),
                                   lerp(this->actor.world.pos.z, this->actor.world.pos.z + prevHeadPos[g].z, i / 6.0f),
                                   EaseIn(nextHeadPosTimer[g] / lerpSpeed[g]));

            Matrix_Translate(newXValue, newYValue, newZValue, MTXMODE_NEW);
            Matrix_RotateZYX(0, i <= 5 ? 0 : this->actor.yawTowardsPlayer, 0, MTXMODE_APPLY);

            float scale = i <= 5 ? lerp(0.25f, 0.15f, i / 6.0f) : 0.3f;
            Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, MATRIX_NEWMTX(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            if (i <= 5) {
                gSPDisplayList(POLY_OPA_DISP++, gGleeokNeckDL);
            } else {
                gSPDisplayList(POLY_OPA_DISP++, gGleeokHeadDL);
            }

            CLOSE_DISPS(play->state.gfxCtx);
        }
    }
}