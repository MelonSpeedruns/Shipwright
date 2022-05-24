#include "vt.h"
#include "z_link_puppet.h"
#include <objects/gameplay_keep/gameplay_keep.h>
#include <string.h>

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

static Vec3s D_80854730 = { -57, 3377, 0 };

extern func_80833338(Player* this);

void LinkPuppet_Init(Actor* thisx, GlobalContext* globalCtx) {
    LinkPuppet* this = (LinkPuppet*)thisx;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFeet, 90.0f);

    SkelAnime_InitLink(globalCtx, &this->linkSkeleton1, gPlayerSkelHeaders[((void)0, gSaveContext.linkAge)], gPlayerAnim_003240, 9, this->jointTable, this->morphTable, PLAYER_LIMB_MAX);
    this->linkSkeleton1.baseTransl = D_80854730;

    SkelAnime_InitLink(globalCtx, &this->linkSkeleton2, gPlayerSkelHeaders[((void)0, gSaveContext.linkAge)], gPlayerAnim_003240, 9, this->linkSkeleton2.jointTable, this->linkSkeleton2.morphTable, PLAYER_LIMB_MAX);
    this->linkSkeleton2.baseTransl = D_80854730;

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
}

void LinkPuppet_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    LinkPuppet* this = (LinkPuppet*)thisx;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void LinkPuppet_Update(Actor* thisx, GlobalContext* globalCtx) {
    LinkPuppet* this = (LinkPuppet*)thisx;

    LinkAnimation_Update(globalCtx, &this->linkSkeleton1);

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 15.0f, 30.0f, 60.0f, 0x1D);

    Collider_UpdateCylinder(thisx, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

    this->actor.world = this->packet.posRot;
    this->actor.shape.rot = this->packet.posRot.rot;

    this->actor.world.pos.x += 25.0f;
    this->actor.world.pos.z += 25.0f;

    if (strlen(this->packet.animName) != 0) {
        LinkAnimation_Change(globalCtx, &this->linkSkeleton1, this->packet.animName, 1.0f, this->packet.currentFrame,
                             Animation_GetLastFrame(this->packet.animName), this->packet.animMode, 0.0f);
        LinkAnimation_Change(globalCtx, &this->linkSkeleton2, this->packet.animName2, 1.0f, this->packet.currentFrame2,
                             Animation_GetLastFrame(this->packet.animName2), this->packet.animMode2, 0.0f);
    }
}

Vec3f FEET_POS[] = {
    { 200.0f, 300.0f, 0.0f },
    { 200.0f, 200.0f, 0.0f },
};

extern Gfx** sPlayerDListGroups[];
extern Gfx* D_80125D28[];

s32 Puppet_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    LinkPuppet* this = (LinkPuppet*)thisx;

    if (limbIndex == PLAYER_LIMB_SHEATH) {
        Gfx** dLists = &sPlayerDListGroups[this->packet.sheathType][(void)0, gSaveContext.linkAge];
        if ((this->packet.sheathType == 18) || (this->packet.sheathType == 19)) {
            dLists += this->packet.shieldType * 4;
        }
        *dList = ResourceMgr_LoadGfxByName(dLists[0]);
    } else if (limbIndex == PLAYER_LIMB_L_HAND) {
        Gfx** dLists = &sPlayerDListGroups[this->packet][(void)0, gSaveContext.linkAge];

        if ((D_80160014 == 4) && (gSaveContext.swordHealth <= 0.0f)) {
            dLists += 4;
        } else if ((D_80160014 == 6) && (this->stateFlags1 & 0x2000000)) {
            dLists = &D_80125E08[gSaveContext.linkAge];
            D_80160014 = 0;
        } else if ((this->leftHandType == 0) && (this->actor.speedXZ > 2.0f) && !(this->stateFlags1 & 0x8000000)) {
            dLists = &D_80125E18[gSaveContext.linkAge];
            D_80160014 = 1;
        }
        *dList = ResourceMgr_LoadGfxByName(dLists[0]);
    } else if (limbIndex == PLAYER_LIMB_R_HAND) {
        Gfx** dLists = &sPlayerDListGroups[this->packet.sheathType][(void)0, gSaveContext.linkAge];
        if ((this->packet.sheathType == 18) || (this->packet.sheathType == 19)) {
            dLists += this->packet.currentShield * 4;
        }
        *dList = ResourceMgr_LoadGfxByName(dLists[0]);
    }

    return false;
}

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

    AnimationContext_SetCopyAll(globalCtx, this->linkSkeleton1.limbCount, this->linkSkeleton1.jointTable,
                                 this->linkSkeleton2.jointTable);

    func_8008F470(globalCtx, this->linkSkeleton1.skeleton, this->linkSkeleton1.jointTable,
                  this->linkSkeleton1.dListCount, 0, 0, 0, 0, Puppet_OverrideLimbDraw, Puppet_PostLimbDraw, this);
}