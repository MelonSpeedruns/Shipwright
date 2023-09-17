/*
 * File: z_en_firstperson.c
 * Overlay: ovl_En_FirstPerson
 * Description: First Person Player
 */

#include "z_en_firstperson.h"
#include <overlays/actors/ovl_En_Partner/z_en_partner.h>
#include "soh_assets.h"
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

    if (this->reload_timer > 0) {
        this->reload_timer--;

        if (this->reload_timer == 0) {
            Inventory_ChangeAmmo(ITEM_BOW, 60);
            Audio_PlaySoundGeneral(NA_SE_IT_WALL_HIT_SOFT, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        }
    }

    f32 relX = sControlInput.cur.stick_x / 10.0f * (CVarGetInteger("gMirroredWorld", 0) ? -1 : 1);
    f32 relY = sControlInput.cur.stick_y / 10.0f;

    this->player.actor.shape.rot.y = GET_ACTIVE_CAM(play)->camDir.y;

    Vec3f camForward = { Math_SinS(this->player.actor.shape.rot.y), 0.0f, Math_CosS(this->player.actor.shape.rot.y) };
    camForward = Vec3fNormalize(camForward);

    Vec3f camRight = { -camForward.z, 0.0f, camForward.x };

    // Handle Jumping & Gravity
    if (thisx->bgCheckFlags & 1) {
        this->falling = 0;
        thisx->velocity.y = -5.0f;

        if (CHECK_BTN_ALL(sControlInput.press.button, BTN_A)) {
            this->falling = 1;
            thisx->velocity.y = 10.0f;
            Audio_PlaySoundGeneral(NA_SE_PL_JUMP_DIRT, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            Audio_PlaySoundGeneral(NA_SE_PL_JUMP_GRASS, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        }
    } else {
        if (this->falling == 0) {
            thisx->velocity.y = 0.0f;
            this->falling = 1;
        }
        thisx->velocity.y += thisx->gravity;
    }

    thisx->velocity.x = 0;
    thisx->velocity.z = 0;

    thisx->velocity.x += camRight.x * relX;
    thisx->velocity.z += camRight.z * relX;
    thisx->velocity.x += camForward.x * relY;
    thisx->velocity.z += camForward.z * relY;

    func_8002D7EC(thisx);
    Actor_UpdateBgCheckInfo(play, thisx, 19.0f, 10.0f, 0.0f, 5);
    Collider_UpdateCylinder(thisx, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);

    // Shooting & Checking if ammo empty
    if (CHECK_BTN_ALL(sControlInput.press.button, BTN_Z)) {
        if (this->reload_timer == 0) {
            if (AMMO(ITEM_BOW) > 0) {
                Inventory_ChangeAmmo(ITEM_BOW, -1);

                Audio_PlaySoundGeneral(NA_SE_SY_START_SHOT, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
                Audio_PlaySoundGeneral(NA_SE_EV_METALDOOR_STOP, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);

                Actor* newarrow =
                    Actor_Spawn(&play->actorCtx, play, GetFPSBulletId(), play->view.eye.x, play->view.eye.y,
                                play->view.eye.z, play->camY, play->camX + 0x8000, 0, ARROW_NORMAL, false);
            } else {
                Audio_PlaySoundGeneral(NA_SE_IT_WALL_HIT_SOFT, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            }
        }
    }

    // Reloading ammo
    if (CHECK_BTN_ALL(sControlInput.press.button, BTN_B)) {
        if (this->reload_timer == 0 && AMMO(ITEM_BOW) < CUR_CAPACITY(UPG_QUIVER)) {
            Audio_PlaySoundGeneral(NA_SE_EV_TBOX_UNLOCK, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            Audio_PlaySoundGeneral(NA_SE_EV_TBOX_OPEN, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            this->reload_timer = 60;
        }
    }
}

void EnFirstPerson_Draw(Actor* thisx, PlayState* play) {
    EnFirstPerson* this = (EnFirstPerson*)thisx;

    if (this->reload_timer == 0) {
        OPEN_DISPS(play->state.gfxCtx);

        Matrix_Translate(play->view.eye.x, play->view.eye.y, play->view.eye.z, MTXMODE_NEW);
        Matrix_RotateZYX(play->camY, play->camX + 0x8000, 0, MTXMODE_APPLY);
        Matrix_Translate(-10, -5, 20, MTXMODE_APPLY);
        Matrix_Scale(0.02f, 0.02f, 0.02f, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, MATRIX_NEWMTX(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gPistolDL);

        Player_DrawGunReticle(play, this, 3.402823466e+12f);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}