/*
 * File: z_en_firstperson_bullet.c
 * Overlay: ovl_En_FirstPerson_Bullet
 * Description: First Person Bullet
 */

#include "z_en_firstperson_bullet.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_UPDATE_WHILE_CULLED | ACTOR_FLAG_DRAW_WHILE_CULLED)

void EnFirstPersonBullet_Init(Actor* thisx, PlayState* play);
void EnFirstPersonBullet_Destroy(Actor* thisx, PlayState* play);
void EnFirstPersonBullet_Update(Actor* thisx, PlayState* play);
void EnFirstPersonBullet_Draw(Actor* thisx, PlayState* play);

static ColliderQuadInit sQuadInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000020, 0x00, 0x01 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_NEAREST | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000020, 0x00, 0x01 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_ON | TOUCH_NEAREST | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 100, 100, 0, { 0, 0, 0 } },
};

void EnFirstPersonBullet_Init(Actor* thisx, PlayState* play) {
    EnFirstPersonBullet* this = (EnFirstPersonBullet*)thisx;
    EffectBlureInit1 blure;

    blure.p1StartColor[0] = 255;
    blure.p1StartColor[1] = 255;
    blure.p1StartColor[2] = 255;
    blure.p1StartColor[3] = 255;

    blure.p2StartColor[0] = 255;
    blure.p2StartColor[1] = 255;
    blure.p2StartColor[2] = 255;
    blure.p2StartColor[3] = 64;

    blure.p1EndColor[0] = 255;
    blure.p1EndColor[1] = 255;
    blure.p1EndColor[2] = 255;
    blure.p1EndColor[3] = 0;

    blure.p2EndColor[0] = 255;
    blure.p2EndColor[1] = 255;
    blure.p2EndColor[2] = 255;
    blure.p2EndColor[3] = 0;

    blure.elemDuration = 4;
    blure.unkFlag = 0;
    blure.calcMode = 0;
    blure.trailType = 2;

    this->deadTimer = 60;

    //Collider_InitQuad(play, &this->collider);
    //Collider_SetQuad(play, &this->collider, &this->actor, &sQuadInit);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);

    Effect_Add(play, &this->effectIndex, EFFECT_BLURE1, 0, 0, &blure);

    this->collider.info.toucherFlags &= ~0x18;
    this->collider.info.toucherFlags |= 0;
    this->collider.info.toucher.dmgFlags = 0x00000020;
}

void EnFirstPersonBullet_Destroy(Actor* thisx, PlayState* play) {
    EnFirstPersonBullet* this = (EnFirstPersonBullet*)thisx;

    Effect_Delete(play, this->effectIndex);
    Collider_DestroyQuad(play, &this->collider);
}

void EnFirstPersonBullet_Update(Actor* thisx, PlayState* play) {
    EnFirstPersonBullet* this = (EnFirstPersonBullet*)thisx;

    CollisionPoly* hitPoly;
    s32 bgId;
    s32 collidedWithActor;
    Vec3f hitPoint;
    Actor* hitActor;

    this->deadTimer--;

    if (this->deadTimer <= 0) {
        Actor_Kill(thisx);
        return;
    }

    // Move Bullet Forward
    thisx->speedXZ = 300.0f;
    thisx->velocity.x = Math_SinS(thisx->world.rot.y) * thisx->speedXZ;
    thisx->velocity.y = -Math_SinS(thisx->world.rot.x) * thisx->speedXZ;
    thisx->velocity.z = Math_CosS(thisx->world.rot.y) * thisx->speedXZ;
    func_8002D7EC(thisx);

    collidedWithActor = this->collider.base.atFlags & AT_HIT;
    collidedWithActor = !!(collidedWithActor);

    if (collidedWithActor) {
        return;
    }

    if ((this->actor.bgCheckFlags & 0xB)) {
        CollisionCheck_SpawnShieldParticlesMetalSound(play, &thisx->prevPos, &thisx->prevPos);
        Actor_Kill(thisx);
        return;
    }

    Actor_UpdateBgCheckInfo(play, thisx, 20.0f, 20.0f, 60.0f, 0x1D);
    Collider_UpdateCylinder(thisx, &this->collider);
    CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
}

void EnFirstPersonBullet_Draw(Actor* thisx, PlayState* play) {
    EnFirstPersonBullet* this = (EnFirstPersonBullet*)thisx;

    static Vec3f sMultVec1 = { -250.0f, 0.0f, 0.0f };
    static Vec3f sMultVec2 = { 250.0f, 0.0f, 0.0f };
    Vec3f vec1;
    Vec3f vec2;

    OPEN_DISPS(play->state.gfxCtx);

    Matrix_RotateY(this->actor.world.rot.y * (M_PI / 0x8000), MTXMODE_APPLY);
    Matrix_RotateZ(0x1F40 * (M_PI / 0x8000), MTXMODE_APPLY);
    Matrix_RotateX(this->actor.world.rot.x * (M_PI / 0x8000), MTXMODE_APPLY);
    Matrix_MultVec3f(&sMultVec1, &vec1);
    Matrix_MultVec3f(&sMultVec2, &vec2);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, MATRIX_NEWMTX(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_DISPS(play->state.gfxCtx);
}
