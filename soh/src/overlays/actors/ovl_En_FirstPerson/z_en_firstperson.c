/*
 * File: z_en_firstperson.c
 * Overlay: ovl_En_FirstPerson
 * Description: First Person Player
 */

#include "z_en_firstperson.h"
#include <overlays/actors/ovl_En_Partner/z_en_partner.h>
#include <overlays/actors/ovl_En_Arrow/z_en_arrow.h>
#include "soh_assets.h"

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

Vec3f Vec3fNormalizeFirstPerson(Vec3f vec) {
    f32 norm = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));

    if (norm != 0.0f) {
        vec.x /= norm;
        vec.y /= norm;
        vec.z /= norm;
    } else {
        vec.x = vec.y = vec.z = 0.0f;
    }

    return vec;
}

void EnFirstPerson_Update(Actor* thisx, PlayState* play) {
    EnFirstPerson* this = (EnFirstPerson*)thisx;

    // Read inputs from Controller 1
    Input sControlInput = play->state.input[0];

    f32 relX = sControlInput.cur.stick_x / 10.0f * (CVarGetInteger("gMirroredWorld", 0) ? -1 : 1);
    f32 relY = sControlInput.cur.stick_y / 10.0f;

    // Init camera forward and right vectors
    Vec3f camForward = { Math_SinS(play->camX), 0.0f, Math_CosS(play->camX) };
    camForward = Vec3fNormalizeFirstPerson(camForward);

    Vec3f camRight = { -camForward.z, 0.0f, camForward.x };

    // Handle Jumping & Gravity
    if (thisx->bgCheckFlags & 1) {
        if (this->falling == 1) {
            this->falling = 0;
            Audio_PlaySoundGeneral(NA_SE_PL_LAND_GRASS, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        }

        thisx->velocity.y = -5.0f;

        if (CHECK_BTN_ALL(sControlInput.press.button, BTN_A)) {
            this->falling = 1;
            thisx->velocity.y = 10.0f;
            Audio_PlaySoundGeneral(NA_SE_PL_JUMP_GRASS, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        }
    } else {
        if (this->falling == 0) {
            thisx->velocity.y = 0.0f;
            this->falling = 1;
        }
        thisx->velocity.y += thisx->gravity;
    }

    // Set velocity and direction of player to move
    this->player.actor.shape.rot.y = play->camX;

    thisx->velocity.x = 0;
    thisx->velocity.z = 0;

    thisx->velocity.x += -camRight.x * relX;
    thisx->velocity.z += -camRight.z * relX;
    thisx->velocity.x += -camForward.x * relY;
    thisx->velocity.z += -camForward.z * relY;

    // Handle footstep sounds
    Vec3f velocityWithoutY = thisx->velocity;
    velocityWithoutY.y = 0;
    this->footstep_timer -= Math3D_Vec3fMagnitude(&velocityWithoutY);

    if (this->footstep_timer < 0 && this->falling == 0) {
        s32 sfxId = SurfaceType_GetSfx(&play->colCtx, this->player.actor.floorPoly, this->player.actor.floorBgId);
        sfxId = func_8083275C(this->player, sfxId);
        Audio_PlaySoundGeneral(sfxId, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        this->footstep_timer = 40;
    }

    // Move player & Collision with terrain and other actors
    func_8002D7EC(thisx);
    Actor_UpdateBgCheckInfo(play, thisx, 19.0f, 10.0f, 0.0f, 5);
    Collider_UpdateCylinder(thisx, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void EnFirstPerson_Draw(Actor* thisx, PlayState* play) {
    EnFirstPerson* this = (EnFirstPerson*)thisx;
}