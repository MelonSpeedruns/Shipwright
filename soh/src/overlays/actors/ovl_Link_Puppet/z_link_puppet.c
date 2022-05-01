#include "vt.h"
#include "z_link_puppet.h"
#include <objects/gameplay_keep/gameplay_keep.h>

extern s32 func_80091880(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* arg);

#define FLAGS ACTOR_FLAG_4

void LinkPuppet_Init(Actor* thisx, GlobalContext* globalCtx);
void LinkPuppet_Destroy(Actor* thisx, GlobalContext* globalCtx);
void LinkPuppet_Update(Actor* thisx, GlobalContext* globalCtx);
void LinkPuppet_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Link_Puppet_InitVars = {
    ACTOR_LINK_PUPPET,
    ACTORCAT_PLAYER,
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
    u8* segment = malloc(512*1024);
    func_80091738(globalCtx, segment, &this->linkSkeleton);
}

void LinkPuppet_Destroy(Actor* thisx, GlobalContext* globalCtx) {

}

void LinkPuppet_Update(Actor* thisx, GlobalContext* globalCtx) {
    
}

void LinkPuppet_Draw(Actor* thisx, GlobalContext* globalCtx) {
    LinkPuppet* this = (LinkPuppet*)thisx;

    u8 sp12C[2];

    sp12C[0] = 0;
    sp12C[1] = 0;

    func_8008F470(globalCtx, this->linkSkeleton.skeleton, this->linkSkeleton.jointTable, this->linkSkeleton.dListCount,
                  0, 0, 0, 0, func_80091880, NULL, &sp12C);
}