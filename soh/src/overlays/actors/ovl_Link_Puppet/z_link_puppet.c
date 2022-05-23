#include "vt.h"
#include "z_link_puppet.h"
#include <objects/gameplay_keep/gameplay_keep.h>
#include <code/z_play.c>

#define FLAGS ACTOR_FLAG_4

void LinkPuppet_Init(Actor* thisx, GlobalContext* globalCtx);
void LinkPuppet_Destroy(Actor* thisx, GlobalContext* globalCtx);
void LinkPuppet_Update(Actor* thisx, GlobalContext* globalCtx);
void LinkPuppet_Draw(Actor* thisx, GlobalContext* globalCtx);

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT5,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 15, 50, 0, { 0, 0, 0 } },
};

const ActorInit Link_Puppet_InitVars = {
    ACTOR_LINK_PUPPET,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_LINK_BOY,
    sizeof(LinkPuppet),
    (ActorFunc)LinkPuppet_Init,
    (ActorFunc)LinkPuppet_Destroy,
    (ActorFunc)LinkPuppet_Update,
    (ActorFunc)LinkPuppet_Draw,
    NULL,
};

void LinkPuppet_Init(Actor* thisx, GlobalContext* globalCtx) {
    LinkPuppet* this = (LinkPuppet*)thisx;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFeet, 90.0f);
    SkelAnime_InitLink(globalCtx, &this->linkSkeleton, gPlayerSkelHeaders[((void)0, gSaveContext.linkAge)],
                       gPlayerAnim_003240, 9, this->jointTable, this->morphTable, PLAYER_LIMB_MAX);

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
}

void LinkPuppet_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    LinkPuppet* this = (LinkPuppet*)thisx;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void LinkPuppet_Update(Actor* thisx, GlobalContext* globalCtx) {
    LinkPuppet* this = (LinkPuppet*)thisx;

    LinkAnimation_Update(globalCtx, &this->linkSkeleton);

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 15.0f, 30.0f, 60.0f, 0x1D);

    Collider_UpdateCylinder(thisx, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

    this->actor.world.pos.x = posx;
    this->actor.world.pos.y = posy;
    this->actor.world.pos.z = posz;
}

Vec3f FEET_POS[] = {
    { 200.0f, 300.0f, 0.0f },
    { 200.0f, 200.0f, 0.0f },
};

void Puppet_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
    LinkPuppet* this = (LinkPuppet*)thisx;

    Vec3f* vec = &FEET_POS[((void)0, gSaveContext.linkAge)];
    Actor_SetFeetPos(&this->actor, limbIndex, PLAYER_LIMB_L_FOOT, vec, PLAYER_LIMB_R_FOOT, vec);
}

void LinkPuppet_Draw(Actor* thisx, GlobalContext* globalCtx) {
    LinkPuppet* this = (LinkPuppet*)thisx;

    u8 sp12C[2];

    sp12C[0] = 0;
    sp12C[1] = 0;

    func_8008F470(globalCtx, this->linkSkeleton.skeleton, this->linkSkeleton.jointTable, this->linkSkeleton.dListCount,
                  0, 0, 0, 0, 0, Puppet_PostLimbDraw, this);
}