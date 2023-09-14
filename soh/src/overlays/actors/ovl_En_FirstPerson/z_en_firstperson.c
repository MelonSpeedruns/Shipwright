/*
 * File: z_en_firstperson.c
 * Overlay: ovl_En_FirstPerson
 * Description: First Person Player
 */

#include "z_en_firstperson.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include <overlays/actors/ovl_En_Partner/z_en_partner.h>
#include "objects/gameplay_keep/gameplay_keep.h"
#include <overlays/actors/ovl_En_Arrow/z_en_arrow.h>

#define FLAGS (ACTOR_FLAG_UPDATE_WHILE_CULLED | ACTOR_FLAG_DRAW_WHILE_CULLED)

void EnFirstPerson_Init(Actor* thisx, PlayState* play);
void EnFirstPerson_Destroy(Actor* thisx, PlayState* play);
void EnFirstPerson_Update(Actor* thisx, PlayState* play);
void EnFirstPerson_Draw(Actor* thisx, PlayState* play);

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00020002, 0x00, 0x01 },
        { 0x4FC00748, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 12, 27, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit sCCInfoInit = { 0, 12, 60, MASS_HEAVY };

void EnFirstPerson_Init(Actor* thisx, PlayState* play) {
    EnFirstPerson* this = (EnFirstPerson*)thisx;

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, thisx, &sCylinderInit);
    Collider_UpdateCylinder(thisx, &this->collider);
    CollisionCheck_SetInfo(&thisx->colChkInfo, NULL, &sCCInfoInit);

    thisx->colChkInfo.mass = MASS_HEAVY;
    thisx->gravity = -1.0f;
    thisx->room = -1;
}

void EnFirstPerson_Destroy(Actor* thisx, PlayState* play) {
}

void EnFirstPerson_Update(Actor* thisx, PlayState* play) {
    EnFirstPerson* this = (EnFirstPerson*)thisx;

    Input sControlInput = play->state.input[0];

    f32 relX = sControlInput.cur.stick_x / 10.0f * (CVarGetInteger("gMirroredWorld", 0) ? -1 : 1);
    f32 relY = sControlInput.cur.stick_y / 10.0f;

    this->player.actor.shape.rot.y = GET_ACTIVE_CAM(play)->camDir.y;

    Vec3f camForward = { Math_SinS(this->player.actor.shape.rot.y), 0.0f, Math_CosS(this->player.actor.shape.rot.y) };
    camForward = Vec3fNormalize(camForward);

    Vec3f camRight = { -camForward.z, 0.0f, camForward.x };

    if (thisx->bgCheckFlags & 1) {
        thisx->velocity.y = 0;
    } else {
        thisx->velocity.y += thisx->gravity;
    }

    thisx->velocity.x = 0;
    thisx->velocity.z = 0;

    this->camRightX = -GET_ACTIVE_CAM(play)->camDir.x;

    thisx->velocity.x += camRight.x * relX;
    thisx->velocity.z += camRight.z * relX;
    thisx->velocity.x += camForward.x * relY;
    thisx->velocity.z += camForward.z * relY;

    func_8002D7EC(thisx);
    Actor_UpdateBgCheckInfo(play, thisx, 19.0f, 10.0f, 0.0f, 5);

    Collider_UpdateCylinder(thisx, &this->collider);

    if (CHECK_BTN_ALL(sControlInput.press.button, BTN_Z)) {
        Audio_PlaySoundGeneral(NA_SE_SY_START_SHOT, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);

        Actor* newarrow = Actor_Spawn(&play->actorCtx, play, GetFPSBulletId(), thisx->world.pos.x,
                                             thisx->world.pos.y + 50, thisx->world.pos.z, this->camRightX,
                                             thisx->shape.rot.y, 0, 0, false);

        newarrow->world.pos.x += camRight.x * 9.0f;
        newarrow->world.pos.z += camRight.z * 9.0f;
    }
}

void EnFirstPerson_Draw(Actor* thisx, PlayState* play) {
    EnFirstPerson* this = (EnFirstPerson*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    Matrix_Translate(-850.0f, 5000.0f, -100.0f, MTXMODE_APPLY);
    Matrix_RotateZYX(this->camRightX, 0, 0, MTXMODE_APPLY);
    Matrix_Scale(2.0f, 2.0f, 2.0f, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, MATRIX_NEWMTX(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gPistolDL);

    Player_DrawHookshotReticle(play, this, 3.402823466e+12f);

    CLOSE_DISPS(play->state.gfxCtx);
}